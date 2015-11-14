#include "stdstring.h"
#include <assert.h>
#include <string.h>

struct String {
  char* data_;
  size_t length_;
  size_t capacity_;
};

const size_t string_npos = (size_t)(-1);

static void string_alloc(StringRef self, size_t size) {
  self->data_ = safe_array_malloc(char, size);
}
static void string_init(StringRef self, const char* src,
                        size_t length, size_t capacity) {
  strncpy(self->data_, src, length + 1);
  self->length_ = length;
  self->capacity_ = capacity;
}
static void string_new(StringRef self, const char* src,
                       size_t length, size_t size) {
  const size_t capacity = enough_capacity(size + 1) - 1;
  string_alloc(self, capacity + 1);
  string_init(self, src, length, capacity);
}
static void string_free(StringRef self) {
  safe_free(self->data_);
}

StringRef string_ctor(const char* src) {
  const size_t length = src ? strlen(src) : 0;
  const StringRef self = safe_malloc(struct String);
  string_new(self, src, length, length);
  return self;
}

void string_dtor(StringRef* pself) {
  assert(pself);
  if (*pself) {
    string_free(*pself);
    safe_free(*pself);
  }
}

char* string_data(StringRef self) {
  assert(self);
  return self->data_;
}

size_t string_length(StringRef self) {
  assert(self);
  return self->length_;
}

void string_reserve(StringRef self, size_t size) {
  assert(self);
  if (string_capacity(self) < size) {
    char* old_data = string_data(self);
    string_new(self, old_data, string_length(self), size);
    safe_free(old_data);
  }
}

size_t string_capacity(StringRef self) {
  assert(self);
  return self->capacity_;
}
