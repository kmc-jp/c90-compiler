#ifndef KMC_C89_COMPILER_UTILITY_H
#define KMC_C89_COMPILER_UTILITY_H

#include <stddef.h>

#define UNUSED(x) (void)(x)

#ifndef __cplusplus
typedef signed char bool;
#define true ((bool)1)
#define false ((bool)0)
#endif  /* __cplusplus */

#ifdef __cplusplus
#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }
#else
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif

#define safe_malloc(type)                       \
  (type*)safe_malloc_impl(sizeof(type))
#define safe_array_malloc(type, size)                   \
  (type*)safe_malloc_impl(sizeof(type) * (size))
#define safe_free(ptr)                                          \
  do { safe_free_impl(ptr); (ptr) = NULL; } while (false)

BEGIN_EXTERN_C

void* safe_malloc_impl(size_t size);
void safe_free_impl(void* ptr);

/* size <= capacity && capacity == pow(2, n) */
size_t enough_capacity(size_t size);

END_EXTERN_C

#endif  /* KMC_C89_COMPILER_UTILITY_H */
