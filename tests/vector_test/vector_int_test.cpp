extern "C" {
#include "vector_int.h"
}
#include "gtest/gtest.h"

#define VECINT(function) VECTORFUNC(int, function)

TEST(VectorIntTest, ctor) {
  VECTORREF(int) v = VECINT(ctor)();
  EXPECT_TRUE(VECINT(empty)(v));
  VECINT(dtor)(&v);
}
