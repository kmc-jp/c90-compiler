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

TEST_F(StringTest, copy) {
  const char * const data = "abcde"
  const size_t length = sizeof(data) / sizeof(char) - 1;
  stringRef v2(data);

  copy(v, v2);
  ASSERT_TRUE(string_data(v) != NULL);
  EXPECT_STREQ(data, string_data(v));
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_size(v));
  EXPECT_LE(length, string_capacity(v));
  string_dtor(&v2);
}

TEST_F(StringTest, assign) {
  const char * const data = "abcde"
  const size_t length = sizeof(data) / sizeof(char) - 1;

  string_assign(v, data);
  ASSERT_TRUE(string_data(v) != NULL);
  EXPECT_STREQ(data, string_data(v));
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_size(v));
  EXPECT_LE(length, string_capacity(v));
}

TEST_F(StringTest, clear) {
  const char * const data = "abcde"
  string_assign(v, data);

  string_clear(v);
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, insert) {
  const char * const data1 = "abcij";
  const char * const data2 = "defgh";
  const char * const data3 = "abcdefghijj";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_insert(v, 3, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1 + length2, string_size(v));
  EXPECT_STREQ(data3, string_data(v));
}

TEST_F(StringTest, erase) {
  const char * const data1 = "abcjihgfde"
  const char * const data2 = "abcde"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_erase(v, 3, 5);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_size(v));
  EXPECT_STREQ(data2, string_data(v));
  
  string_erase(v, 0, 5);
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, push_back) {
  const char * const data = "abcjihgfde"
  const size_t length = sizeof(data) / sizeof(char) - 1;
  size_t i = 0;

  for (i = 0; i < length; ++i) {
    string_push_back(v, data[i]);
  }
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_size(v));
  EXPECT_STREQ(data, string_data(v));
}

TEST_F(StringTest, pop_back) {
  const char * const data1 = "abcdefghij"
  const char * const data2 = "abcde"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data);
  size_t i = 0;

  for (i = 0; i < length1 - length2; ++i) {
    string_pop_back(v);
  }
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_size(v));
  EXPECT_STREQ(data2, string_data(v));
  for (i = 0; i < length2; ++i) {
    string_pop_back(v);
  }
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, append) {
  const char * const data1 = "abcij";
  const char * const data2 = "defgh";
  const char * const data3 = "abcdefghijj";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;

  string_append(v, data1);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_size(v));
  EXPECT_STREQ(data1, string_data(v));

  string_append(v1, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1 + length2, string_size(v));
  EXPECT_STREQ(data3, string_data(v));
}

TEST_F(StringTest, string_compare){
  const StringRef[] vs = {"", "a", "ab", "aba", "abc", "c"};
  const int count = 6;
  int i = 0; j = 1, result = 0;
  for (i = 0; i < count ; ++i) {
    for (j = 0 ; j < count ; ++i) {
      result = string_compare(vs[i], vs[j]);
      if (i < j){
        EXPECT_LT(0, result);
      } else if (i > j) {
        EXPECT_GT(0, result);
      } else {
        EXPECT_EQ(0, result);
      }
    }
  }
  for (i = 0; i < count ; ++i) {
    string_dtor(&vs[i]);
  }
}

TEST_F(StringTest, replace) {
  const char data1[] = "abcdeghij";
  const char data2[] = "xyz"
  const int data3[] = "abcxyzhij"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_replace(v, 3, length2, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_size(v));
  EXPECT_STREQ(data3, string_data(v))
}

TEST_F(StringTest, substr) {
  const char data1[] = "abcxyzhij";
  const char data2[] = "xyz"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  StringRef v2 = string_substr(v, 3, length2);
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length2, string_size(v2));
  EXPECT_STREQ(data2, string_data(v2))

  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_size(v));
  EXPECT_STREQ(data1, string_data(v))
}

TEST_F(StringTest, copy_to) {
  const char data1[] = "abcxyzhij";
  const char data2[] = "xyz"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  const char dst[] = "\0\0\0";
  string_assign(v, data1);

  string_copy_to(v, dst, length2, 3);
  EXPECT_STREQ(data2, dst)

  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_size(v));
  EXPECT_STREQ(data1, string_data(v))
}

TEST_F(StringTest, swap) {
  const char data1[] = "abcde";
  const char data2[] = "xyz"
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  StringRef v2 = string_ctor(data2);
  string_assign(v, data1);

  string_swap(v, v2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_size(v));
  EXPECT_STREQ(data2, string_data(v))
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length1, string_size(v2));
  EXPECT_STREQ(data1, string_data(v2))

  string_dtor(&v2);
}

