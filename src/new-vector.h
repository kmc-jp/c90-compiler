#ifndef KMC_C89_COMPILER_NEW_VECTOR_H
#define KMC_C89_COMPILER_NEW_VECTOR_H

#include "utility.h"

#define VECTOR_MEMORY_COPY(dst, src, count)             \
  memory_copy((dst), (src), sizeof(Type), (count))
#define VECTOR_MEMORY_MOVE(dst, src, count)             \
  memory_move((dst), (src), sizeof(Type), (count))

typedef int Type;

/* reference to vector of Type */
typedef struct Vector* VectorRef;
/* allocator for vector */
typedef struct VectorAllocator* VectorAllocatorRef;

/* generate initialized vector */
VectorRef make_vector(const Type* src, size_t count);

/* constructor */
VectorRef vector_ctor(void);
/* destructor */
void vector_dtor(VectorRef* pself);
/* operator= */
void vector_copy(VectorRef self, VectorRef src);
/* assign */
void vector_assign(VectorRef self, const Type* src, size_t count);

/* at */
/* undefined behavior if out of range */
Type vector_at(VectorRef self, size_t index);
/* front */
/* undefined behavior if empty */
Type vector_front(VectorRef self);
/* front */
/* undefined behavior if empty */
Type vector_back(VectorRef self);
/* data */
/* same as begin */
Type* vector_data(VectorRef self);
/* begin */
Type* vector_begin(VectorRef self);
/* end */
Type* vector_end(VectorRef self);

/* empty */
bool vector_empty(VectorRef self);
/* size */
size_t vector_size(VectorRef self);
/* reserve */
void vector_reserve(VectorRef self, size_t size);
/* capacity */
size_t vector_capacity(VectorRef self);
/* shrink_to_fit */
void vector_shrink_to_fit(VectorRef self);

/* clear */
void vector_clear(VectorRef self);
/* insert */
/* undefined behavior if index is out of range */
void vector_insert(VectorRef self, size_t index,
                   const Type* data, size_t count);
/* erase */
/* undefined behavior if index is out of range */
/* remove from index to the end if 'index + count' is out of range */
void vector_erase(VectorRef self, size_t index, size_t count);
/* push_back */
void vector_push_back(VectorRef self, Type data);
/* pop_back */
/* undefined behavior if empty */
void vector_pop_back(VectorRef self);
/* resize */
void vector_resize(VectorRef self, size_t size, Type fill);
/* swap */
void vector_swap(VectorRef self, VectorRef other);

#endif  /* KMC_C89_COMPILER_NEW_VECTOR_H */
