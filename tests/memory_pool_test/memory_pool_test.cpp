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

TEST_F(MemoryPoolTest, ctor_and_dtor) {
  MemoryPoolRef pool = memory_pool_ctor(0);
  EXPECT_TRUE(NULL != pool);
  memory_pool_dtor(&pool);
  EXPECT_EQ(NULL, pool);
}
