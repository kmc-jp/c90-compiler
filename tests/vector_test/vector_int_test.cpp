extern "C" {
#include "vector_int.h"
}
#include "gtest/gtest.h"

#define VINT VECTORREF(int)
#define VECINT(function) VECTORFUNC(int, function)

class VectorIntTest : public ::testing::Test {
 protected:
  VectorIntTest() : v(VECINT(ctor)()) {}
  ~VectorIntTest() {
    VECINT(dtor)(&v);
  }
  VINT v;
};

TEST_F(VectorIntTest, ctor) {
  EXPECT_EQ(NULL, VECINT(data)(v));
  EXPECT_EQ(NULL, VECINT(begin)(v));
  EXPECT_EQ(NULL, VECINT(end)(v));
  EXPECT_TRUE(VECINT(empty)(v));
  EXPECT_EQ(0U, VECINT(size)(v));
  EXPECT_EQ(0U, VECINT(capacity)(v));
}

TEST_F(VectorIntTest, dtor) {
  VINT v2 = VECINT(ctor)();
  VECINT(dtor)(&v2);
  EXPECT_EQ(NULL, v2);
}

TEST_F(VectorIntTest, copy) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VINT v2 = VECINT(ctor)();
  VECINT(assign)(v, data, count);
  VECINT(copy)(v2, v);
  ASSERT_TRUE(VECINT(data)(v2) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v2)[i]);
  }
  EXPECT_FALSE(VECINT(empty)(v2));
  EXPECT_EQ(count, VECINT(size)(v2));
  EXPECT_LE(count, VECINT(capacity)(v2));
  VECINT(dtor)(&v2);
}

TEST_F(VectorIntTest, assign) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VECINT(assign)(v, data, count);
  ASSERT_TRUE(VECINT(data)(v) != NULL);
  for (i = 0; i < count; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count, VECINT(size)(v));
  EXPECT_LE(count, VECINT(capacity)(v));
}

TEST_F(VectorIntTest, reserve) {
  const size_t size = 5;
  VECINT(reserve)(v, size);
  EXPECT_TRUE(VECINT(empty)(v));
  EXPECT_LE(size, VECINT(capacity)(v));
}

TEST_F(VectorIntTest, clear) {
  const int data[] = {0, 1, 2, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  VECINT(assign)(v, data, count);
  VECINT(clear)(v);
  EXPECT_TRUE(VECINT(empty)(v));
}

TEST_F(VectorIntTest, insert) {
  const int data1[] = {0, 1, 2, 8, 9};
  const int data2[] = {3, 4, 5, 6, 7};
  const size_t count1 = sizeof(data1) / sizeof(int);
  const size_t count2 = sizeof(data2) / sizeof(int);
  size_t i = 0;
  VECINT(assign)(v, data1, count1);
  VECINT(insert)(v, 3, data2, count2);
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count1 + count2, VECINT(size)(v));
  for (i = 0; i < count1 + count2; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, erase) {
  const int data[] = {0, 1, 2, 9, 8, 7, 6, 5, 3, 4};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VECINT(assign)(v, data, count);
  VECINT(erase)(v, 3, 5);
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(5U, VECINT(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  VECINT(erase)(v, 0, 5);
  EXPECT_TRUE(VECINT(empty)(v));
}

TEST_F(VectorIntTest, push) {
  int value = 0;
  size_t i = 0;
  for (i = 0; i < 10; ++i, ++value) {
    VECINT(push)(v, &value);
  }
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(10U, VECINT(size)(v));
  for (i = 0; i < 10; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, pop) {
  const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  const size_t count = sizeof(data) / sizeof(int);
  size_t i = 0;
  VECINT(assign)(v, data, count);
  for (i = 0; i < 5; ++i) {
    VECINT(pop)(v);
  }
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(5U, VECINT(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  for (i = 0; i < 5; ++i) {
    VECINT(pop)(v);
  }
  EXPECT_TRUE(VECINT(empty)(v));
}

TEST_F(VectorIntTest, resize) {
  size_t i = 0;
  int value = 0;
  VECINT(resize)(v, 5, &value);
  EXPECT_EQ(5U, VECINT(size)(v));
  value = 1;
  VECINT(resize)(v, 10, &value);
  EXPECT_EQ(10U, VECINT(size)(v));
  for (i = 0; i < 5; ++i) {
    EXPECT_EQ(0, VECINT(data)(v)[i]);
  }
  for (i = 5; i < 10; ++i) {
    EXPECT_EQ(1, VECINT(data)(v)[i]);
  }
  VECINT(resize)(v, 3, NULL);
  EXPECT_EQ(3U, VECINT(size)(v));
  for (i = 0; i < 3; ++i) {
    EXPECT_EQ(0, VECINT(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, swap) {
  const int data1[] = {0, 1, 2};
  const int data2[] = {0, 1, 2, 3, 4};
  const size_t count1 = sizeof(data1) / sizeof(int);
  const size_t count2 = sizeof(data2) / sizeof(int);
  size_t i = 0;
  VINT v2 = VECINT(ctor)();
  VECINT(assign)(v, data1, count1);
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count1, VECINT(size)(v));
  for (i = 0; i < count1; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  VECINT(assign)(v2, data2, count2);
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count2, VECINT(size)(v2));
  for (i = 0; i < count2; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v2)[i]);
  }
  VECINT(swap)(v, v2);
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count2, VECINT(size)(v));
  for (i = 0; i < count2; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v)[i]);
  }
  EXPECT_FALSE(VECINT(empty)(v));
  EXPECT_EQ(count1, VECINT(size)(v2));
  for (i = 0; i < count1; ++i) {
    EXPECT_EQ((int)i, VECINT(data)(v2)[i]);
  }
  VECINT(dtor)(&v2);
}
