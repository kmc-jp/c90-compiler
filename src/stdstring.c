#include "stdstring_impl.h"
#include <assert.h>
#include <string.h>
#include "allocator_impl.h"

const size_t string_npos = (size_t)(-1);  /* big enough size */

static void* default_allocate_container(void* manager) {
  return safe_malloc(struct String);
  UNUSED(manager);
}
static void* default_allocate_element(size_t count, void* manager) {
  return safe_array_malloc(char, count);
  UNUSED(manager);
}
static void default_deallocate(void* ptr, void* manager) {
  safe_free(ptr);
  UNUSED(manager);
}
AllocatorRef string_default_allocator(void) {
  static const struct Allocator allocator = {
    NULL,
    default_allocate_container,
    default_allocate_element,
    default_deallocate
  };
  return &allocator;
}

/* private functions for implementations follow */
static StringRef string_container_alloc(AllocatorRef allocator) {
  const StringRef self = allocate_container(allocator);
  self->data_ = NULL;
  self->length_ = self->capacity_ = 0;
  self->allocator_ = allocator;
  return self;
}
static void string_container_free(StringRef* pself) {
  deallocate((*pself)->allocator_, *pself);
  *pself = NULL;
}
static void string_set_end(StringRef self, char data) {
  self->data_[self->length_] = data;
}
static void string_set_length(StringRef self, size_t length) {
  self->length_ = length;
  self->data_[length] = '\0';
}
static void string_free(StringRef self) {
  deallocate(self->allocator_, self->data_);
}
static void string_init_copy(StringRef self, const char* src, size_t length) {
  memcpy(self->data_, src, length);
  string_set_length(self, length);
}
static void string_init_move(StringRef self, const char* src, size_t length) {
  memmove(self->data_, src, length);
  string_set_length(self, length);
}
static void string_alloc(StringRef self, size_t size) {
  /* capacity do not include terminating null character */
  const size_t capacity = enough_capacity(size + 1) - 1;
  /* storage hold terminating null character */
  self->data_ = allocate_element(self->allocator_, capacity + 1);
  self->capacity_ = capacity;
}
static void string_extend(StringRef self, size_t size) {
  if (self->capacity_ < size) {
    string_free(self);
    string_alloc(self, size);
  }
}


StringRef make_string(const char* src, size_t length, AllocatorRef allocator) {
  assert(src);
  {
    const StringRef self = string_container_alloc(
        allocator ? allocator : string_default_allocator());
    string_alloc(self, length);
    string_init_copy(self, src, length);
    return self;
  }
}

StringRef string_ctor(const char* src, AllocatorRef allocator) {
  assert(src);
  return make_string(src, strlen(src), allocator);
}

void string_dtor(StringRef* pself) {
  assert(pself);
  if (*pself) {
    string_free(*pself);
    string_container_free(pself);
  }
}

void string_copy(StringRef self, StringRef src) {
  assert(self && src);
  {
    const size_t length = string_length(src);
    string_extend(self, length);
    string_init_copy(self, string_data(src), length);
  }
}

void string_assign(StringRef self, const char* src) {
  assert(self && src);
  {
    const size_t length = strlen(src);
    string_extend(self, length);
    string_init_move(self, src, length);
  }
}

char string_at(StringRef self, size_t index) {
  assert(self);
  return string_data(self)[index];
}

char string_front(StringRef self) {
  assert(self);
  return *string_begin(self);
}

char string_back(StringRef self) {
  assert(self);
  if (string_empty(self)) {
    /* return null character */
    return string_end(self)[0];
  }
  /* return end of string */
  return string_end(self)[-1];
}

char* string_data(StringRef self) {
  assert(self);
  return self->data_;
}

char* string_begin(StringRef self) {
  assert(self);
  return string_data(self);
}

char* string_end(StringRef self) {
  assert(self);
  return string_data(self) + string_length(self);
}

bool string_empty(StringRef self) {
  assert(self);
  return string_length(self) == 0;
}

size_t string_length(StringRef self) {
  assert(self);
  return self->length_;
}

void string_reserve(StringRef self, size_t size) {
  assert(self);
  if (string_capacity(self) < size) {
    char* original = string_data(self);
    string_alloc(self, size);
    string_init_copy(self, original, string_length(self));
    safe_free(original);
  }
}

size_t string_capacity(StringRef self) {
  assert(self);
  return self->capacity_;
}

void string_shrink_to_fit(StringRef self) {
  assert(self);
  {
    const size_t length = string_length(self);
    if (length < string_capacity(self)) {
      char* original = string_data(self);
      string_alloc(self, length);
      string_init_copy(self, original, length);
      safe_free(original);
    }
  }
}

void string_clear(StringRef self) {
  assert(self);
  string_set_length(self, 0);
}

void string_insert(StringRef self, size_t index, StringRef data) {
  assert(self && data);
  {
    const size_t count = string_length(data);
    const size_t length = string_length(self);
    const size_t new_length = length + count;
    string_reserve(self, new_length);
    if (0 < count) {
      char* const head = string_data(self) + index;
      char* const tail = head + count;
      memmove(tail, head, length - index);
      memcpy(head, string_data(data), count);
      string_set_length(self, new_length);
    }
  }
}

void string_erase(StringRef self, size_t index, size_t count) {
  assert(self);
  {
    const size_t length = string_length(self);
    if (count == string_npos || length < index + count) {
      string_set_length(self, index);
    } else {
      char* const head = string_data(self) + index;
      char* const tail = head + count;
      const size_t new_length = length - count;
      memmove(head, tail, new_length - index);
      string_set_length(self, new_length);
    }
  }
}

void string_push_back(StringRef self, char data) {
  assert(self);
  {
    const size_t length = string_length(self);
    string_reserve(self, length + 1);
    string_set_end(self, data);
    string_set_length(self, length + 1);
  }
}

void string_pop_back(StringRef self) {
  assert(self);
  string_set_length(self, string_length(self) - 1);
}

void string_append(StringRef self, StringRef data) {
  assert(self && data);
  {
    const size_t count = string_length(data);
    const size_t new_length = string_length(self) + count;
    string_reserve(self, new_length);
    memcpy(string_end(self), string_data(data), count);
    string_set_length(self, new_length);
  }
}

int string_compare(StringRef self, StringRef other) {
  assert(self && other);
  return strcmp(string_data(self), string_data(other));
}

void string_replace(StringRef self, size_t index, size_t count,
                    StringRef data) {
  assert(self && data);
  {
    const size_t length = string_length(self);
    const size_t data_length = string_length(data);
    if (count == string_npos || length < index + count) {
      count = length - index;
    }
    {
      const size_t new_length = length + data_length - count;
      string_reserve(self, new_length);
      {
        char* const head = string_data(self) + index;
        char* const dst = head + data_length;
        char* const src = head + count;
        memmove(dst, src, length - index - count);
        memcpy(head, string_data(data), data_length);
        string_set_length(self, new_length);
      }
    }
  }
}

StringRef string_substr(StringRef self, size_t index, size_t count) {
  assert(self);
  {
    const size_t length = string_length(self);
    char* const src = string_data(self) + index;
    if (count == string_npos || length < index + count) {
      count = length - index;
    }
    return make_string(src, count, self->allocator_);
  }
}

size_t string_copy_to(StringRef self, char* dst, size_t count, size_t index) {
  assert(self && dst);
  {
    const size_t length = string_length(self);
    char* const src = string_data(self) + index;
    if (count == string_npos || length < index + count) {
      count = length - index;
    }
    memmove(dst, src, count);
    return count;
  }
}

void string_resize(StringRef self, size_t size) {
  assert(self);
  {
    const size_t length = string_length(self);
    if (length < size) {
      string_reserve(self, size);
      memset(string_end(self), '\0', size - length);
    }
    string_set_length(self, size);
  }
}

void string_swap(StringRef self, StringRef other) {
  assert(self && other);
  {
    struct String tmp = *self;
    *self = *other;
    *other = tmp;
  }
}

size_t string_find(StringRef self, const char* str) {
  assert(self && str);
  {
    char* const data = string_data(self);
    char* const found = strstr(data, str);
    if (found) {
      return found - data;
    } else {
      return string_npos;
    }
  }
}

size_t string_find_first_of(StringRef self, const char* str) {
  assert(self && str);
  {
    const size_t found = strcspn(string_data(self), str);
    return found == string_length(self) ? string_npos : found;
  }
}

size_t string_find_first_not_of(StringRef self, const char* str) {
  assert(self && str);
  {
    const size_t found = strspn(string_data(self), str);
    return found == string_length(self) ? string_npos : found;
  }
}
