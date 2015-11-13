#include "memory_pool.h"

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
