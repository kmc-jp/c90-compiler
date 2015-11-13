#ifndef KMC_C89_COMPILER_MEMORY_POOL_H
#define KMC_C89_COMPILER_MEMORY_POOL_H

#include "utility.h"

#define palloc(type, pool, count)                                       \
  (type*)palloc_impl(pool, sizeof(type) * (count), ALIGNOF(type))

typedef struct MemoryPool* MemoryPoolRef;

/* create memory pool
   each block size is 'size' */
MemoryPoolRef memory_pool_ctor(size_t size);
/* destroy memory pool */
void memory_pool_dtor(MemoryPoolRef* ppool);
/* allocate 'size' memory from pool */
void* palloc_impl(MemoryPoolRef pool, size_t size, size_t alignment);

#endif  /* KMC_C89_COMPILER_MEMORY_POOL_H */
