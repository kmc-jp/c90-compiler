extern "C" {
#include "vector_int.h"
}
#include "gtest/gtest.h"

TEST(VectorIntTest, ctor) {
  VECTORREF(int) v = VECTORFUNC(int, ctor)();
  EXPECT_TRUE(VECTORFUNC(int, empty)(v));
  VECTORFUNC(int, dtor)(&v);
}
