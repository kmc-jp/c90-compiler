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
