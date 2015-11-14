#include "stdstring.h"
#include <assert.h>
#include <string.h>

struct String {
  char* data_;
  size_t length_;
  size_t capacity_;
};

const size_t string_npos = (size_t)(-1);

static void string_new(StringRef self, const char* src,
                       size_t length, size_t size) {
  const size_t capacity = enough_capacity(size + 1);
  self->data_ = safe_array_malloc(char, capacity);
  strncpy(self->data_, src, length + 1);
  self->length_ = length;
  self->capacity_ = capacity - 1;
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
    safe_free((*pself)->data_);
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

size_t string_capacity(StringRef self) {
  assert(self);
  return self->capacity_;
}
