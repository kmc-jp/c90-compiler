#include "stdstring.h"

struct String {
  char* data_;
  size_t length_;
};

const size_t string_npos = (size_t)(-1);
