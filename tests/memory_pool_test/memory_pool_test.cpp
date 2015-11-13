#include "gtest/gtest.h"
extern "C" {
#include "memory_pool.h"
}

namespace detail {
template <typename T>
class align_of {
  struct inner {
    char a;
    T b;
  };
 public:
  static const size_t value = MIN(sizeof(T), offsetof(inner, b));
};
}

#define ALIGNOF(type)                           \
  detail::align_of<type>::value

#define IS_ALIGNED(type, ptr)                   \
  ((size_t)(ptr) % ALIGNOF(type) == 0)

class MemoryPoolTest : public ::testing::Test {
 protected:
  MemoryPoolTest() : p(memory_pool_ctor(1024)) {}
  ~MemoryPoolTest() {
    memory_pool_dtor(&p);
  }
  MemoryPoolRef p;
};

TEST_F(MemoryPoolTest, ctor_and_dtor) {
  MemoryPoolRef pool = memory_pool_ctor(0);
  EXPECT_TRUE(NULL != pool);
  memory_pool_dtor(&pool);
  EXPECT_EQ(NULL, pool);
}

TEST_F(MemoryPoolTest, strings) {
  const char* const expected =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i = 0;
  int j = 0;
  char** const ptrs = palloc(char*, p, 100);
  for (i = 0; i < 100; ++i) {
    char* const str = ptrs[i] = palloc(char, p, 64);
    EXPECT_TRUE(IS_ALIGNED(char, str));
    for (j = 0; j < 10; ++j) {
      str[j] = '0' + j;
    }
    for (j = 0; j < 26; ++j) {
      str[j + 10] = 'a' + j;
    }
    for (j = 0; j < 26; ++j) {
      str[j + 36] = 'A' + j;
    }
    for (j = 62; j < 64; ++j) {
      str[j] = '\0';
    }
    EXPECT_STREQ(expected, str);
  }
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}

TEST_F(MemoryPoolTest, built_in_types) {
  bool* b =
      palloc(bool, p, 1);
  *b = true;
  char* c =
      palloc(char, p, 2);
  *c = 2;
  signed char* sc =
      palloc(signed char, p, 3);
  *sc = 3;
  unsigned char* uc =
      palloc(unsigned char, p, 5);
  *uc = 5;
  short* s =
      palloc(short, p, 7);
  *s = 7;
  unsigned short* us =
      palloc(unsigned short, p, 11);
  *us = 11;
  int* i =
      palloc(int, p, 13);
  *i = 13;
  unsigned int* ui =
      palloc(unsigned int, p, 17);
  *ui = 17;
  long* l =
      palloc(long, p, 19);
  *l = 19;
  unsigned long* ul =
      palloc(unsigned long, p, 23);
  *ul = 23;
  long long* ll =
      palloc(long long, p, 29);
  *ll = 29;
  unsigned long long* ull =
      palloc(unsigned long long, p, 31);
  *ull = 31;
  float* f =
      palloc(float, p, 37);
  *f = 37;
  double* d =
      palloc(double, p, 41);
  *d = 41;
  long double* ld =
      palloc(long double, p, 43);
  *ld = 43;
  size_t* st =
      palloc(size_t, p, 47);
  *st = 47;
  ptrdiff_t* pt =
      palloc(ptrdiff_t, p, 53);
  *pt = 53;

  EXPECT_EQ(true, *b);
  EXPECT_EQ((char)2, *c);
  EXPECT_EQ((signed char)3, *sc);
  EXPECT_EQ((unsigned char)5, *uc);
  EXPECT_EQ((short)7, *s);
  EXPECT_EQ((unsigned short)11, *us);
  EXPECT_EQ((int)13, *i);
  EXPECT_EQ((unsigned int)17, *ui);
  EXPECT_EQ((long)19, *l);
  EXPECT_EQ((unsigned long)23, *ul);
  EXPECT_EQ((long long)29, *ll);
  EXPECT_EQ((unsigned long long)31, *ull);
  EXPECT_EQ((float)37, *f);
  EXPECT_EQ((double)41, *d);
  EXPECT_EQ((long double)43, *ld);
  EXPECT_EQ((size_t)47, *st);
  EXPECT_EQ((ptrdiff_t)53, *pt);

  EXPECT_TRUE(IS_ALIGNED(bool, b));
  EXPECT_TRUE(IS_ALIGNED(char, c));
  EXPECT_TRUE(IS_ALIGNED(signed char, sc));
  EXPECT_TRUE(IS_ALIGNED(unsigned char, uc));
  EXPECT_TRUE(IS_ALIGNED(short, s));
  EXPECT_TRUE(IS_ALIGNED(unsigned short, us));
  EXPECT_TRUE(IS_ALIGNED(int, i));
  EXPECT_TRUE(IS_ALIGNED(unsigned int, ui));
  EXPECT_TRUE(IS_ALIGNED(long, l));
  EXPECT_TRUE(IS_ALIGNED(unsigned long, ul));
  EXPECT_TRUE(IS_ALIGNED(long long, ll));
  EXPECT_TRUE(IS_ALIGNED(unsigned long long, ull));
  EXPECT_TRUE(IS_ALIGNED(float, f));
  EXPECT_TRUE(IS_ALIGNED(double, d));
  EXPECT_TRUE(IS_ALIGNED(long double, ld));
  EXPECT_TRUE(IS_ALIGNED(size_t, st));
  EXPECT_TRUE(IS_ALIGNED(ptrdiff_t, pt));
}

struct S {
  char c[29];
  short s[23];
  int i[19];
  long l[17];
  long long ll[13];
  float f[11];
  double d[7];
  long double ld[5];
  size_t st[3];
  ptrdiff_t pt[2];
};

TEST_F(MemoryPoolTest, struct_types) {
  int i = 0;
  int j = 0;
  S** ptrs = palloc(S*, p, 100);
  for (i = 0; i < 100; ++i) {
    ptrs[i] = palloc(S, p, 100);
    EXPECT_TRUE(IS_ALIGNED(S, ptrs[i]));
  }
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}

union U {
  char c[29];
  short s[23];
  int i[19];
  long l[17];
  long long ll[13];
  float f[11];
  double d[7];
  long double ld[5];
  size_t st[3];
  ptrdiff_t pt[2];
};

TEST_F(MemoryPoolTest, union_types) {
  int i = 0;
  int j = 0;
  U** ptrs = palloc(U*, p, 100);
  for (i = 0; i < 100; ++i) {
    ptrs[i] = palloc(U, p, 100);
    EXPECT_TRUE(IS_ALIGNED(U, ptrs[i]));
  }
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}

struct B {
  char c[10101];
  long long ll;
};

TEST_F(MemoryPoolTest, big) {
  int i = 0;
  int j = 0;
  B** ptrs = palloc(B*, p, 100);
  for (i = 0; i < 100; ++i) {
    ptrs[i] = palloc(B, p, 100);
    EXPECT_TRUE(IS_ALIGNED(B, ptrs[i]));
  }
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      EXPECT_NE(ptrs[i], ptrs[j]);
    }
  }
}
