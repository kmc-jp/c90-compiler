#include "gtest/gtest.h"
extern "C" {
#include "string.h"
}

class StringEnvironment : public ::testing::Environment {
  virtual void SetUp() {
  }
};

GTEST_API_ int main(int argc, char **argv) {
  ::testing::AddGlobalTestEnvironment(new StringEnvironment);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
