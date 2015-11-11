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

TEST_F(StringTest, ctor) {
  EXPECT_EQ('\0', *string_data(v));
  EXPECT_EQ('\0', string_front(v));
  EXPECT_EQ('\0', string_back(v));
  EXPECT_EQ('\0', *string_begin(v));
  EXPECT_EQ('\0', *string_end(v));
  EXPECT_TRUE(string_empty(v));
  EXPECT_EQ(0U, string_length(v));
  EXPECT_EQ(0U, string_capasity(v));
}

TEST_F(StringTest, dtor) {
  StringRef v2 = string_ctor();
  string_dtor(&v2);
  EXPECT_EQ(NULL, v2);
}

TEST_F(StringTest, ctor_with_data) {
  const char * const data = "abcde";
  const size_t length = sizeof(data) / sizeof(char) - 1;
  size_t i = 0;
  StringRef v2 = string_ctor(data);
  EXPECT_STREQ(data, string_data(v2));
  EXPECT_EQ(data[0], string_front(v2));
  EXPECT_EQ(data[length], string_back(v2));
  EXPECT_EQ(data[0], *string_begin(v));
  EXPECT_EQ(data[length], *string_end(v));
  string_assign(v, data);
  for (i = 0 ; i < length ; ++i) {
    EXPECT_EQ(data[i], string_at(v, i));
  }
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length, string_length(v2));
  EXPECT_LE(length, string_capasity(v2));
  string_dtor(v2);
}
