#include "stdstring.h"
#include <string.h>

struct String {
  char* data_;
  size_t length_;
};

const size_t string_npos = (size_t)(-1);

StringRef string_ctor(const char* src) {
  const size_t length = src ? strlen(src) : 0;
  const StringRef self = safe_malloc(struct String);
  self->data_ = safe_array_malloc(char, length + 1);
  strncpy(self->data_, src, length + 1);
  self->length_ = length;
  return self;
}
