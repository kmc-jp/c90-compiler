#ifndef INCLUDE_GUARD_UUID_CE8F872C_1C85_4BD9_BA55_DCCB9DFCA5FD
#define INCLUDE_GUARD_UUID_CE8F872C_1C85_4BD9_BA55_DCCB9DFCA5FD

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

#endif  /* INCLUDE_GUARD_UUID_CE8F872C_1C85_4BD9_BA55_DCCB9DFCA5FD */
