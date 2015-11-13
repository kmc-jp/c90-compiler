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

TEST_F(MemoryPoolTest, strings) {
  const char* const expected =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i = 0;
  int j = 0;
  char** const ptrs = palloc(char*, p, 100);
  for (i = 0; i < 100; ++i) {
    char* const str = ptrs[i] = palloc(char, p, 64);
    EXPECT_TRUE(IS_ALIGNED(char, str));
    for (j = 0; j < 10; ++j) {
      str[j] = '0' + j;
    }
    for (j = 0; j < 26; ++j) {
      str[j + 10] = 'a' + j;
    }
    for (j = 0; j < 26; ++j) {
      str[j + 36] = 'A' + j;
    }
    for (j = 62; j < 64; ++j) {
      str[j] = '\0';
    }
    EXPECT_STREQ(expected, str);
  }
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}
