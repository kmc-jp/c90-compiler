#include "stdstring.h"
#include <assert.h>
#include <string.h>

struct String {
  char* data_;
  size_t length_;
  size_t capacity_;
};

const size_t string_npos = (size_t)(-1);

static void string_set_end(StringRef self, char data) {
  self->data_[self->length_] = data;
}
static void string_set_length(StringRef self, size_t length) {
  self->length_ = length;
  self->data_[length] = '\0';
}
static void string_free(StringRef self) {
  safe_free(self->data_);
}
static void string_init(StringRef self, const char* src, size_t length) {
  memcpy(self->data_, src, length);
  string_set_length(self, length);
}
static void string_alloc(StringRef self, size_t size) {
  self->data_ = safe_array_malloc(char, enough_capacity(size + 1));
  self->capacity_ = size - 1;
}
static void string_extend(StringRef self, size_t size) {
  if (self->capacity_ < size) {
    string_free(self);
    string_alloc(self, size);
  }
}
StringRef string_ctor_impl(const char* src, size_t length) {
  const StringRef self = safe_malloc(struct String);
  string_alloc(self, length);
  string_init(self, src, length);
  return self;
}

StringRef string_ctor(const char* src) {
  src = src ? src : "";
  return string_ctor_impl(src, strlen(src));
}

void string_dtor(StringRef* pself) {
  assert(pself);
  if (*pself) {
    string_free(*pself);
    safe_free(*pself);
  }
}

void string_copy(StringRef self, StringRef src) {
  assert(self && src);
  {
    const size_t length = string_length(src);
    string_extend(self, length);
    string_init(self, string_data(src), length);
  }
}

void string_assign(StringRef self, const char* src) {
  assert(self);
  src = src ? src : "";
  {
    const size_t length = strlen(src);
    string_extend(self, length);
    string_init(self, src, length);
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
  return *string_end(self);
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
    string_init(self, original, string_length(self));
    safe_free(original);
  }
}

size_t string_capacity(StringRef self) {
  assert(self);
  return self->capacity_;
}

void string_clear(StringRef self) {
  assert(self);
  string_set_length(self, 0);
}

void string_insert(StringRef self, size_t index, const char* data) {
  assert(self);
  if (data) {
    const size_t count = strlen(data);
    const size_t length = string_length(self);
    const size_t new_length = length + count;
    string_reserve(self, new_length);
    if (0 < count) {
      char* const head = string_data(self) + index;
      char* const tail = head + count;
      memmove(tail, head, length - index);
      memcpy(head, data, count);
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

void string_append(StringRef self, const char* data) {
  assert(self);
  if (data) {
    const size_t count = strlen(data);
    const size_t new_length = string_length(self) + count;
    string_reserve(self, new_length);
    memcpy(string_end(self), data, count);
    string_set_length(self, new_length);
  }
}

int string_compare(StringRef self, StringRef other) {
  assert(self && other);
  return strcmp(string_data(self), string_data(other));
}

void string_replace(StringRef self, size_t index, size_t count,
                    const char* data) {
  assert(self);
  if (data) {
    const size_t length = string_length(self);
    const size_t data_length = strlen(data);
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
        memcpy(head, data, data_length);
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
    return string_ctor_impl(src, count);
  }
}

size_t string_copy_to(StringRef self, char* dst, size_t count, size_t index) {
  assert(self);
  {
    const size_t length = string_length(self);
    char* const src = string_data(self) + index;
    if (count == string_npos || length < index + count) {
      count = length - index;
    }
    memcpy(dst, src, count);
    return count;
  }
}

void string_resize(StringRef self, size_t size) {
  assert(self);
  {
    const size_t length = string_length(self);
    if (length < size) {
      string_reserve(self, size);
      memset(string_end(self), 0, size - length);
    }
    string_set_length(self, size);
  }
}

void string_swap(StringRef self, StringRef other) {
  assert(self);
  {
    struct String tmp = *self;
    *self = *other;
    *other = tmp;
  }
}

size_t string_find(StringRef self, const char* str) {
  assert(self);
  {
    char* const data = string_data(self);
    char* const head = strstr(data, str);
    if (head) {
      return head - data;
    } else {
      return string_npos;
    }
  }
}

size_t string_find_first_of(StringRef self, const char* str) {
  assert(self);
  {
    const size_t found = strcspn(string_data(self), str);
    return found == string_length(self) ? string_npos : found;
  }
}

size_t string_find_first_not_of(StringRef self, const char* str) {
  assert(self);
  {
    const size_t found = strspn(string_data(self), str);
    return found == string_length(self) ? string_npos : found;
  }
}
