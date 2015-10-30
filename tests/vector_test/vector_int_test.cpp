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
