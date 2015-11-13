#include "memory_pool.h"
#include <assert.h>

typedef struct MemoryPoolBlock* MemoryPoolBlockRef;
typedef struct MemoryPoolLarge* MemoryPoolLargeRef;

struct MemoryPoolBlock {
  byte* begin_;
  byte* end_;
  MemoryPoolBlockRef prev_;
};

struct MemoryPoolLarge {
  void* data_;
  MemoryPoolLargeRef prev_;
};

struct MemoryPool {
  MemoryPoolBlockRef block_;
  MemoryPoolLargeRef large_;
  size_t max_;
};

static void memory_pool_block_dtor(MemoryPoolBlockRef block) {
  if (block) {
    memory_pool_block_dtor(block->prev_);
    safe_free(block);
  }
}
static void memory_pool_large_dtor(MemoryPoolLargeRef large) {
  UNUSED(large);
}

MemoryPoolRef memory_pool_ctor(size_t size) {
  const size_t header_size = sizeof(struct MemoryPoolBlock);
  const size_t block_size = MAX(size, header_size * 2);
  const MemoryPoolRef pool = safe_malloc(struct MemoryPool);
  byte* const block = safe_array_malloc(byte, block_size);
  pool->block_ = (MemoryPoolBlockRef)block;
  pool->block_->begin_ = block + header_size;
  pool->block_->end_ = block + block_size;
  pool->block_->prev_ = NULL;
  pool->large_ = NULL;
  pool->max_ = block_size - header_size;
  return pool;
}

void memory_pool_dtor(MemoryPoolRef* ppool) {
  assert(ppool);
  if (*ppool) {
    memory_pool_block_dtor((*ppool)->block_);
    memory_pool_large_dtor((*ppool)->large_);
    safe_free(*ppool);
  }
}
