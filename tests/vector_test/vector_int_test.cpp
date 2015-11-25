#include "gtest/gtest.h"
#include "new-vector.h"

#define VINT VectorRef
#define VINTF(function) CONCAT(vector_, function)

static const size_t SIZE = 100;

class VectorIntTest : public ::testing::Test {
 protected:
  VectorIntTest() : v(VINTF(ctor)()) {
    for (int i = 0; (size_t)i < SIZE; ++i) {
      data[i] = i;
    }
  }
  ~VectorIntTest() {
    VINTF(dtor)(&v);
  }
  VINT v;
  int data[SIZE];
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
  VINT v2 = VINTF(ctor)();
  VINTF(assign)(v, data, SIZE);
  VINTF(copy)(v2, v);
  ASSERT_TRUE(VINTF(data)(v2) != NULL);
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(i, VINTF(data)(v2)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v2));
  EXPECT_EQ(SIZE, VINTF(size)(v2));
  EXPECT_LE(SIZE, VINTF(capacity)(v2));
  VINTF(dtor)(&v2);
}

TEST_F(VectorIntTest, assign) {
  VINTF(assign)(v, data, SIZE);
  ASSERT_TRUE(VINTF(data)(v) != NULL);
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(SIZE, VINTF(size)(v));
  EXPECT_LE(SIZE, VINTF(capacity)(v));
}

TEST_F(VectorIntTest, reserve) {
  const size_t size = 5;
  VINTF(reserve)(v, size);
  EXPECT_TRUE(VINTF(empty)(v));
  EXPECT_LE(size, VINTF(capacity)(v));
}

TEST_F(VectorIntTest, clear) {
  VINTF(assign)(v, data, SIZE);
  VINTF(clear)(v);
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, insert) {
  int data1[SIZE];
  int data2[SIZE];
  size_t index = SIZE / 2;
  for (int i = 0; (size_t)i < index; ++i) {
    data1[i] = i;
  }
  for (int i = index; (size_t)i < SIZE; ++i) {
    data1[i] = i + SIZE;
  }
  for (int i = 0; (size_t)i < SIZE; ++i) {
    data2[i] = i + index;
  }
  VINTF(assign)(v, data1, SIZE);
  VINTF(insert)(v, index, data2, SIZE);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(SIZE * 2, VINTF(size)(v));
  for (int i = 0; (size_t)i < SIZE * 2; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, erase) {
  size_t index = SIZE / 3;
  VINTF(assign)(v, data, SIZE);
  VINTF(erase)(v, index, index);
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(SIZE - index, VINTF(size)(v));
  for (int i = 0; (size_t)i < index; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
  for (int i = index; (size_t)i < SIZE - index; ++i) {
    EXPECT_EQ((int)(i + index), VINTF(data)(v)[i]);
  }
  VINTF(erase)(v, 0, SIZE);
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, push_back) {
  for (int i = 0; (size_t)i < SIZE; ++i) {
    VINTF(push_back)(v, i);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(SIZE, VINTF(size)(v));
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, pop_back) {
  size_t index = SIZE / 2;
  VINTF(assign)(v, data, SIZE);
  for (int i = 0; (size_t)i < SIZE - index; ++i) {
    VINTF(pop_back)(v);
  }
  EXPECT_FALSE(VINTF(empty)(v));
  EXPECT_EQ(index, VINTF(size)(v));
  for (int i = 0; (size_t)i < index; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
  for (int i = 0; (size_t)i < index; ++i) {
    VINTF(pop_back)(v);
  }
  EXPECT_TRUE(VINTF(empty)(v));
}

TEST_F(VectorIntTest, resize) {
  size_t index = SIZE / 2;
  VINTF(assign)(v, data, SIZE);
  VINTF(resize)(v, index, 0);
  EXPECT_EQ(index, VINTF(size)(v));
  VINTF(resize)(v, SIZE, 0);
  EXPECT_EQ(SIZE, VINTF(size)(v));
  for (int i = 0; (size_t)i < index; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
  for (int i = index; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(0, VINTF(data)(v)[i]);
  }
  VINTF(resize)(v, index, 0);
  EXPECT_EQ(index, VINTF(size)(v));
  for (int i = 0; (size_t)i < index; ++i) {
    EXPECT_EQ(i, VINTF(data)(v)[i]);
  }
}

TEST_F(VectorIntTest, swap) {
  int data1[SIZE];
  int data2[SIZE];
  for (int i = 0; (size_t)i < SIZE; ++i) {
    data1[i] = i;
    data2[i] = SIZE - i;
  }
  VINT v1 = VINTF(ctor)();
  VINTF(assign)(v1, data1, SIZE);
  EXPECT_FALSE(VINTF(empty)(v1));
  EXPECT_EQ(SIZE, VINTF(size)(v1));
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(i, VINTF(data)(v1)[i]);
  }
  VINT v2 = VINTF(ctor)();
  VINTF(assign)(v2, data2, SIZE);
  EXPECT_FALSE(VINTF(empty)(v2));
  EXPECT_EQ(SIZE, VINTF(size)(v2));
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ((int)(SIZE - i), VINTF(data)(v2)[i]);
  }
  VINTF(swap)(v1, v2);
  EXPECT_FALSE(VINTF(empty)(v1));
  EXPECT_EQ(SIZE, VINTF(size)(v1));
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ((int)(SIZE - i), VINTF(data)(v1)[i]);
  }
  EXPECT_FALSE(VINTF(empty)(v2));
  EXPECT_EQ(SIZE, VINTF(size)(v2));
  for (int i = 0; (size_t)i < SIZE; ++i) {
    EXPECT_EQ(i, VINTF(data)(v2)[i]);
  }
  VINTF(dtor)(&v1);
  VINTF(dtor)(&v2);
}
