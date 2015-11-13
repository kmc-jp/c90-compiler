#ifndef KMC_C89_COMPILER_MEMORY_POOL_H
#define KMC_C89_COMPILER_MEMORY_POOL_H

#include "utility.h"

typedef struct MemoryPool* MemoryPoolRef;

/* create memory pool
   each block size is 'size' */
MemoryPoolRef memory_pool_ctor(size_t size);
/* destroy memory pool */
void memory_pool_dtor(MemoryPoolRef* ppool);

#endif  /* KMC_C89_COMPILER_MEMORY_POOL_H */
