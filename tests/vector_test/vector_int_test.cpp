extern "C" {
#include "vector_int.h"
}
#include "gtest/gtest.h"

#define VECINT(function) VECTORFUNC(int, function)

class VectorIntTest : public ::testing::Test {
 protected:
  VectorIntTest() : v(VECINT(ctor)()) {}
  ~VectorIntTest() {
    VECINT(dtor)(&v);
  }
  VECTORREF(int) v;
};

TEST_F(VectorIntTest, ctor) {
  EXPECT_EQ(NULL, VECINT(data)(v));
  EXPECT_EQ(NULL, VECINT(begin)(v));
  EXPECT_EQ(NULL, VECINT(end)(v));
  EXPECT_TRUE(VECINT(empty)(v));
  EXPECT_EQ(0U, VECINT(size)(v));
  EXPECT_EQ(0U, VECINT(capacity)(v));
}

TEST_F(VectorIntTest, dtor) {
  VECTORREF(int) vec = VECINT(ctor)();
  VECINT(dtor)(&vec);
  EXPECT_EQ(NULL, vec);
}

TEST_F(VectorIntTest, copy) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VECTORREF(int) v2 = VECINT(ctor)();
  VECINT(assign)(v, data, count);
  VECINT(copy)(v2, v);
  ASSERT_TRUE(VECINT(data)(v2) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v2)[i]);
  }
  EXPECT_FALSE(VECINT(empty)(v2));
  EXPECT_EQ(count, VECINT(size)(v2));
  EXPECT_LE(count, VECINT(capacity)(v2));
}

TEST_F(VectorIntTest, assign) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VECINT(assign)(v, data, count);
  ASSERT_TRUE(VECINT(data)(v) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count, VECINT(size)(v));
  EXPECT_LE(count, VECINT(capacity)(v));
}
