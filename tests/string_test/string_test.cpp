extern "C" {
#include "stdstring.h"
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
}

TEST_F(StringTest, dtor) {
  StringRef v2 = string_ctor(NULL);
  string_dtor(&v2);
  EXPECT_EQ(NULL, v2);
}

TEST_F(StringTest, ctor_with_data) {
  const char data[] = "abcde";
  const size_t length = sizeof(data) / sizeof(char) - 1;
  size_t i = 0;
  StringRef v2 = string_ctor(data);
  EXPECT_STREQ(data, string_data(v2));
  EXPECT_EQ(data[0], string_front(v2));
  EXPECT_EQ(data[length], string_back(v2));
  EXPECT_EQ('\0', *string_begin(v));
  EXPECT_EQ('\0', *string_end(v));
  string_assign(v, data);
  for (i = 0 ; i < length ; ++i) {
    EXPECT_EQ(data[i], string_at(v, i));
  }
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length, string_length(v2));
  EXPECT_LE(length, string_capacity(v2));
  string_dtor(&v2);
}

TEST_F(StringTest, copy) {
  const char data[] = "abcde";
  const size_t length = sizeof(data) / sizeof(char) - 1;
  StringRef v2 = string_ctor(data);

  string_copy(v, v2);
  ASSERT_TRUE(string_data(v) != NULL);
  EXPECT_STREQ(data, string_data(v));
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_length(v));
  EXPECT_LE(length, string_capacity(v));
  string_dtor(&v2);
}

TEST_F(StringTest, assign) {
  const char data[] = "abcde";
  const size_t length = sizeof(data) / sizeof(char) - 1;

  string_assign(v, data);
  ASSERT_TRUE(string_data(v) != NULL);
  EXPECT_STREQ(data, string_data(v));
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_length(v));
  EXPECT_LE(length, string_capacity(v));
}

TEST_F(StringTest, reserve) {
  const size_t length = 5;

  string_reserve(v, length);
  EXPECT_TRUE(string_empty(v));
  EXPECT_LE(length, string_capacity(v));
}

TEST_F(StringTest, shrink_to_fit) {
  const char data[] = "abcde";
  const size_t length = sizeof(data) / sizeof(char) - 1;
  string_assign(v, data);

  string_reserve(v, 20);
  EXPECT_LE(20U, string_capacity(v));

  string_shrink_to_fit(v);
  EXPECT_LE(length, string_capacity(v));
}
TEST_F(StringTest, clear) {
  const char data[] = "abcde";
  string_assign(v, data);

  string_clear(v);
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, insert) {
  const char data1[] = "abcij";
  const char data2[] = "defgh";
  const char data3[] = "abcdefghij";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_insert(v, 3, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1 + length2, string_length(v));
  EXPECT_STREQ(data3, string_data(v));
}

TEST_F(StringTest, erase) {
  const char data1[] = "abcjihgfde";
  const char data2[] = "abcde";
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_erase(v, 3, 5);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_length(v));
  EXPECT_STREQ(data2, string_data(v));

  string_erase(v, 0, 5);
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, push_back) {
  const char data[] = "abcjihgfde";
  const size_t length = sizeof(data) / sizeof(char) - 1;
  size_t i = 0;

  for (i = 0; i < length; ++i) {
    string_push_back(v, data[i]);
  }
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length, string_length(v));
  EXPECT_STREQ(data, string_data(v));
}

TEST_F(StringTest, pop_back) {
  const char data1[] = "abcdefghij";
  const char data2[] = "abcde";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);
  size_t i = 0;

  for (i = 0; i < length1 - length2; ++i) {
    string_pop_back(v);
  }
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_length(v));
  EXPECT_STREQ(data2, string_data(v));
  for (i = 0; i < length2; ++i) {
    string_pop_back(v);
  }
  EXPECT_TRUE(string_empty(v));
}

TEST_F(StringTest, append) {
  const char data1[] = "abcde";
  const char data2[] = "fghij";
  const char data3[] = "abcdefghij";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;

  string_append(v, data1);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_length(v));
  EXPECT_STREQ(data1, string_data(v));

  string_append(v, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1 + length2, string_length(v));
  EXPECT_STREQ(data3, string_data(v));
}

TEST_F(StringTest, string_compare){
  const char * const data[] = {"", "a", "ab", "aba", "abc", "c"};
  const int count = 6;
  StringRef vs[count];
  int i = 0, j = 1, result = 0;
  for (i = 0; i < count ; ++i) {
    vs[i] = string_ctor(data[i]);
  }
  for (i = 0; i < count ; ++i) {
    for (j = 0 ; j < count ; ++j) {
      result = string_compare(vs[i], vs[j]);
      if (i < j){
        EXPECT_GT(0, result);
      } else if (i > j) {
        EXPECT_LT(0, result);
      } else {
        EXPECT_EQ(0, result);
      }
    }
  }
  for (i = 0; i < count ; ++i) {
    string_dtor(vs + i);
  }
}

TEST_F(StringTest, replace) {
  const char data1[] = "abcdeghij";
  const char data2[] = "xyz";
  const char data3[] = "abcxyzhij";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  string_replace(v, 3, length2, data2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_length(v));
  EXPECT_STREQ(data3, string_data(v));
}

TEST_F(StringTest, substr) {
  const char data1[] = "abcxyzhij";
  const char data2[] = "xyz";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  string_assign(v, data1);

  StringRef v2 = string_substr(v, 3, length2);
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length2, string_length(v2));
  EXPECT_STREQ(data2, string_data(v2));

  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_length(v));
  EXPECT_STREQ(data1, string_data(v));
}

TEST_F(StringTest, copy_to) {
  const char data1[] = "abcxyzhij";
  const char data2[] = "xyz";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  char dst[] = "\0\0\0";
  string_assign(v, data1);

  string_copy_to(v, dst, length2, 3);
  EXPECT_STREQ(data2, dst);

  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length1, string_length(v));
  EXPECT_STREQ(data1, string_data(v));
}

TEST_F(StringTest, resize) {
  const char data1[] = "abcd";
  const char data2[] = "abcd\0";
  const char data3[] = "abcd\0\0\0\0\0\0";
  const char data4[] = "abc";
  int i = 0;
  string_assign(v, data1);

  string_resize(v, 5);
  EXPECT_EQ(5U, string_length(v));
  for (i = 0; i <= 5; ++i) {
    EXPECT_EQ(data2[i], string_data(v)[i]);
  }
  string_resize(v, 10);
  EXPECT_EQ(10U, string_length(v));
  for (i = 0; i <= 10; ++i) {
    EXPECT_EQ(data3[i], string_data(v)[i]);
  }
  string_resize(v, 3);
  EXPECT_EQ(3U, string_length(v));
  for (i = 0; i <= 3; ++i) {
    EXPECT_EQ(data4[i], string_data(v)[i]);
  }
}

TEST_F(StringTest, swap) {
  const char data1[] = "abcde";
  const char data2[] = "xyz";
  const size_t length1 = sizeof(data1) / sizeof(char) - 1;
  const size_t length2 = sizeof(data2) / sizeof(char) - 1;
  StringRef v2 = string_ctor(data2);
  string_assign(v, data1);

  string_swap(v, v2);
  EXPECT_FALSE(string_empty(v));
  EXPECT_EQ(length2, string_length(v));
  EXPECT_STREQ(data2, string_data(v));
  EXPECT_FALSE(string_empty(v2));
  EXPECT_EQ(length1, string_length(v2));
  EXPECT_STREQ(data1, string_data(v2));

  string_dtor(&v2);
}

TEST_F(StringTest, find) {
  const char data[] = "abcdefg";
  const char target[] = "def";
  const char missed[] = "dack";
  string_assign(v, data);

  EXPECT_EQ(3U, string_find(v, target));
  EXPECT_EQ(string_npos, string_find(v, missed));
}

TEST_F(StringTest, find_first_of) {
  const char data[] = "abcdefg";
  const char target[] = "fgd";
  const char missed[] = "xyz";
  string_assign(v, data);

  EXPECT_EQ(3U, string_find_first_of(v, target));
  EXPECT_EQ(string_npos, string_find(v, missed));
}

TEST_F(StringTest, find_first_not_of) {
  const char data[] = "abcdefg";
  const char target[] = "cba";
  const char allchars[] = "gfedcba";
  string_assign(v, data);

  EXPECT_EQ(3U, string_find_first_not_of(v, target));
  EXPECT_EQ(string_npos, string_find(v, allchars));
}
