#include "gtest/gtest.h"
extern "C" {
#include "memory_pool.h"
}

class MemoryPoolTest : public ::testing::Test {
 protected:
  MemoryPoolTest() : p(memory_pool_ctor(1024)) {}
  ~MemoryPoolTest() {
    memory_pool_dtor(&p);
  }
  MemoryPoolRef p;
};
