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
#define VECTOR_GLOBAL(type) CONCAT(global_, TEMPLATE(type, VectorMethods))
#define VECTOR_METHOD(type, function) VECTOR_GLOBAL(type).WITHBAR(function)
#define VF(function, type) TEMPLATE(type, CONCAT(Vector, function))

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
  void VECTORFUNC(Initialize, Type)(TEMPLATE(Type, CtorMethod) ctor,    \
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
  VECTORREF(Type) VF(Ctor, Type)(void);                                 \
  /* destructor */                                                      \
  void VF(Dtor, Type)(VECTORREF(Type)* pthis);                          \
  /* operator= */                                                       \
  void VF(Copy, Type)(VECTORREF(Type) this, VECTORREF(Type) src);       \
  /* assign */                                                          \
  void VF(Assign, Type)(VECTORREF(Type) this,                           \
                        Type* data, size_t count);                      \
  /* data */                                                            \
  Type* VF(Data, Type)(VECTORREF(Type) this);                           \
  /* begin */                                                           \
  Type* VF(Begin, Type)(VECTORREF(Type) this);                          \
  /* end */                                                             \
  Type* VF(End, Type)(VECTORREF(Type) this);                            \
  /* empty */                                                           \
  bool VF(Empty, Type)(VECTORREF(Type) this);                           \
  /* size */                                                            \
  size_t VF(Size, Type)(VECTORREF(Type) this);                          \
  /* reserve */                                                         \
  void VF(Reserve, Type)(VECTORREF(Type) this, size_t size);            \
  /* capacity */                                                        \
  size_t VF(Capacity, Type)(VECTORREF(Type) this);                      \
  /* clear */                                                           \
  void VF(Clear, Type)(VECTORREF(Type) this);                           \
  /* insert */                                                          \
  /* insert 'count' elements in data                                    \
     to the position indexed by 'pos' */                                \
  void VF(Insert, Type)(VECTORREF(Type) this,                           \
                        size_t pos, Type* data, size_t count);          \
  /* erase */                                                           \
  /* remove consecutive 'count' elements                                \
     whose head is indexed by 'pos' */                                  \
  void VF(Erase, Type)(VECTORREF(Type) this,                            \
                       size_t pos, size_t count);                       \
  /* push_back */                                                       \
  void VF(Push, Type)(VECTORREF(Type) this, Type* value);               \
  /* pop_back */                                                        \
  /* calling pop_back on empty vector is undefined */                   \
  void VF(Pop, Type)(VECTORREF(Type) this);                             \
  /* resize */                                                          \
  /* append copies of 'value' when extension */                         \
  void VF(Resize, Type)(VECTORREF(Type) this,                           \
                        size_t size, Type* value);                      \
  /* swap */                                                            \
  void VF(Swap, Type)(VECTORREF(Type) lhs, VECTORREF(Type) rhs);        \

#define DEFINE_VECTOR(Type)                                             \
  struct TEMPLATE(Type, VectorMethods) VECTOR_GLOBAL(Type);             \
                                                                        \
  void TEMPLATE(Type, VectorInitialize)(                                \
      TEMPLATE(Type, CtorMethod) ctor,                                  \
      TEMPLATE(Type, DtorMethod) dtor,                                  \
      TEMPLATE(Type, CopyMethod) copy) {                                \
    VECTOR_METHOD(Type, ctor) = ctor;                                   \
    VECTOR_METHOD(Type, dtor) = dtor;                                   \
    VECTOR_METHOD(Type, copy) = copy;                                   \
  }                                                                     \
                                                                        \
  void VF(Free, Type)(VECTORREF(Type) this) {                           \
    free(this->start_);                                                 \
  }                                                                     \
  void VF(Nullify, Type)(VECTORREF(Type) this) {                        \
    this->start_ = this->finish_ = this->end_ = NULL;                   \
  }                                                                     \
  Type* VF(SetEnd, Type)(VECTORREF(Type) this, Type* end) {             \
    return this->finish_ = end;                                         \
  }                                                                     \
  void VF(MoveUp, Type)(Type* head, Type* tail, size_t count) {         \
    if (0 < count) {                                                    \
      Type* src = tail;                                                 \
      Type* dst = tail + count;                                         \
      for (; src != head; --dst, --src) {                               \
        VECTOR_METHOD(Type, copy)(dst - 1, src - 1);                    \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VF(MoveDown, Type)(Type* head, Type* tail, size_t count) {       \
    if (0 < count) {                                                    \
      Type* src = head;                                                 \
      Type* dst = head - count;                                         \
      for (; src != tail; ++dst, ++src) {                               \
        VECTOR_METHOD(Type, copy)(dst, src);                            \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VF(RangeCtorCopy, Type)(Type* head, Type* tail, Type* data) {    \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VF(RangeCtorFill, Type)(Type* head, Type* tail, Type* data) {    \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VF(RangeCtor, Type)(Type* head, Type* tail) {                    \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VF(RangeDtor, Type)(Type* head, Type* tail) {                    \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, dtor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VF(RangeCopy, Type)(Type* head, Type* tail, Type* data) {        \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  /* this->start_ must not be allocated */                              \
  void VF(New, Type)(VECTORREF(Type) this,                              \
                     size_t size, Type* data, size_t count) {           \
    const size_t capacity = EnoughCapacity(size);                       \
    this->start_ = (Type*)malloc(sizeof(Type) * capacity);              \
    this->finish_ = this->start_ + count;                               \
    this->end_ = this->start_ + capacity;                               \
    VF(RangeCtorCopy, Type)(this->start_, this->finish_, data);         \
  }                                                                     \
                                                                        \
  VECTORREF(Type) VF(Ctor, Type)(void) {                                \
    VECTORREF(Type) this =                                              \
        (VECTORREF(Type))malloc(sizeof(struct VECTOR(Type)));           \
    VF(Nullify, Type)(this);                                            \
    return this;                                                        \
  }                                                                     \
  void VF(Dtor, Type)(VECTORREF(Type)* pthis) {                         \
    assert(pthis && *pthis);                                            \
    VF(Clear, Type)(*pthis);                                            \
    VF(Free, Type)(*pthis);                                             \
    free(*pthis);                                                       \
    *pthis = NULL;                                                      \
  }                                                                     \
  void VF(Copy, Type)(VECTORREF(Type) this, VECTORREF(Type) src) {      \
    assert(this && src);                                                \
    VF(Assign, Type)(this, VF(Data, Type)(src), VF(Size, Type)(src));   \
  }                                                                     \
  void VF(Assign, Type)(VECTORREF(Type) this,                           \
                        Type* data, size_t count) {                     \
    assert(this);                                                       \
    assert(count == 0 || data);                                         \
    if (VF(Capacity, Type)(this) < count) {                             \
      VF(Clear, Type)(this);                                            \
      VF(Reserve, Type)(this, count);                                   \
    }                                                                   \
    {                                                                   \
      Type* const begin = VF(Begin, Type)(this);                        \
      Type* const end = VF(End, Type)(this);                            \
      Type* const new_end = VF(SetEnd, Type)(this, begin + count);      \
      if (count < VF(Size, Type)(this)) {                               \
        VF(RangeCopy, Type)(begin, new_end, data);                      \
        VF(RangeDtor, Type)(new_end, end);                              \
      } else {                                                          \
        VF(RangeCtor, Type)(end, new_end);                              \
        VF(RangeCopy, Type)(begin, new_end, data);                      \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  Type* VF(Data, Type)(VECTORREF(Type) this) {                          \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VF(Begin, Type)(VECTORREF(Type) this) {                         \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VF(End, Type)(VECTORREF(Type) this) {                           \
    assert(this);                                                       \
    return this->finish_;                                               \
  }                                                                     \
  bool VF(Empty, Type)(VECTORREF(Type) this) {                          \
    assert(this);                                                       \
    return this->start_ == this->finish_;                               \
  }                                                                     \
  size_t VF(Size, Type)(VECTORREF(Type) this) {                         \
    assert(this);                                                       \
    return this->finish_ - this->start_;                                \
  }                                                                     \
  void VF(Reserve, Type)(VECTORREF(Type) this, size_t size) {           \
    assert(this);                                                       \
    if (VF(Capacity, Type)(this) < size) {                              \
      const size_t old_size = VF(Size, Type)(this);                     \
      if (old_size == 0) {                                              \
        VF(Free, Type)(this);                                           \
        VF(New, Type)(this, size, NULL, 0);                             \
      } else {                                                          \
        VECTORREF(Type) buffer = VF(Ctor, Type)();                      \
        VF(New, Type)(buffer, size, VF(Data, Type)(this), old_size);    \
        VF(Swap, Type)(this, buffer);                                   \
        VF(Dtor, Type)(&buffer);                                        \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  size_t VF(Capacity, Type)(VECTORREF(Type) this) {                     \
    assert(this);                                                       \
    return this->end_ - this->start_;                                   \
  }                                                                     \
  void VF(Clear, Type)(VECTORREF(Type) this) {                          \
    assert(this);                                                       \
    {                                                                   \
      Type* const begin = VF(Begin, Type)(this);                        \
      Type* const end = VF(End, Type)(this);                            \
      VF(SetEnd, Type)(this, begin);                                    \
      VF(RangeDtor, Type)(begin, end);                                  \
    }                                                                   \
  }                                                                     \
  void VF(Insert, Type)(VECTORREF(Type) this,                           \
                        size_t pos, Type* data, size_t count) {         \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VF(Size, Type)(this);                         \
      assert(pos <= size);                                              \
      assert(count == 0 || data);                                       \
      VF(Reserve, Type)(this, size + count);                            \
      {                                                                 \
        Type* const begin = VF(Begin, Type)(this);                      \
        Type* const end = VF(End, Type)(this);                          \
        Type* const new_end = VF(SetEnd, Type)(this, end + count);      \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VF(RangeCtor, Type)(end, new_end);                              \
        VF(MoveUp, Type)(head, end, count);                             \
        VF(RangeCopy, Type)(head, tail, data);                          \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VF(Erase, Type)(VECTORREF(Type) this,                            \
                       size_t pos, size_t count) {                      \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VF(Size, Type)(this);                         \
      assert(pos + count <= size);                                      \
      {                                                                 \
        Type* const begin = VF(Begin, Type)(this);                      \
        Type* const end = VF(End, Type)(this);                          \
        Type* const new_end = VF(SetEnd, Type)(this, end - count);      \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VF(MoveDown, Type)(tail, end, count);                           \
        VF(RangeDtor, Type)(new_end, end);                              \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VF(Push, Type)(VECTORREF(Type) this, Type* value) {              \
    assert(this && value);                                              \
    VF(Reserve, Type)(this, VF(Size, Type)(this) + 1);                  \
    {                                                                   \
      Type* const end = VF(End, Type)(this);                            \
      Type* const new_end = VF(SetEnd, Type)(this, end + 1);            \
      VF(RangeCtorCopy, Type)(end, new_end, value);                     \
    }                                                                   \
  }                                                                     \
  void VF(Pop, Type)(VECTORREF(Type) this) {                            \
    assert(this);                                                       \
    {                                                                   \
      Type* const end = VF(End, Type)(this);                            \
      Type* const new_end = VF(SetEnd, Type)(this, end - 1);            \
      VF(RangeDtor, Type)(new_end, end);                                \
    }                                                                   \
  }                                                                     \
  void VF(Resize, Type)(VECTORREF(Type) this,                           \
                        size_t size, Type* value) {                     \
    assert(this);                                                       \
    {                                                                   \
      const size_t old_size = VF(Size, Type)(this);                     \
      if (old_size < size) {                                            \
        assert(value);                                                  \
        VF(Reserve, Type)(this, size);                                  \
      }                                                                 \
      {                                                                 \
        Type* const begin = VF(Begin, Type)(this);                      \
        Type* const end = VF(End, Type)(this);                          \
        Type* const new_end = VF(SetEnd, Type)(this, begin + size);     \
        if (old_size < size) {                                          \
          VF(RangeCtorFill, Type)(end, new_end, value);                 \
        } else {                                                        \
          VF(RangeDtor, Type)(new_end, end);                            \
        }                                                               \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VF(Swap, Type)(VECTORREF(Type) lhs, VECTORREF(Type) rhs) {       \
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
