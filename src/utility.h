#ifndef KMC_C89_COMPILER_UTILITY_H
#define KMC_C89_COMPILER_UTILITY_H

#include <stddef.h>

#define UNUSED(x) (void)(x)

#ifndef __cplusplus
typedef signed char bool;
#define true ((bool)1)
#define false ((bool)0)
#endif  /* __cplusplus */

void* safe_malloc_impl(size_t size);
#define safe_malloc(type)                       \
  (type*)safe_malloc_impl(sizeof(type))
#define safe_array_malloc(type, size)           \
  (type*)safe_malloc_impl(sizeof(type) * (size))

void safe_free_impl(void* ptr);
#define safe_free(ptr)                          \
  do { safe_free_impl(ptr); ptr = NULL; } while(false)

/* size <= capacity && capacity == pow(2, n) */
size_t enough_capacity(size_t size);

#endif  /* KMC_C89_COMPILER_UTILITY_H */
