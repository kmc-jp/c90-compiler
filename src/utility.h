#ifndef KMC_C89_COMPILER_UTILITY_H
#define KMC_C89_COMPILER_UTILITY_H

#include <stddef.h>

#define UNUSED(x) (void)(x)
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) < (y) ? (y) : (x))

#ifndef __cplusplus
#define ALIGNOF(type)                                           \
  MIN(sizeof(type), offsetof(struct { char a; type b; }, b))
#endif

#ifndef __cplusplus
typedef signed char bool;
#define true ((bool)1)
#define false ((bool)0)
#endif  /* __cplusplus */

typedef unsigned char byte;

#ifdef __cplusplus
#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }
#else
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif

#define safe_malloc(type) \
  (type*)safe_malloc_impl(sizeof(type))
#define safe_array_malloc(type, size) \
  (type*)safe_malloc_impl(sizeof(type) * (size))
#define safe_free(ptr) \
  do { safe_free_impl(ptr); (ptr) = NULL; } while (false)

BEGIN_EXTERN_C

void* safe_malloc_impl(size_t size);
void safe_free_impl(void* ptr);

/* size <= capacity && capacity == pow(2, n) */
size_t enough_capacity(size_t size);
/* return true if size is power of 2 */
bool is_power_of_two(size_t size);
/* return offset address require to satisfy alignment */
size_t align_offset(void* address, size_t alignment);

END_EXTERN_C

#endif  /* KMC_C89_COMPILER_UTILITY_H */
