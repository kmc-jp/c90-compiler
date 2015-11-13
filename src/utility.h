#ifndef KMC_C89_COMPILER_UTILITY_H
#define KMC_C89_COMPILER_UTILITY_H

#include <stddef.h>

#define UNUSED(x) (void)(x)
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) < (y) ? (y) : (x))

#ifdef __cplusplus
namespace detail {
template <typename T>
class align_of {
  struct inner {
    char a;
    T b;
  };
 public:
  static const std::size_t value = offsetof(inner, b);
};
}
#endif

#ifndef __cplusplus
#define ALIGNOF(type)                                           \
  MIN(sizeof(type), offsetof(struct { char a; type b; }, b))
#else
#define ALIGNOF(type)                                   \
  MIN(sizeof(type), detail::align_of<type>::value)
#endif

#ifndef __cplusplus
typedef signed char bool;
#define true ((bool)1)
#define false ((bool)0)
#endif  /* __cplusplus */

typedef unsigned char byte;

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
