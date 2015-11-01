#ifndef KMC_C89_COMPILER_USE_VECTOR_H
#define KMC_C89_COMPILER_USE_VECTOR_H

#include "vector.h"

DECLARE_VECTOR(char)
DECLARE_DEFAULT_METHODS(char)

/* Add initialization for VECTORREF(Type) to this */
/* Then call this at the head of execution
   like at the beginning of main */
void initialize_vector();

#endif  /* KMC_C89_COMPILER_USE_VECTOR_H */
