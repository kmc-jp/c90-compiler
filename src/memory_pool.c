#include "memory_pool.h"
#include <assert.h>

typedef struct MemoryPoolBlock* MemoryPoolBlockRef;
typedef struct MemoryPoolLarge* MemoryPoolLargeRef;

struct MemoryPoolBlock {
  byte* begin_;
  byte* end_;
  MemoryPoolBlockRef next_;
  size_t failed_;
};

struct MemoryPoolLarge {
  void* data_;
  MemoryPoolLargeRef prev_;
};

struct MemoryPool {
  MemoryPoolBlockRef block_;
  MemoryPoolBlockRef current_;
  MemoryPoolLargeRef large_;
  size_t max_;
};

static const size_t FAILED_THRESHOLD = 4;

static MemoryPoolBlockRef memory_pool_block_ctor(size_t data_size) {
  const size_t header_size = sizeof(struct MemoryPoolBlock);
  const size_t block_size = data_size + header_size;
  byte* const block_data = safe_array_malloc(byte, block_size);
  const MemoryPoolBlockRef block = (MemoryPoolBlockRef)block_data;
  block->begin_ = block_data + header_size;
  block->end_ = block_data + block_size;
  block->next_ = NULL;
  block->failed_ = 0;
  return block;
}
static void memory_pool_block_dtor(MemoryPoolBlockRef block) {
  if (block) {
    memory_pool_block_dtor(block->next_);
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
static void* palloc_from_block(MemoryPoolBlockRef block,
                               size_t size, size_t alignment) {
  const size_t rest = block->end_ - block->begin_;
  const size_t offset = align_offset(block->begin_, alignment);
  if (rest < offset + size) {
    ++block->failed_;
    return NULL;
  } else {
    byte* const data = block->begin_ + offset;
    block->begin_ = data + size;
    return data;
  }
}
static void* palloc_from_large(MemoryPoolRef pool, size_t size) {
  const MemoryPoolLargeRef large = memory_pool_large_ctor(size);
  large->prev_ = pool->large_;
  pool->large_ = large;
  return large->data_;
}

MemoryPoolRef memory_pool_ctor(size_t size) {
  const size_t header_size = sizeof(struct MemoryPoolBlock);
  const size_t block_size = MAX(size, header_size * 2);
  const size_t data_size = block_size - header_size;
  const MemoryPoolRef pool = safe_malloc(struct MemoryPool);
  pool->block_ = memory_pool_block_ctor(data_size);
  pool->current_ = pool->block_;
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

void* palloc_impl(MemoryPoolRef pool, size_t size, size_t alignment) {
  assert(pool);
  assert(0 < size);
  assert(is_power_of_two(alignment));
  if (size < pool->max_) {
    MemoryPoolBlockRef iter = pool->current_;
    byte* data = NULL;
    for (; !data && iter; iter = iter->next_) {
      data = palloc_from_block(iter, size, alignment);
      if (!data && !iter->next_) {
        iter = iter->next_ = memory_pool_block_ctor(pool->max_);
        data = palloc_from_block(iter, size, alignment);
      }
    }
    for (iter = pool->current_; iter->next_; iter = iter->next_) {
      if (FAILED_THRESHOLD < iter->failed_) {
        pool->current_ = iter->next_;
      } else {
        break;
      }
    }
    if (data) {
      return data;
    }
  }
  return palloc_from_large(pool, size);
}
