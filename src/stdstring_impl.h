#ifndef INCLUDE_GUARD_UUID_5C5CF2B9_E7DB_49BB_94B3_F1C9EEE856D8
#define INCLUDE_GUARD_UUID_5C5CF2B9_E7DB_49BB_94B3_F1C9EEE856D8

#include "allocator.h"
#include "stdstring.h"

struct String {
  char* data_;  /* contents of string */
  size_t length_;  /* length of data_ without terminating null character */
  size_t capacity_;  /* capacity of data_ without terminating null character */
  AllocatorRef allocator_;
};

#endif  /* INCLUDE_GUARD_UUID_5C5CF2B9_E7DB_49BB_94B3_F1C9EEE856D8 */
