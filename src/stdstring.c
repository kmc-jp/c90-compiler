#include "stdstring.h"
#include <assert.h>
#include <string.h>

struct String {
  char* data_;
  size_t length_;
  size_t capacity_;
};

const size_t string_npos = (size_t)(-1);

StringRef string_ctor(const char* src) {
  const size_t length = src ? strlen(src) : 0;
  const size_t size = enough_capacity(length + 1);
  const StringRef self = safe_malloc(struct String);
  self->data_ = safe_array_malloc(char, size);
  strncpy(self->data_, src, length + 1);
  self->length_ = length;
  self->capacity_ = size - 1;
  return self;
}

void string_dtor(StringRef* pself) {
  assert(pself);
  if (*pself) {
    safe_free((*pself)->data_);
    safe_free(*pself);
  }
}
