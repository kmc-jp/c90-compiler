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
  EXPECT_TRUE(VECINT(empty)(v));
}
