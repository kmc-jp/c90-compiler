#ifndef KMC_C89_COMPILER_VECTOR_H
#define KMC_C89_COMPILER_VECTOR_H

#include <assert.h>
#include <stdlib.h>
#include "utility.h"

#define CONCATENATE(x, y) x ## y
#define CONCAT(x, y) CONCATENATE(x, y)
#define WITHBAR(x) CONCAT(x, _)
#define TBRACKET(x) CONCAT(T, CONCAT(x, T))

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
  typedef void (*TEMPLATE(Type, CopyMethod))(Type* dst,                 \
                                             const Type* src);          \
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
  void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pself);                  \
  /* operator= */                                                       \
  void VECTORFUNC(Type, copy)(VECTORREF(Type) self,                     \
                              VECTORREF(Type) src);                     \
  /* assign */                                                          \
  void VECTORFUNC(Type, assign)(VECTORREF(Type) self,                   \
                                const Type* data, size_t count);        \
  /* data */                                                            \
  Type* VECTORFUNC(Type, data)(VECTORREF(Type) self);                   \
  /* begin */                                                           \
  Type* VECTORFUNC(Type, begin)(VECTORREF(Type) self);                  \
  /* end */                                                             \
  Type* VECTORFUNC(Type, end)(VECTORREF(Type) self);                    \
  /* empty */                                                           \
  bool VECTORFUNC(Type, empty)(VECTORREF(Type) self);                   \
  /* size */                                                            \
  size_t VECTORFUNC(Type, size)(VECTORREF(Type) self);                  \
  /* reserve */                                                         \
  void VECTORFUNC(Type, reserve)(VECTORREF(Type) self, size_t size);    \
  /* capacity */                                                        \
  size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) self);              \
  /* clear */                                                           \
  void VECTORFUNC(Type, clear)(VECTORREF(Type) self);                   \
  /* insert */                                                          \
  /* insert 'count' elements in data                                    \
     to the position indexed by 'pos' */                                \
  void VECTORFUNC(Type, insert)(VECTORREF(Type) self, size_t pos,       \
                                const Type* data, size_t count);        \
  /* erase */                                                           \
  /* remove consecutive 'count' elements                                \
     whose head is indexed by 'pos' */                                  \
  void VECTORFUNC(Type, erase)(VECTORREF(Type) self,                    \
                               size_t pos, size_t count);               \
  /* push_back */                                                       \
  void VECTORFUNC(Type, push_back)(VECTORREF(Type) self,                \
                                   const Type* value);                  \
  /* pop_back */                                                        \
  /* calling pop_back on empty vector is undefined */                   \
  void VECTORFUNC(Type, pop_back)(VECTORREF(Type) self);                \
  /* resize */                                                          \
  /* append copies of value pointed by 'value' when extension */        \
  void VECTORFUNC(Type, resize)(VECTORREF(Type) self,                   \
                                size_t size, const Type* value);        \
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
  static void VECTORFUNC(Type, free)(VECTORREF(Type) self) {            \
    safe_free(self->start_);                                            \
    self->finish_ = self->end_ = NULL;                                  \
  }                                                                     \
  static void VECTORFUNC(Type, nullify)(VECTORREF(Type) self) {         \
    self->start_ = self->finish_ = self->end_ = NULL;                   \
  }                                                                     \
  static Type* VECTORFUNC(Type, set_end)(VECTORREF(Type) self,          \
                                         Type* end) {                   \
    return self->finish_ = end;                                         \
  }                                                                     \
  static void VECTORFUNC(Type, move_up)(                                \
      Type* head, Type* tail, size_t count) {                           \
    if (0 < count) {                                                    \
      Type* src = tail;                                                 \
      Type* dst = tail + count;                                         \
      for (; src != head; --dst, --src) {                               \
        VECTOR_METHOD(Type, copy)(dst - 1, src - 1);                    \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, move_down)(                              \
      Type* head, Type* tail, size_t count) {                           \
    if (0 < count) {                                                    \
      Type* src = head;                                                 \
      Type* dst = head - count;                                         \
      for (; src != tail; ++dst, ++src) {                               \
        VECTOR_METHOD(Type, copy)(dst, src);                            \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, range_ctor_copy)(                        \
      Type* head, Type* tail, const Type* data) {                       \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, range_ctor_fill)(                        \
      Type* head, Type* tail, const Type* data) {                       \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, range_ctor)(Type* head, Type* tail) {    \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, ctor)(head);                                  \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, range_dtor)(Type* head, Type* tail) {    \
    for (; head != tail; ++head) {                                      \
      VECTOR_METHOD(Type, dtor)(head);                                  \
    }                                                                   \
  }                                                                     \
  static void VECTORFUNC(Type, range_copy)(                             \
      Type* head, Type* tail, const Type* data) {                       \
    for (; head != tail; ++head, ++data) {                              \
      VECTOR_METHOD(Type, copy)(head, data);                            \
    }                                                                   \
  }                                                                     \
  /* self->start_ must not be allocated */                              \
  static void VECTORFUNC(Type, new)(VECTORREF(Type) self, size_t size,  \
                                    const Type* data, size_t count) {   \
    const size_t capacity = enough_capacity(size);                      \
    self->start_ = safe_array_malloc(Type, capacity);                   \
    self->finish_ = self->start_ + count;                               \
    self->end_ = self->start_ + capacity;                               \
    VECTORFUNC(Type, range_ctor_copy)(                                  \
        self->start_, self->finish_, data);                             \
  }                                                                     \
                                                                        \
  VECTORREF(Type) VECTORFUNC(Type, ctor)(void) {                        \
    VECTORREF(Type) self = safe_malloc(struct VECTOR(Type));            \
    VECTORFUNC(Type, nullify)(self);                                    \
    return self;                                                        \
  }                                                                     \
  void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pself) {                 \
    assert(pself && *pself);                                            \
    VECTORFUNC(Type, clear)(*pself);                                    \
    VECTORFUNC(Type, free)(*pself);                                     \
    safe_free(*pself);                                                  \
  }                                                                     \
  void VECTORFUNC(Type, copy)(VECTORREF(Type) self,                     \
                              VECTORREF(Type) src) {                    \
    assert(self && src);                                                \
    VECTORFUNC(Type, assign)(self, VECTORFUNC(Type, data)(src),         \
                             VECTORFUNC(Type, size)(src));              \
  }                                                                     \
  void VECTORFUNC(Type, assign)(VECTORREF(Type) self,                   \
                                const Type* data, size_t count) {       \
    assert(self);                                                       \
    assert(count == 0 || data);                                         \
    if (VECTORFUNC(Type, capacity)(self) < count) {                     \
      VECTORFUNC(Type, clear)(self);                                    \
      VECTORFUNC(Type, reserve)(self, count);                           \
    }                                                                   \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, begin)(self);                \
      Type* const end = VECTORFUNC(Type, end)(self);                    \
      Type* const new_end =                                             \
          VECTORFUNC(Type, set_end)(self, begin + count);               \
      if (count < VECTORFUNC(Type, size)(self)) {                       \
        VECTORFUNC(Type, range_copy)(begin, new_end, data);             \
        VECTORFUNC(Type, range_dtor)(new_end, end);                     \
      } else {                                                          \
        VECTORFUNC(Type, range_ctor)(end, new_end);                     \
        VECTORFUNC(Type, range_copy)(begin, new_end, data);             \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  Type* VECTORFUNC(Type, data)(VECTORREF(Type) self) {                  \
    assert(self);                                                       \
    return self->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, begin)(VECTORREF(Type) self) {                 \
    assert(self);                                                       \
    return self->start_;                                                \
  }                                                                     \
  Type* VECTORFUNC(Type, end)(VECTORREF(Type) self) {                   \
    assert(self);                                                       \
    return self->finish_;                                               \
  }                                                                     \
  bool VECTORFUNC(Type, empty)(VECTORREF(Type) self) {                  \
    assert(self);                                                       \
    return self->start_ == self->finish_;                               \
  }                                                                     \
  size_t VECTORFUNC(Type, size)(VECTORREF(Type) self) {                 \
    assert(self);                                                       \
    return self->finish_ - self->start_;                                \
  }                                                                     \
  void VECTORFUNC(Type, reserve)(VECTORREF(Type) self, size_t size) {   \
    assert(self);                                                       \
    if (VECTORFUNC(Type, capacity)(self) < size) {                      \
      const size_t old_size = VECTORFUNC(Type, size)(self);             \
      if (old_size == 0) {                                              \
        VECTORFUNC(Type, free)(self);                                   \
        VECTORFUNC(Type, new)(self, size, NULL, 0);                     \
      } else {                                                          \
        VECTORREF(Type) buffer = VECTORFUNC(Type, ctor)();              \
        VECTORFUNC(Type, new)(buffer, size,                             \
                              VECTORFUNC(Type, data)(self), old_size);  \
        VECTORFUNC(Type, swap)(self, buffer);                           \
        VECTORFUNC(Type, dtor)(&buffer);                                \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) self) {             \
    assert(self);                                                       \
    return self->end_ - self->start_;                                   \
  }                                                                     \
  void VECTORFUNC(Type, clear)(VECTORREF(Type) self) {                  \
    assert(self);                                                       \
    {                                                                   \
      Type* const begin = VECTORFUNC(Type, begin)(self);                \
      Type* const end = VECTORFUNC(Type, end)(self);                    \
      VECTORFUNC(Type, set_end)(self, begin);                           \
      VECTORFUNC(Type, range_dtor)(begin, end);                         \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, insert)(VECTORREF(Type) self, size_t pos,       \
                                const Type* data, size_t count) {       \
    assert(self);                                                       \
    {                                                                   \
      const size_t size = VECTORFUNC(Type, size)(self);                 \
      assert(pos <= size);                                              \
      assert(count == 0 || data);                                       \
      VECTORFUNC(Type, reserve)(self, size + count);                    \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(self);              \
        Type* const end = VECTORFUNC(Type, end)(self);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(self, end + count);               \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, range_ctor)(end, new_end);                     \
        VECTORFUNC(Type, move_up)(head, end, count);                    \
        VECTORFUNC(Type, range_copy)(head, tail, data);                 \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, erase)(VECTORREF(Type) self,                    \
                               size_t pos, size_t count) {              \
    assert(self);                                                       \
    {                                                                   \
      assert(pos + count <= VECTORFUNC(Type, size)(self));              \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(self);              \
        Type* const end = VECTORFUNC(Type, end)(self);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(self, end - count);               \
        Type* const head = begin + pos;                                 \
        Type* const tail = head + count;                                \
        VECTORFUNC(Type, move_down)(tail, end, count);                  \
        VECTORFUNC(Type, range_dtor)(new_end, end);                     \
      }                                                                 \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, push_back)(VECTORREF(Type) self,                \
                                   const Type* value) {                 \
    assert(self && value);                                              \
    VECTORFUNC(Type, reserve)(self, VECTORFUNC(Type, size)(self) + 1);  \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, end)(self);                    \
      Type* const new_end = VECTORFUNC(Type, set_end)(self, end + 1);   \
      VECTORFUNC(Type, range_ctor_copy)(end, new_end, value);           \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, pop_back)(VECTORREF(Type) self) {               \
    assert(self);                                                       \
    {                                                                   \
      Type* const end = VECTORFUNC(Type, end)(self);                    \
      Type* const new_end = VECTORFUNC(Type, set_end)(self, end - 1);   \
      VECTORFUNC(Type, range_dtor)(new_end, end);                       \
    }                                                                   \
  }                                                                     \
  void VECTORFUNC(Type, resize)(VECTORREF(Type) self,                   \
                                size_t size, const Type* value) {       \
    assert(self);                                                       \
    {                                                                   \
      const size_t old_size = VECTORFUNC(Type, size)(self);             \
      if (old_size < size) {                                            \
        assert(value);                                                  \
        VECTORFUNC(Type, reserve)(self, size);                          \
      }                                                                 \
      {                                                                 \
        Type* const begin = VECTORFUNC(Type, begin)(self);              \
        Type* const end = VECTORFUNC(Type, end)(self);                  \
        Type* const new_end =                                           \
            VECTORFUNC(Type, set_end)(self, begin + size);              \
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
  void DEFAULT_METHOD(Type, copy)(Type* dst, const Type* src);  \

#define DEFINE_DEFAULT_METHODS(Type)                            \
  void DEFAULT_METHOD(Type, ctor)(Type* value) {                \
    *value = (Type)0;                                           \
  }                                                             \
  void DEFAULT_METHOD(Type, dtor)(Type* value) {                \
    UNUSED(value);                                              \
  }                                                             \
  void DEFAULT_METHOD(Type, copy)(Type* dst, const Type* src) { \
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
                                         const VECTORREF(Type)* src);   \

#define DEFINE_DEFAULT_VECTOR_METHODS(Type)                             \
  void DEFAULT_VECTOR_METHOD(Type, ctor)(VECTORREF(Type)* value) {      \
    *value = VECTORFUNC(Type, ctor)();                                  \
  }                                                                     \
  void DEFAULT_VECTOR_METHOD(Type, dtor)(VECTORREF(Type)* value) {      \
    VECTORFUNC(Type, dtor)(value);                                      \
  }                                                                     \
  void DEFAULT_VECTOR_METHOD(Type, copy)(VECTORREF(Type)* dst,          \
                                         const VECTORREF(Type)* src) {  \
    VECTORFUNC(Type, copy)(*dst, *src);                                 \
  }                                                                     \

#define INITIALIZE_DEFAULT_VECTOR_METHODS(Type) \
  VECTORFUNC(VECTORREF(Type), initialize)(      \
      DEFAULT_VECTOR_METHOD(Type, ctor),        \
      DEFAULT_VECTOR_METHOD(Type, dtor),        \
      DEFAULT_VECTOR_METHOD(Type, copy))        \

#endif  /* KMC_C89_COMPILER_VECTOR_H */
