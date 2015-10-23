#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)

/* template macro */
#define T(identifier, type) CONCAT(WITHBAR(identifier), WITHBAR(type))

#endif  /* KMC_C89_COMPILER_VECTOR_H */
