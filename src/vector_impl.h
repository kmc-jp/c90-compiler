#ifndef INCLUDE_GUARD_UUID_E601D647_8BA3_4262_B950_FE4DD1C72D12
#define INCLUDE_GUARD_UUID_E601D647_8BA3_4262_B950_FE4DD1C72D12
#include "allocator_impl.h"
#include <assert.h>

#define VECTOR_ELEMENT_COPY(type, dst, first, last) \
  memory_copy((dst), (first), sizeof(type), ((type*)(last) - (type*)(first)))
#define VECTOR_ELEMENT_MOVE(type, dst, first, last) \
  memory_move((dst), (first), sizeof(type), ((type*)(last) - (type*)(first)))

#define DEFINE_VECTOR(T) \
  /* vector of T */ \
  struct VECTOR(T) { \
    T* start_;  /* first data */ \
    T* finish_;  /* last data */ \
    T* end_;  /* end of storage */ \
    AllocatorRef allocator_; \
  }; \
  \
  static void* VECTORFUNC(T, default_allocate_container) \
      (void* manager) { \
    return safe_malloc(struct VECTOR(T)); \
    UNUSED(manager); \
  } \
  static void* VECTORFUNC(T, default_allocate_element) \
      (size_t count, void* manager) { \
    return safe_array_malloc(T, count); \
    UNUSED(manager); \
  } \
  static void VECTORFUNC(T, default_deallocate) \
      (void* ptr, void* manager) { \
    safe_free(ptr); \
    UNUSED(manager); \
  } \
  AllocatorRef VECTORFUNC(T, default_allocator)(void) { \
    static const struct Allocator allocator = { \
      NULL, \
      VECTORFUNC(T, default_allocate_container), \
      VECTORFUNC(T, default_allocate_element), \
      VECTORFUNC(T, default_deallocate) \
    }; \
    return &allocator; \
  } \
  static AllocatorRef VECTORFUNC(T, valid_allocator)(AllocatorRef allocator) { \
    return allocator ? allocator : VECTORFUNC(T, default_allocator)(); \
  } \
  \
  \
  static struct VECTOR(T) VECTORFUNC(T, null_vector)(AllocatorRef allocator) { \
    static struct VECTOR(T) null = { NULL, NULL, NULL, NULL }; \
    null.allocator_ = VECTORFUNC(T, valid_allocator)(allocator); \
    return null; \
  } \
  static VECTORREF(T) VECTORFUNC(T, vector_alloc)(AllocatorRef allocator) { \
    const VECTORREF(T) self = allocate_container(allocator); \
    *self = VECTORFUNC(T, null_vector)(allocator); \
    return self; \
  } \
  static void VECTORFUNC(T, vector_free)(VECTORREF(T)* pself) { \
    deallocate((*pself)->allocator_, *pself); \
    *pself = NULL; \
  } \
  static void VECTORFUNC(T, alloc)(VECTORREF(T) self, size_t size) { \
    const size_t capacity = enough_capacity(size); \
    self->start_ = allocate_element(self->allocator_, capacity); \
    self->finish_ = self->start_; \
    self->end_ = self->start_ + capacity; \
  } \
  static void VECTORFUNC(T, free)(VECTORREF(T) self) { \
    deallocate(self->allocator_, self->start_); \
    *self = VECTORFUNC(T, null_vector)(self->allocator_); \
  } \
  static void VECTORFUNC(T, realloc)(VECTORREF(T) self, size_t size) { \
    struct VECTOR(T) old = *self; \
    VECTORFUNC(T, alloc)(self, size); \
    VECTORFUNC(T, copy)(self, &old); \
    VECTORFUNC(T, free)(&old); \
  } \
  static size_t VECTORFUNC(T, get_size)(VECTORREF(T) self) { \
    return self->finish_ - self->start_; \
  } \
  static size_t VECTORFUNC(T, get_capacity)(VECTORREF(T) self) { \
    return self->end_ - self->start_; \
  } \
  static T* VECTORFUNC(T, get_begin)(VECTORREF(T) self) { \
    return self->start_; \
  } \
  static T* VECTORFUNC(T, get_end)(VECTORREF(T) self) { \
    return self->finish_; \
  } \
  static void VECTORFUNC(T, set_size)(VECTORREF(T) self, size_t size) { \
    self->finish_ = self->start_ + size; \
  } \
  static void VECTORFUNC(T, modify_size)(VECTORREF(T) self, int diff) { \
    self->finish_ += diff; \
  } \
  static void VECTORFUNC(T, fill)(T* dst, T fill, size_t count) { \
    size_t i = 0; \
    for (i = 0; i < count; ++i) { \
      dst[i] = fill; \
    } \
  } \
  \
  \
  VECTORREF(T) VECTORFUNC(T, make_vector)(const T* src, size_t count, \
                                          AllocatorRef allocator) { \
    const VECTORREF(T) self = VECTORFUNC(T, ctor)(allocator); \
    VECTORFUNC(T, assign)(self, src, count); \
    return self; \
  } \
  VECTORREF(T) VECTORFUNC(T, ctor)(AllocatorRef allocator) { \
    allocator = VECTORFUNC(T, valid_allocator)(allocator); \
    return VECTORFUNC(T, vector_alloc)(allocator); \
  } \
  void VECTORFUNC(T, dtor)(VECTORREF(T)* pself) { \
    assert(pself); \
    if (*pself) { \
      VECTORFUNC(T, free)(*pself); \
      VECTORFUNC(T, vector_free)(pself); \
    } \
  } \
  void VECTORFUNC(T, copy)(VECTORREF(T) self, VECTORREF(T) src) { \
    assert(self && src); \
    VECTORFUNC(T, assign)(self, VECTORFUNC(T, data)(src), \
                          VECTORFUNC(T, size)(src)); \
  } \
  void VECTORFUNC(T, assign)(VECTORREF(T) self, const T* src, size_t count) { \
    assert(self); \
    assert(count == 0 || src); \
    if (0 < count) { \
      struct VECTOR(T) old = VECTORFUNC(T, null_vector)(NULL); \
      if (VECTORFUNC(T, capacity)(self) < count) { \
        old = *self; \
        VECTORFUNC(T, alloc)(self, count); \
      } \
      VECTOR_ELEMENT_MOVE(T, VECTORFUNC(T, data)(self), src, src + count); \
      VECTORFUNC(T, free)(&old); \
    } \
    VECTORFUNC(T, set_size)(self, count); \
  } \
  T VECTORFUNC(T, at)(VECTORREF(T) self, size_t index) { \
    assert(self); \
    return VECTORFUNC(T, data)(self)[index]; \
  } \
  T VECTORFUNC(T, front)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, begin)(self)[0]; \
  } \
  T VECTORFUNC(T, back)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, end)(self)[-1]; \
  } \
  T* VECTORFUNC(T, data)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, get_begin)(self); \
  } \
  T* VECTORFUNC(T, begin)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, get_begin)(self); \
  } \
  T* VECTORFUNC(T, end)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, get_end)(self); \
  } \
  bool VECTORFUNC(T, empty)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, begin)(self) == VECTORFUNC(T, end)(self); \
  } \
  size_t VECTORFUNC(T, size)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, get_size)(self); \
  } \
  void VECTORFUNC(T, reserve)(VECTORREF(T) self, size_t size) { \
    assert(self); \
    if (VECTORFUNC(T, capacity)(self) < size) { \
      VECTORFUNC(T, realloc)(self, size); \
    } \
  } \
  size_t VECTORFUNC(T, capacity)(VECTORREF(T) self) { \
    assert(self); \
    return VECTORFUNC(T, get_capacity)(self); \
  } \
  void VECTORFUNC(T, shrink_to_fit)(VECTORREF(T) self) { \
    assert(self); \
    if (VECTORFUNC(T, size)(self) < VECTORFUNC(T, capacity)(self)) { \
      VECTORFUNC(T, realloc)(self, VECTORFUNC(T, size)(self)); \
    } \
  } \
  void VECTORFUNC(T, clear)(VECTORREF(T) self) { \
    assert(self); \
    VECTORFUNC(T, set_size)(self, 0); \
  } \
  void VECTORFUNC(T, insert)(VECTORREF(T) self, size_t index, \
                             const T* data, size_t count) { \
    assert(self); \
    assert(count == 0 || data); \
    if (0 < count) { \
      struct VECTOR(T) src = VECTORFUNC(T, null_vector)(NULL); \
      VECTORFUNC(T, assign)(&src, data, count); \
      data = VECTORFUNC(T, data)(&src); \
      VECTORFUNC(T, reserve)(self, VECTORFUNC(T, size)(self) + count); \
      { \
        T* const begin = VECTORFUNC(T, begin)(self); \
        T* const end = VECTORFUNC(T, end)(self); \
        T* const head = begin + index; \
        T* const tail = head + count; \
        VECTOR_ELEMENT_MOVE(T, tail, head, end); \
        VECTOR_ELEMENT_COPY(T, head, data, data + count); \
      } \
      VECTORFUNC(T, modify_size)(self, count); \
      VECTORFUNC(T, free)(&src); \
    } \
  } \
  void VECTORFUNC(T, erase)(VECTORREF(T) self, size_t index, size_t count) { \
    assert(self); \
    if (index + count < VECTORFUNC(T, size)(self)) { \
      T* const begin = VECTORFUNC(T, begin)(self); \
      T* const end = VECTORFUNC(T, end)(self); \
      T* const head = begin + index; \
      T* const tail = head + count; \
      VECTOR_ELEMENT_MOVE(T, head, tail, end); \
      VECTORFUNC(T, modify_size)(self, -count); \
    } else { \
      VECTORFUNC(T, set_size)(self, index); \
    } \
  } \
  void VECTORFUNC(T, push_back)(VECTORREF(T) self, T data) { \
    assert(self); \
    VECTORFUNC(T, reserve)(self, VECTORFUNC(T, size)(self) + 1); \
    *VECTORFUNC(T, end)(self) = data; \
    VECTORFUNC(T, modify_size)(self, 1); \
  } \
  void VECTORFUNC(T, pop_back)(VECTORREF(T) self) { \
    assert(self); \
    VECTORFUNC(T, modify_size)(self, -1); \
  } \
  void VECTORFUNC(T, resize)(VECTORREF(T) self, size_t size, T fill) { \
    assert(self); \
    if (VECTORFUNC(T, size)(self) < size) { \
      const size_t count = size - VECTORFUNC(T, size)(self); \
      VECTORFUNC(T, reserve)(self, size); \
      VECTORFUNC(T, fill)(VECTORFUNC(T, end)(self), fill, count); \
    } \
    VECTORFUNC(T, set_size)(self, size); \
  } \
  void VECTORFUNC(T, swap)(VECTORREF(T) self, VECTORREF(T) other) { \
    assert(self); \
    { \
      struct VECTOR(T) tmp = *self; \
      *self = *other; \
      *other = tmp; \
    } \
  } \

#endif  /* INCLUDE_GUARD_UUID_E601D647_8BA3_4262_B950_FE4DD1C72D12 */
