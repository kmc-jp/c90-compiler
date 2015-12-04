#include "gtest/gtest.h"
#include "new-vector.h"

#define VINT VectorRef
#define VINTF(function) CONCAT(vector_, function)

class VectorIntTest : public ::testing::Test {
 protected:
  VectorIntTest() : v(VINTF(ctor)()) {}
  ~VectorIntTest() {
    VINTF(dtor)(&v);
  }
  VINT v;
};

TEST_F(VectorIntTest, ctor) {
  EXPECT_EQ(NULL, VINTF(data)(v));
  EXPECT_EQ(NULL, VINTF(begin)(v));
  EXPECT_EQ(NULL, VINTF(end)(v));
  EXPECT_TRUE(VINTF(empty)(v));
  EXPECT_EQ(0U, VINTF(size)(v));
  EXPECT_EQ(0U, VINTF(capacity)(v));
}

TEST_F(VectorIntTest, dtor) {
  VINT v2 = VINTF(ctor)();
  VINTF(dtor)(&v2);
  EXPECT_EQ(NULL, v2);
}

TEST_F(VectorIntTest, copy) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VINT v2 = VINTF(ctor)();
  VINTF(assign)(v, data, count);
  VINTF(copy)(v2, v);
  ASSERT_TRUE(VINTF(data)(v2) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v2)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v2));
  EXPECT_EQ(count, VINTF(size)(v2));
  EXPECT_LE(count, VINTF(capacity)(v2));
  VINTF(dtor)(&v2);
}

TEST_F(VectorIntTest, assign) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VINTF(assign)(v, data, count);
  ASSERT_TRUE(VINTF(data)(v) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count, VINTF(size)(v));
  EXPECT_LE(count, VINTF(capacity)(v));
}

TEST_F(VectorIntTest, reserve) {
  const size_t size = 5;
  VINTF(reserve)(v, size);
  EXPECT_TRUE(VINTF(empty)(v));
  EXPECT_LE(size, VINTF(capacity)(v));
}

TEST_F(VectorIntTest, clear) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  VINTF(assign)(v, data, count);
  VINTF(clear)(v);
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, insert) {
  const int data1[] = {0, 1, 2, 8, 9};
  const int data2[] = {3, 4, 5, 6, 7};
  const size_t count1 = sizeof(data1) / sizeof(int);
  const size_t count2 = sizeof(data2) / sizeof(int);
  size_t i = 0;
  VINTF(assign)(v, data1, count1);
  VINTF(insert)(v, 3, data2, count2);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count1 + count2, VINTF(size)(v));
  for (i = 0; i < count1 + count2; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, erase) {
  const int data[] = {0, 1, 2, 9, 8, 7, 6, 5, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VINTF(assign)(v, data, count);
  VINTF(erase)(v, 3, 5);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(5U, VINTF(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
  VINTF(erase)(v, 0, 5);
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, push_back) {
  int value = 0;
  size_t i = 0;
  for (i = 0; i < 10; ++i, ++value) {
    VINTF(push_back)(v, &value);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(10U, VINTF(size)(v));
  for (i = 0; i < 10; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, pop_back) {
  const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VINTF(assign)(v, data, count);
  for (i = 0; i < 5; ++i) {
    VINTF(pop_back)(v);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(5U, VINTF(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
  for (i = 0; i < 5; ++i) {
    VINTF(pop_back)(v);
  }
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, resize) {
  size_t i = 0;
  int value = 0;
  VINTF(resize)(v, 5, &value);
  EXPECT_EQ(5U, VINTF(size)(v));
  value = 1;
  VINTF(resize)(v, 10, &value);
  EXPECT_EQ(10U, VINTF(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ(0, VINTF(data)(v)[i]);
  }
  for (i = 5; i < 10; ++i) {
    EXPECT_EQ(1, VINTF(data)(v)[i]);
  }
  VINTF(resize)(v, 3, NULL);
  EXPECT_EQ(3U, VINTF(size)(v));
  for (i = 0; i < 3; ++i) {
    EXPECT_EQ(0, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, swap) {
  const int data1[] = {0, 1, 2};
  const int data2[] = {0, 1, 2, 3, 4};
  const size_t count1 = sizeof(data1) / sizeof(int);
  const size_t count2 = sizeof(data2) / sizeof(int);
  size_t i = 0;
  VINT v2 = VINTF(ctor)();
  VINTF(assign)(v, data1, count1);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count1, VINTF(size)(v));
  for (i = 0; i < count1; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
  VINTF(assign)(v2, data2, count2);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count2, VINTF(size)(v2));
  for (i = 0; i < count2; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v2)[i]);
  }
  VINTF(swap)(v, v2);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count2, VINTF(size)(v));
  for (i = 0; i < count2; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(count1, VINTF(size)(v2));
  for (i = 0; i < count1; ++i) {
    EXPECT_EQ((int)i, VINTF(data)(v2)[i]);
  }
  VINTF(dtor)(&v2);
}
