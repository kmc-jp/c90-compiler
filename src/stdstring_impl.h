#ifndef KMC_C89_COMPILER_STDSTRING_IMPL_H
#define KMC_C89_COMPILER_STDSTRING_IMPL_H

#include "allocator.h"
#include "stdstring.h"

struct String {
  char* data_;  /* contents of string */
  size_t length_;  /* length of data_ without terminating null character */
  size_t capacity_;  /* capacity of data_ without terminating null character */
  AllocatorRef allocator_;
};

#endif  /* KMC_C89_COMPILER_STDSTRING_IMPL_H */
