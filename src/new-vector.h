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

AllocatorRef vector_default_allocator(void);

/* generate initialized vector */
VECTORREF(Type) make_vector(AllocatorRef allocator,
                            const Type* src, size_t count);

/* constructor */
VECTORREF(Type) vector_ctor(AllocatorRef allocator);
/* destructor */
void vector_dtor(VECTORREF(Type)* pself);
/* operator= */
void vector_copy(VECTORREF(Type) self, VECTORREF(Type) src);
/* assign */
void vector_assign(VECTORREF(Type) self, const Type* src, size_t count);

/* at */
/* undefined behavior if out of range */
Type vector_at(VECTORREF(Type) self, size_t index);
/* front */
/* undefined behavior if empty */
Type vector_front(VECTORREF(Type) self);
/* front */
/* undefined behavior if empty */
Type vector_back(VECTORREF(Type) self);
/* data */
/* same as begin */
Type* vector_data(VECTORREF(Type) self);
/* begin */
Type* vector_begin(VECTORREF(Type) self);
/* end */
Type* vector_end(VECTORREF(Type) self);

/* empty */
bool vector_empty(VECTORREF(Type) self);
/* size */
size_t vector_size(VECTORREF(Type) self);
/* reserve */
void vector_reserve(VECTORREF(Type) self, size_t size);
/* capacity */
size_t vector_capacity(VECTORREF(Type) self);
/* shrink_to_fit */
void vector_shrink_to_fit(VECTORREF(Type) self);

/* clear */
void vector_clear(VECTORREF(Type) self);
/* insert */
/* undefined behavior if index is out of range */
void vector_insert(VECTORREF(Type) self, size_t index,
                   const Type* data, size_t count);
/* erase */
/* undefined behavior if index is out of range */
/* remove from index to the end if 'index + count' is out of range */
void vector_erase(VECTORREF(Type) self, size_t index, size_t count);
/* push_back */
void vector_push_back(VECTORREF(Type) self, Type data);
/* pop_back */
/* undefined behavior if empty */
void vector_pop_back(VECTORREF(Type) self);
/* resize */
void vector_resize(VECTORREF(Type) self, size_t size, Type fill);
/* swap */
void vector_swap(VECTORREF(Type) self, VECTORREF(Type) other);

END_EXTERN_C

#endif  /* KMC_C89_COMPILER_NEW_VECTOR_H */
