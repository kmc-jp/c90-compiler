#ifndef KMC_C89_COMPILER_UTILITY_H
#define KMC_C89_COMPILER_UTILITY_H

#include <stddef.h>

#define UNUSED(x) (void)(x)

#ifndef __cplusplus
typedef signed char bool;
extern const bool true;
extern const bool false;
#endif  /* __cplusplus */

#endif  /* KMC_C89_COMPILER_UTILITY_H */
