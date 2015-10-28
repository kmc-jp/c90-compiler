#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

#include <assert.h>
#include <stdlib.h>

#ifndef __cplusplus
typedef signed char bool;
#endif  /* __cplusplus */

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)
#define TBRACKET(x) CONCAT(T, CONCAT(x, T))
#define UNUSED(x) (void)(x)

/* template macro */
#define TEMPLATE(type, identifier)              \
  CONCAT(identifier, TBRACKET(type))
#define VECTOR(type)                            \
  TEMPLATE(type, Vector)
#define VECTORREF(type)                         \
  TEMPLATE(type, VectorRef)
#define VECTORFUNC(type, function)              \
  TEMPLATE(type, CONCAT(Vector, function))
#define VECTOR_GLOBAL(type)                             \
  CONCAT(global_, TEMPLATE(type, VectorMethods))
#define VECTOR_METHOD(type, function)           \
  VECTOR_GLOBAL(type).WITHBAR(function)
#define DEFAULT_METHOD(type, function)          \
  TEMPLATE(type, CONCAT(default_, function))
#define DEFAULT_VECTOR_METHOD(type, function)           \
  TEMPLATE(type, CONCAT(default_vector_, function))

/* declare vector template prototypes */
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
  void VECTORFUNC(Type, initialize)(TEMPLATE(Type, CtorMethod) ctor,    \
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
  VECTORREF(Type) VECTORFUNC(Type, ctor)(void);                         \
  /* destructor */                                                      \
  void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pthis);                  \
  /* operator= */                                                       \
  void VECTORFUNC(Type, copy)(VECTORREF(Type) this,                     \
                              VECTORREF(Type) src);                     \
  /* assign */                                                          \
  void VECTORFUNC(Type, assign)(VECTORREF(Type) this,                   \
                                Type* data, size_t count);              \
  /* data */                                                            \
  Type* VECTORFUNC(Type, data)(VECTORREF(Type) this);                   \
  /* begin */                                                           \
  Type* VECTORFUNC(Type, begin)(VECTORREF(Type) this);                  \
  /* end */                                                             \
  Type* VECTORFUNC(Type, end)(VECTORREF(Type) this);                    \
  /* empty */                                                           \
  bool VECTORFUNC(Type, empty)(VECTORREF(Type) this);                   \
  /* size */                                                            \
  size_t VECTORFUNC(Type, size)(VECTORREF(Type) this);                  \
  /* reserve */                                                         \
  void VECTORFUNC(Type, reserve)(VECTORREF(Type) this, size_t size);    \
  /* capacity */                                                        \
  size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) this);              \
  /* clear */                                                           \
  void VECTORFUNC(Type, clear)(VECTORREF(Type) this);                   \
  /* insert */                                                          \
  /* insert 'count' elements in data                                    \
     to the position indexed by 'pos' */                                \
  void VECTORFUNC(Type, insert)(VECTORREF(Type) this,                   \
                                size_t pos, Type* data, size_t count);  \
  /* erase */                                                           \
  /* remove consecutive 'count' elements                                \
     whose head is indexed by 'pos' */                                  \
  void VECTORFUNC(Type, erase)(VECTORREF(Type) this,                    \
                               size_t pos, size_t count);               \
  /* push_back */                                                       \
  void VECTORFUNC(Type, push)(VECTORREF(Type) this, Type* value);       \
  /* pop_back */                                                        \
  /* calling pop_back on empty vector is undefined */                   \
  void VECTORFUNC(Type, pop)(VECTORREF(Type) this);                     \
  /* resize */                                                          \
  /* append copies of 'value' when extension */                         \
  void VECTORFUNC(Type, resize)(VECTORREF(Type) this,                   \
                                size_t size, Type* value);              \
  /* swap */                                                            \
  void VECTORFUNC(Type, swap)(VECTORREF(Type) lhs,                      \
                              VECTORREF(Type) rhs);                     \

/* define vector template implementations */
#define DEFINE_VECTOR(Type)                                             \
  struct TEMPLATE(Type, VectorMethods) VECTOR_GLOBAL(Type);             \
                                                                        \
  void VECTORFUNC(Type, initialize)(                                    \
      TEMPLATE(Type, CtorMethod) ctor,                                  \
      TEMPLATE(Type, DtorMethod) dtor,                                  \
      TEMPLATE(Type, CopyMethod) copy) {                                \
    VECTOR_METHOD(Type, ctor) = ctor;                                   \
    VECTOR_METHOD(Type, dtor) = dtor;                                   \
    VECTOR_METHOD(Type, copy) = copy;                                   \
  }                                                                     \
                                                                        \
  void VECTORFUNC(Type, free)(VECTORREF(Type) this) {                   \
    free(this->start_);                                                 \
  }                                                                     \
  void VECTORFUNC(Type, nullify)(VECTORREF(Type) this) {                \
    this->start_ = this->finish_ = this->end_ = NULL;                   \
  }                                                                     \
  Type* VECTORFUNC(Type, set_end)(VECTORREF(Type) this, Type* end) {    \
    return this->finish_ = end;                                         \
  }                                                                     \
  void VECTORFUNC(Type, move_up)(                                       \
      Type* head, Type* tail, size_t count) {                           \
    if (0 < count) {                                                    \
      Type* src = tail;                                                 \
      Type* dst = tail + count;                                         \
      for (; src != head; --dst, --src) {                               \
        VECTOR_METHOD(Type, copy)(dst - 1, src - 1);                    \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, move_down)(                                     \
      Type* head, Type* tail, size_t count) {                           \
    if (0 < count) {                                                    \
      Type* src = head;                                                 \
      Type* dst = head - count;                                         \
      for (; src != tail; ++dst, ++src) {                               \
        VECTOR_METHOD(Type, copy)(dst, src);                            \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, range_ctor_copy)(                               \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, range_ctor_fill)(                               \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, range_ctor)(Type* head, Type* tail) {           \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, range_dtor)(Type* head, Type* tail) {           \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, dtor)(head);                                  \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, range_copy)(                                    \
      Type* head, Type* tail, Type* data) {                             \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  /* this->start_ must not be allocated */                              \
  void VECTORFUNC(Type, new)(VECTORREF(Type) this,                      \
                             size_t size, Type* data, size_t count) {   \
    const size_t capacity = enough_capacity(size);                      \
    this->start_ = (Type*)malloc(sizeof(Type) * capacity);              \
    this->finish_ = this->start_ + count;                               \
    this->end_ = this->start_ + capacity;                               \
    VECTORFUNC(Type, range_ctor_copy)(                                  \
        this->start_, this->finish_, data);                             \
  }                                                                     \
                                                                        \
  VECTORREF(Type) VECTORFUNC(Type, ctor)(void) {                        \
    VECTORREF(Type) this =                                              \
        (VECTORREF(Type))malloc(sizeof(struct VECTOR(Type)));           \
    VECTORFUNC(Type, nullify)(this);                                    \
    return this;                                                        \
  }                                                                     \
  void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pthis) {                 \
    assert(pthis && *pthis);                                            \
    VECTORFUNC(Type, clear)(*pthis);                                    \
    VECTORFUNC(Type, free)(*pthis);                                     \
    free(*pthis);                                                       \
    *pthis = NULL;                                                      \
  }                                                                     \
  void VECTORFUNC(Type, copy)(VECTORREF(Type) this,                     \
                              VECTORREF(Type) src) {                    \
    assert(this && src);                                                \
    VECTORFUNC(Type, assign)(this, VECTORFUNC(Type, data)(src),         \
                             VECTORFUNC(Type, size)(src));              \
  }                                                                     \
  void VECTORFUNC(Type, assign)(VECTORREF(Type) this,                   \
                                Type* data, size_t count) {             \
    assert(this);                                                       \
    assert(count == 0 || data);                                         \
    if (VECTORFUNC(Type, capacity)(this) < count) {                     \
      VECTORFUNC(Type, clear)(this);                                    \
      VECTORFUNC(Type, reserve)(this, count);                           \
    }                                                                   \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, begin)(this);                \
      Type* const end = VECTORFUNC(Type, end)(this);                    \
      Type* const new_end =                                             \
          VECTORFUNC(Type, set_end)(this, begin + count);               \
      if (count < VECTORFUNC(Type, size)(this)) {                       \
        VECTORFUNC(Type, range_copy)(begin, new_end, data);             \
        VECTORFUNC(Type, range_dtor)(new_end, end);                     \
      } else {                                                          \
        VECTORFUNC(Type, range_ctor)(end, new_end);                     \
        VECTORFUNC(Type, range_copy)(begin, new_end, data);             \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  Type* VECTORFUNC(Type, data)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, begin)(VECTORREF(Type) this) {                 \
    assert(this);                                                       \
    return this->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, end)(VECTORREF(Type) this) {                   \
    assert(this);                                                       \
    return this->finish_;                                               \
  }                                                                     \
  bool VECTORFUNC(Type, empty)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    return this->start_ == this->finish_;                               \
  }                                                                     \
  size_t VECTORFUNC(Type, size)(VECTORREF(Type) this) {                 \
    assert(this);                                                       \
    return this->finish_ - this->start_;                                \
  }                                                                     \
  void VECTORFUNC(Type, reserve)(VECTORREF(Type) this, size_t size) {   \
    assert(this);                                                       \
    if (VECTORFUNC(Type, capacity)(this) < size) {                      \
      const size_t old_size = VECTORFUNC(Type, size)(this);             \
      if (old_size == 0) {                                              \
        VECTORFUNC(Type, free)(this);                                   \
        VECTORFUNC(Type, new)(this, size, NULL, 0);                     \
      } else {                                                          \
        VECTORREF(Type) buffer = VECTORFUNC(Type, ctor)();              \
        VECTORFUNC(Type, new)(buffer, size,                             \
                              VECTORFUNC(Type, data)(this), old_size);  \
        VECTORFUNC(Type, swap)(this, buffer);                           \
        VECTORFUNC(Type, dtor)(&buffer);                                \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) this) {             \
    assert(this);                                                       \
    return this->end_ - this->start_;                                   \
  }                                                                     \
  void VECTORFUNC(Type, clear)(VECTORREF(Type) this) {                  \
    assert(this);                                                       \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, begin)(this);                \
      Type* const end = VECTORFUNC(Type, end)(this);                    \
      VECTORFUNC(Type, set_end)(this, begin);                           \
      VECTORFUNC(Type, range_dtor)(begin, end);                         \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, insert)(VECTORREF(Type) this,                   \
                                size_t pos, Type* data, size_t count) { \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VECTORFUNC(Type, size)(this);                 \
      assert(pos <= size);                                              \
      assert(count == 0 || data);                                       \
      VECTORFUNC(Type, reserve)(this, size + count);                    \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(this);              \
        Type* const end = VECTORFUNC(Type, end)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(this, end + count);               \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, range_ctor)(end, new_end);                     \
        VECTORFUNC(Type, move_up)(head, end, count);                    \
        VECTORFUNC(Type, range_copy)(head, tail, data);                 \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, erase)(VECTORREF(Type) this,                    \
                               size_t pos, size_t count) {              \
    assert(this);                                                       \
    {                                                                   \
      const size_t size = VECTORFUNC(Type, size)(this);                 \
      assert(pos + count <= size);                                      \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(this);              \
        Type* const end = VECTORFUNC(Type, end)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(this, end - count);               \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, move_down)(tail, end, count);                  \
        VECTORFUNC(Type, range_dtor)(new_end, end);                     \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, push)(VECTORREF(Type) this, Type* value) {      \
    assert(this && value);                                              \
    VECTORFUNC(Type, reserve)(this, VECTORFUNC(Type, size)(this) + 1);  \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, end)(this);                    \
      Type* const new_end = VECTORFUNC(Type, set_end)(this, end + 1);   \
      VECTORFUNC(Type, range_ctor_copy)(end, new_end, value);           \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, pop)(VECTORREF(Type) this) {                    \
    assert(this);                                                       \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, end)(this);                    \
      Type* const new_end = VECTORFUNC(Type, set_end)(this, end - 1);   \
      VECTORFUNC(Type, range_dtor)(new_end, end);                       \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, resize)(VECTORREF(Type) this,                   \
                                size_t size, Type* value) {             \
    assert(this);                                                       \
    {                                                                   \
      const size_t old_size = VECTORFUNC(Type, size)(this);             \
      if (old_size < size) {                                            \
        assert(value);                                                  \
        VECTORFUNC(Type, reserve)(this, size);                          \
      }                                                                 \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(this);              \
        Type* const end = VECTORFUNC(Type, end)(this);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(this, begin + size);              \
        if (old_size < size) {                                          \
          VECTORFUNC(Type, range_ctor_fill)(end, new_end, value);       \
        } else {                                                        \
          VECTORFUNC(Type, range_dtor)(new_end, end);                   \
        }                                                               \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, swap)(VECTORREF(Type) lhs,                      \
                              VECTORREF(Type) rhs) {                    \
    assert(lhs && rhs);                                                 \
    {                                                                   \
      struct VECTOR(Type) tmp = *lhs;                                   \
      *lhs = *rhs;                                                      \
      *rhs = tmp;                                                       \
    }                                                                   \
  }                                                                     \

/* default methods for built-in type */
#define DECLARE_DEFAULT_METHODS(Type)                           \
  void DEFAULT_METHOD(Type, ctor)(Type* value);                 \
  void DEFAULT_METHOD(Type, dtor)(Type* value);                 \
  void DEFAULT_METHOD(Type, copy)(Type* dst, Type* src);        \

#define DEFINE_DEFAULT_METHODS(Type)                            \
  void DEFAULT_METHOD(Type, ctor)(Type* value) {                \
    *value = (Type)0;                                           \
  }                                                             \
  void DEFAULT_METHOD(Type, dtor)(Type* value) {                \
    UNUSED(value);                                              \
  }                                                             \
  void DEFAULT_METHOD(Type, copy)(Type* dst, Type* src) {       \
    *dst = *src;                                                \
  }                                                             \

#define INITIALIZE_DEFAULT_METHODS(Type)                        \
  VECTORFUNC(Type, initialize)(DEFAULT_METHOD(Type, ctor),      \
                               DEFAULT_METHOD(Type, dtor),      \
                               DEFAULT_METHOD(Type, copy))      \

/* default methods for vector type */
#define DECLARE_DEFAULT_VECTOR_METHODS(Type)                            \
  void DEFAULT_VECTOR_METHOD(Type, ctor)(VECTORREF(Type)* value);       \
  void DEFAULT_VECTOR_METHOD(Type, dtor)(VECTORREF(Type)* value);       \
  void DEFAULT_VECTOR_METHOD(Type, copy)(VECTORREF(Type)* dst,          \
                                         VECTORREF(Type)* src);         \

#define DEFINE_DEFAULT_VECTOR_METHODS(Type)                             \
  void DEFAULT_VECTOR_METHOD(Type, ctor)(VECTORREF(Type)* value) {      \
    *value = VECTORFUNC(Type, ctor)();                                  \
  }                                                                     \
  void DEFAULT_VECTOR_METHOD(Type, dtor)(VECTORREF(Type)* value) {      \
    VECTORFUNC(Type, dtor)(value);                                      \
  }                                                                     \
  void DEFAULT_VECTOR_METHOD(Type, copy)(VECTORREF(Type)* dst,          \
                                         VECTORREF(Type)* src) {        \
    VECTORFUNC(Type, copy)(*dst, *src);                                 \
  }                                                                     \

#define INITIALIZE_DEFAULT_VECTOR_METHODS(Type) \
  VECTORFUNC(VECTORREF(Type), initialize)(      \
      DEFAULT_VECTOR_METHOD(Type, ctor),        \
      DEFAULT_VECTOR_METHOD(Type, dtor),        \
      DEFAULT_VECTOR_METHOD(Type, copy))        \

/* size <= capacity && capacity == pow(2, n) */
size_t enough_capacity(size_t size);

#endif  /* KMC_C89_COMPILER_VECTOR_H */
