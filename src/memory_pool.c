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

static MemoryPoolBlockRef memory_pool_block_ctor(size_t data_size) {
  const size_t header_size = sizeof(struct MemoryPoolBlock);
  const size_t block_size = data_size + header_size;
  byte* const block_data = safe_array_malloc(byte, block_size);
  const MemoryPoolBlockRef block = (MemoryPoolBlockRef)block_data;
  block->begin_ = block_data + header_size;
  block->end_ = block_data + block_size;
  block->prev_ = NULL;
  return block;
}
static void memory_pool_block_dtor(MemoryPoolBlockRef block) {
  if (block) {
    memory_pool_block_dtor(block->prev_);
    safe_free(block);
  }
}
static MemoryPoolLargeRef memory_pool_large_ctor(size_t data_size) {
  const MemoryPoolLargeRef large = safe_malloc(struct MemoryPoolLarge);
  large->data_ = safe_array_malloc(byte, data_size);
  large->prev_ = NULL;
  return large;
}
static void memory_pool_large_dtor(MemoryPoolLargeRef large) {
  if (large) {
    memory_pool_large_dtor(large->prev_);
    safe_free(large->data_);
    safe_free(large);
  }
}

MemoryPoolRef memory_pool_ctor(size_t size) {
  const size_t header_size = sizeof(struct MemoryPoolBlock);
  const size_t block_size = MAX(size, header_size * 3);
  const size_t data_size = block_size - header_size;
  const MemoryPoolRef pool = safe_malloc(struct MemoryPool);
  pool->block_ = memory_pool_block_ctor(data_size);
  pool->large_ = NULL;
  pool->max_ = data_size;
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
