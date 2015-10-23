#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

/* to make compilable */
#define Type int

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)

/* template macro */
#define T(identifier, type) CONCAT(WITHBAR(identifier), WITHBAR(type))
#define V(type) T(Vector, type)
#define VR(type) T(VectorRef, type)

/* vector of Type */
struct V(Type) {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
};

/* reference to vector of Type */
typedef struct V(Type)* VR(Type);

#endif  /* KMC_C89_COMPILER_VECTOR_H */
