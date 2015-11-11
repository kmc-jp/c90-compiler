#include "gtest/gtest.h"
extern "C" {
#include "string.h"
}

class StringEnvironment {
  virtual void SetUp() {
    INITIALIZE_DEFAULT_METHODS(int);
  }
};

GTEST_API_ int main(int argc, char **argv) {
  ::testing::AddGlobalTestEnvironment(new StringEnvironment);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
