#include "gtest/gtest.h"
extern "C" {
#include "memory_pool.h"
}

namespace detail {
template <typename T>
class align_of {
  struct inner {
    char a;
    T b;
  };
 public:
  static const size_t value = MIN(sizeof(T), offsetof(inner, b));
};
}

#define ALIGNOF(type)                           \
  detail::align_of<type>::value

#define IS_ALIGNED(type, ptr)                   \
  ((size_t)(ptr) % ALIGNOF(type) == 0)

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
