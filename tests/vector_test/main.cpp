#include "gtest/gtest.h"
extern "C" {
#include "use_vector.h"
}

class VectorIntEnvironment : public ::testing::Environment {
  virtual void SetUp() {
    INITIALIZE_DEFAULT_METHODS(int);
  }
};

GTEST_API_ int main(int argc, char **argv) {
  ::testing::AddGlobalTestEnvironment(new VectorIntEnvironment);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
