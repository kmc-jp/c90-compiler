extern "C" {
#include "string.h"
}
#include "gtest/gtest.h"

class StringTest : public ::testing::Test {
 protected:
  StringTest() : v(string_ctor(NULL)) {}
  ~StringTest() {
    string_dtor(&v);
  }
  StringRef v;
};
