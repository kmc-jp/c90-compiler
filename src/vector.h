#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

#include <assert.h>
#include <stdlib.h>

typedef signed char bool;

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)

/* template macro */
#define TEMPLATE(type, identifier) CONCAT(WITHBAR(identifier), WITHBAR(type))
#define VECTOR(type) TEMPLATE(type, Vector)
#define VECTORREF(type) TEMPLATE(type, VectorRef)
#define VECTORFUNC(type, function) TEMPLATE(CONCAT(Vector, function), type)
#define VECTOR_GLOBAL(type) CONCAT(global_, TEMPLATE(type, VectorMethods))
#define VECTOR_METHOD(type, function) VECTOR_GLOBAL(type).WITHBAR(function)

#define DECLARE_VECTOR(Type)                                            \
  typedef void (*TEMPLATE(Type, CtorMethod))(Type* value);              \
  typedef void (*TEMPLATE(Type, DtorMethod))(Type* value);              \
  typedef void (*TEMPLATE(Type, CopyMethod))(Type* dst, Type* src);     \
                                                                        \
  /* special member functions */                                        \
  struct TEMPLATE(Type, VectorMethods) {                                \
    TEMPLATE(Type, CtorMethod) WITHBAR(ctor);                           \
    TEMPLATE(Type, DtorMethod) WITHBAR(dtor);                           \
    TEMPLATE(Type, CopyMethod) WITHBAR(copy);                           \
  };                                                                    \
  extern struct TEMPLATE(Type, VectorMethods) VECTOR_GLOBAL(Type);      \
                                                                        \
  /* first of all, you must initialize special member functions */      \
  void VECTORFUNC(Type, Initialize)(TEMPLATE(Type, CtorMethod) ctor,    \
                                    TEMPLATE(Type, DtorMethod) dtor,    \
                                    TEMPLATE(Type, CopyMethod) copy);   \
                                                                        \
  /* vector of Type */                                                  \
  struct VECTOR(Type) {                                                 \
    Type* start_;  /* first data */                                     \
    Type* finish_;  /* last data */                                     \
    Type* end_;  /* end of storage */                                   \
  };                                                                    \
  /* reference to vector of Type */                                     \
  typedef struct VECTOR(Type)* VECTORREF(Type);                         \
                                                                        \
  /* constructor */                                                     \
  VECTORREF(Type) VECTORFUNC(Type, Ctor)(void);                         \
  /* destructor */                                                      \
  void VECTORFUNC(Type, Dtor)(VECTORREF(Type)* pthis);                  \
  /* operator= */                                                       \
  void VECTORFUNC(Type, Copy)(VECTORREF(Type) this,                     \
                              VECTORREF(Type) src);                     \
  /* assign */                                                          \
  void VECTORFUNC(Type, Assign)(VECTORREF(Type) this,                   \
                                Type* data, size_t count);              \
  /* data */                                                            \
  Type* VECTORFUNC(Type, Data)(VECTORREF(Type) this);                   \
  /* begin */                                                           \
  Type* VECTORFUNC(Type, Begin)(VECTORREF(Type) this);                  \
  /* end */                                                             \
  Type* VECTORFUNC(Type, End)(VECTORREF(Type) this);                    \
  /* empty */                                                           \
  bool VECTORFUNC(Type, Empty)(VECTORREF(Type) this);                   \
  /* size */                                                            \
  size_t VECTORFUNC(Type, Size)(VECTORREF(Type) this);                  \
  /* reserve */                                                         \
  void VECTORFUNC(Type, Reserve)(VECTORREF(Type) this, size_t size);    \
  /* capacity */                                                        \
  size_t VECTORFUNC(Type, Capacity)(VECTORREF(Type) this);              \
  /* clear */                                                           \
  void VECTORFUNC(Type, Clear)(VECTORREF(Type) this);                   \
  /* insert */                                                          \
  /* insert 'count' elements in data                                    \
     to the position indexed by 'pos' */                                \
  void VECTORFUNC(Type, Insert)(VECTORREF(Type) this,                   \
                                size_t pos, Type* data, size_t count);  \
  /* erase */                                                           \
  /* remove consecutive 'count' elements                                \
     whose head is indexed by 'pos' */                                  \
  void VECTORFUNC(Type, Erase)(VECTORREF(Type) this,                    \
                               size_t pos, size_t count);               \
  /* push_back */                                                       \
  void VECTORFUNC(Type, Push)(VECTORREF(Type) this, Type* value);       \
  /* pop_back */                                                        \
  /* calling pop_back on empty vector is undefined */                   \
  void VECTORFUNC(Type, Pop)(VECTORREF(Type) this);                     \
  /* resize */                                                          \
  /* append copies of 'value' when extension */                         \
  void VECTORFUNC(Type, Resize)(VECTORREF(Type) this,                   \
                                size_t size, Type* value);              \
  /* swap */                                                            \
  void VECTORFUNC(Type, Swap)(VECTORREF(Type) lhs,                      \
                              VECTORREF(Type) rhs);                     \

#define DEFINE_VECTOR(Type)                                             \
  struct TEMPLATE(Type, VectorMethods) VECTOR_GLOBAL(Type);             \
                                                                        \
  void VECTORFUNC(Type, Initialize)(                                    \
      TEMPLATE(Type, CtorMethod) ctor,                                  \
      TEMPLATE(Type, DtorMethod) dtor,                                  \
      TEMPLATE(Type, CopyMethod) copy) {                                \
    VECTOR_METHOD(Type, ctor) = ctor;                                   \
    VECTOR_METHOD(Type, dtor) = dtor;                                   \
    VECTOR_METHOD(Type, copy) = copy;                                   \
  }                                                                     \
                                                                        \
  void VECTORFUNC(Type, Free)(VECTORREF(Type) this) {                   \
    free(this->start_);                                                 \
  }                                                                     \
  void VECTORFUNC(Type, Nullify)(VECTORREF(Type) this) {                \
    this->start_ = this->finish_ = this->end_ = NULL;                   \
  }                                                                     \
  Type* VECTORFUNC(Type, SetEnd)(VECTORREF(Type) this, Type* end) {     \
    return this->finish_ = end;                                         \
  }                                                                     \
  void VECTORFUNC(Type, MoveUp)(Type* head, Type* tail, size_t count) { \
    if (0 < count) {                                                    \
      Type* src = tail;                                                 \
      Type* dst = tail + count;                                         \
      for (; src != head; --dst, --src) {                               \
        VECTOR_METHOD(Type, copy)(dst - 1, src - 1);                    \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, MoveDown)(                                      \
      Type* head, Type* tail, size_t count) {                           \
    if (0 < count) {                                                    \
      Type* src = head;                                                 \
      Type* dst = head - count;                                         \
      for (; src != tail; ++dst, ++src) {                               \
        VECTOR_METHOD(Type, copy)(dst, src);                            \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, RangeCtorCopy)(                                 \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, RangeCtorFill)(                                 \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, RangeCtor)(Type* head, Type* tail) {            \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, RangeDtor)(Type* head, Type* tail) {            \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, dtor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, RangeCopy)(                                     \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  /* this->start_ must not be allocated */                              \
  void VECTORFUNC(Type, New)(VECTORREF(Type) this,                      \
                             size_t size, Type* data, size_t count) {   \
    const size_t capacity = EnoughCapacity(size);                       \
    this->start_ = (Type*)malloc(sizeof(Type) * capacity);              \
    this->finish_ = this->start_ + count;                               \
    this->end_ = this->start_ + capacity;                               \
    VECTORFUNC(Type, RangeCtorCopy)(this->start_, this->finish_, data); \
  }                                                                     \
                                                                        \
  VECTORREF(Type) VECTORFUNC(Type, Ctor)(void) {                        \
    VECTORREF(Type) this =                                              \
        (VECTORREF(Type))malloc(sizeof(struct VECTOR(Type)));           \
    VECTORFUNC(Type, Nullify)(this);                                    \
    return this;                                                        \
  }                                                                     \
  void VECTORFUNC(Type, Dtor)(VECTORREF(Type)* pthis) {                 \
    assert(pthis && *pthis);                                            \
    VECTORFUNC(Type, Clear)(*pthis);                                    \
    VECTORFUNC(Type, Free)(*pthis);                                     \
    free(*pthis);                                                       \
    *pthis = NULL;                                                      \
  }                                                                     \
  void VECTORFUNC(Type, Copy)(VECTORREF(Type) this,                     \
                              VECTORREF(Type) src) {                    \
    assert(this && src);                                                \
    VECTORFUNC(Type, Assign)(this, VECTORFUNC(Type, Data)(src),         \
                             VECTORFUNC(Type, Size)(src));              \
  }                                                                     \
  void VECTORFUNC(Type, Assign)(VECTORREF(Type) this,                   \
                                Type* data, size_t count) {             \
    assert(this);                                                       \
    assert(count == 0 || data);                                         \
    if (VECTORFUNC(Type, Capacity)(this) < count) {                     \
      VECTORFUNC(Type, Clear)(this);                                    \
      VECTORFUNC(Type, Reserve)(this, count);                           \
    }                                                                   \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, Begin)(this);                \
      Type* const end = VECTORFUNC(Type, End)(this);                    \
      Type* const new_end =                                             \
          VECTORFUNC(Type, SetEnd)(this, begin + count);                \
      if (count < VECTORFUNC(Type, Size)(this)) {                       \
        VECTORFUNC(Type, RangeCopy)(begin, new_end, data);              \
        VECTORFUNC(Type, RangeDtor)(new_end, end);                      \
      } else {                                                          \
        VECTORFUNC(Type, RangeCtor)(end, new_end);                      \
        VECTORFUNC(Type, RangeCopy)(begin, new_end, data);              \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  Type* VECTORFUNC(Type, Data)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, Begin)(VECTORREF(Type) this) {                 \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, End)(VECTORREF(Type) this) {                   \
    assert(this);                                                       \
    return this->finish_;                                               \
  }                                                                     \
  bool VECTORFUNC(Type, Empty)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    return this->start_ == this->finish_;                               \
  }                                                                     \
  size_t VECTORFUNC(Type, Size)(VECTORREF(Type) this) {                 \
    assert(this);                                                       \
    return this->finish_ - this->start_;                                \
  }                                                                     \
  void VECTORFUNC(Type, Reserve)(VECTORREF(Type) this, size_t size) {   \
    assert(this);                                                       \
    if (VECTORFUNC(Type, Capacity)(this) < size) {                      \
      const size_t old_size = VECTORFUNC(Type, Size)(this);             \
      if (old_size == 0) {                                              \
        VECTORFUNC(Type, Free)(this);                                   \
        VECTORFUNC(Type, New)(this, size, NULL, 0);                     \
      } else {                                                          \
        VECTORREF(Type) buffer = VECTORFUNC(Type, Ctor)();              \
        VECTORFUNC(Type, New)(buffer, size,                             \
                              VECTORFUNC(Type, Data)(this), old_size);  \
        VECTORFUNC(Type, Swap)(this, buffer);                           \
        VECTORFUNC(Type, Dtor)(&buffer);                                \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  size_t VECTORFUNC(Type, Capacity)(VECTORREF(Type) this) {             \
    assert(this);                                                       \
    return this->end_ - this->start_;                                   \
  }                                                                     \
  void VECTORFUNC(Type, Clear)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, Begin)(this);                \
      Type* const end = VECTORFUNC(Type, End)(this);                    \
      VECTORFUNC(Type, SetEnd)(this, begin);                            \
      VECTORFUNC(Type, RangeDtor)(begin, end);                          \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Insert)(VECTORREF(Type) this,                   \
                                size_t pos, Type* data, size_t count) { \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VECTORFUNC(Type, Size)(this);                 \
      assert(pos <= size);                                              \
      assert(count == 0 || data);                                       \
      VECTORFUNC(Type, Reserve)(this, size + count);                    \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, Begin)(this);              \
        Type* const end = VECTORFUNC(Type, End)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, SetEnd)(this, end + count);                \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, RangeCtor)(end, new_end);                      \
        VECTORFUNC(Type, MoveUp)(head, end, count);                     \
        VECTORFUNC(Type, RangeCopy)(head, tail, data);                  \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Erase)(VECTORREF(Type) this,                    \
                               size_t pos, size_t count) {              \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VECTORFUNC(Type, Size)(this);                 \
      assert(pos + count <= size);                                      \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, Begin)(this);              \
        Type* const end = VECTORFUNC(Type, End)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, SetEnd)(this, end - count);                \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, MoveDown)(tail, end, count);                   \
        VECTORFUNC(Type, RangeDtor)(new_end, end);                      \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Push)(VECTORREF(Type) this, Type* value) {      \
    assert(this && value);                                              \
    VECTORFUNC(Type, Reserve)(this, VECTORFUNC(Type, Size)(this) + 1);  \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, End)(this);                    \
      Type* const new_end = VECTORFUNC(Type, SetEnd)(this, end + 1);    \
      VECTORFUNC(Type, RangeCtorCopy)(end, new_end, value);             \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Pop)(VECTORREF(Type) this) {                    \
    assert(this);                                                       \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, End)(this);                    \
      Type* const new_end = VECTORFUNC(Type, SetEnd)(this, end - 1);    \
      VECTORFUNC(Type, RangeDtor)(new_end, end);                        \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Resize)(VECTORREF(Type) this,                   \
                                size_t size, Type* value) {             \
    assert(this);                                                       \
    {                                                                   \
      const size_t old_size = VECTORFUNC(Type, Size)(this);             \
      if (old_size < size) {                                            \
        assert(value);                                                  \
        VECTORFUNC(Type, Reserve)(this, size);                          \
      }                                                                 \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, Begin)(this);              \
        Type* const end = VECTORFUNC(Type, End)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, SetEnd)(this, begin + size);               \
        if (old_size < size) {                                          \
          VECTORFUNC(Type, RangeCtorFill)(end, new_end, value);         \
        } else {                                                        \
          VECTORFUNC(Type, RangeDtor)(new_end, end);                    \
        }                                                               \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, Swap)(VECTORREF(Type) lhs,                      \
                              VECTORREF(Type) rhs) {                    \
    assert(lhs && rhs);                                                 \
    {                                                                   \
      struct VECTOR(Type) tmp = *lhs;                                   \
      *lhs = *rhs;                                                      \
      *rhs = tmp;                                                       \
    }                                                                   \
  }                                                                     \

/* size <= capacity && capacity == pow(2, n) */
size_t EnoughCapacity(size_t size);

#endif  /* KMC_C89_COMPILER_VECTOR_H */
