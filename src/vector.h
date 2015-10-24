#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

#include <stddef.h>

typedef signed char bool;

/* to make compilable */
#define Type int

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)

/* template macro */
#define T(identifier, type) CONCAT(WITHBAR(identifier), WITHBAR(type))
#define V(type) T(Vector, type)
#define VR(type) T(VectorRef, type)
#define VM(type) T(VectorMethods, type)
#define GV(type) CONCAT(global_, VM(type))
#define VF(function, type) T(CONCAT(Vector, function), type)

typedef void (*T(CtorMethod, Type))(Type* value);
typedef void (*T(DtorMethod, Type))(Type* value);
typedef void (*T(CopyMethod, Type))(Type* dst, Type* src);

/* special member functions */
struct VM(Type) {
  T(CtorMethod, Type) ctor_;
  T(DtorMethod, Type) dtor_;
  T(CopyMethod, Type) copy_;
};
extern struct VM(Type) GV(Type);

/* first of all, you must initialize special member functions */
void T(VectorInitialize, Type)(T(CtorMethod, Type) ctor,
                               T(DtorMethod, Type) dtor,
                               T(CopyMethod, Type) copy);

/* vector of Type */
struct V(Type) {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
};

/* reference to vector of Type */
typedef struct V(Type)* VR(Type);

/* constructor */
VR(Type) VF(Ctor, Type)(void);
/* destructor */
void VF(Dtor, Type)(VR(Type)* pv);
/* operator= */
void VF(Copy, Type)(VR(Type) dst, VR(Type) src);
/* assign */
void VF(Assign, Type)(VR(Type) v, Type* data, size_t size);
/* data */
Type* VF(Data, Type)(VR(Type) v);
/* begin */
Type* VF(Begin, Type)(VR(Type) v);
/* end */
Type* VF(End, Type)(VR(Type) v);
/* empty */
bool VF(Empty, Type)(VR(Type) v);
/* size */
size_t VF(Size, Type)(VR(Type) v);
/* reserve */
void VF(Reserve, Type)(VR(Type) v, size_t size);
/* capacity */
size_t VF(Capacity, Type)(VR(Type) v);
/* clear */
void VF(Clear, Type)(VR(Type) v);
/* pop_back */
/* calling pop_back on empty vector is undefined */
void VF(Pop, Type)(VR(Type) v);

#endif  /* KMC_C89_COMPILER_VECTOR_H */
