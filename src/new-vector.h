#ifndef KMC_C89_COMPILER_NEW_VECTOR_H
#define KMC_C89_COMPILER_NEW_VECTOR_H

#include "utility.h"
#include "allocator.h"

#define VECTOR(type) \
  TEMPLATE(type, Vector)
#define VECTORREF(type) \
  TEMPLATE(type, VectorRef)
#define VECTORFUNC(type, function) \
  CONCAT(VECTOR(type), function)

typedef int Type;

/* reference to vector of Type */
typedef struct VECTOR(Type)* VECTORREF(Type);

BEGIN_EXTERN_C

AllocatorRef VECTORFUNC(Type, default_allocator)(void);

/* generate initialized vector */
VECTORREF(Type) VECTORFUNC(Type, make_vector)(AllocatorRef allocator,
                                              const Type* src, size_t count);

/* constructor */
VECTORREF(Type) VECTORFUNC(Type, ctor)(AllocatorRef allocator);
/* destructor */
void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pself);
/* operator= */
void VECTORFUNC(Type, copy)(VECTORREF(Type) self, VECTORREF(Type) src);
/* assign */
void VECTORFUNC(Type, assign)(VECTORREF(Type) self,
                              const Type* src, size_t count);

/* at */
/* undefined behavior if out of range */
Type VECTORFUNC(Type, at)(VECTORREF(Type) self, size_t index);
/* front */
/* undefined behavior if empty */
Type VECTORFUNC(Type, front)(VECTORREF(Type) self);
/* front */
/* undefined behavior if empty */
Type VECTORFUNC(Type, back)(VECTORREF(Type) self);
/* data */
/* same as begin */
Type* VECTORFUNC(Type, data)(VECTORREF(Type) self);
/* begin */
Type* VECTORFUNC(Type, begin)(VECTORREF(Type) self);
/* end */
Type* VECTORFUNC(Type, end)(VECTORREF(Type) self);

/* empty */
bool VECTORFUNC(Type, empty)(VECTORREF(Type) self);
/* size */
size_t VECTORFUNC(Type, size)(VECTORREF(Type) self);
/* reserve */
void VECTORFUNC(Type, reserve)(VECTORREF(Type) self, size_t size);
/* capacity */
size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) self);
/* shrink_to_fit */
void VECTORFUNC(Type, shrink_to_fit)(VECTORREF(Type) self);

/* clear */
void VECTORFUNC(Type, clear)(VECTORREF(Type) self);
/* insert */
/* undefined behavior if index is out of range */
void VECTORFUNC(Type, insert)(VECTORREF(Type) self, size_t index,
                              const Type* data, size_t count);
/* erase */
/* undefined behavior if index is out of range */
/* remove from index to the end if 'index + count' is out of range */
void VECTORFUNC(Type, erase)(VECTORREF(Type) self, size_t index, size_t count);
/* push_back */
void VECTORFUNC(Type, push_back)(VECTORREF(Type) self, Type data);
/* pop_back */
/* undefined behavior if empty */
void VECTORFUNC(Type, pop_back)(VECTORREF(Type) self);
/* resize */
void VECTORFUNC(Type, resize)(VECTORREF(Type) self, size_t size, Type fill);
/* swap */
void VECTORFUNC(Type, swap)(VECTORREF(Type) self, VECTORREF(Type) other);

END_EXTERN_C

#endif  /* KMC_C89_COMPILER_NEW_VECTOR_H */
