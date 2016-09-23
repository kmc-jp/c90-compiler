#ifndef INCLUDE_GUARD_UUID_7DB59410_A810_40B5_BB5F_19CB9E822A40
#define INCLUDE_GUARD_UUID_7DB59410_A810_40B5_BB5F_19CB9E822A40

#include "utility.h"
#include "allocator.h"

#define VECTOR(type) \
  TEMPLATE(type, Vector)
#define VECTORREF(type) \
  TEMPLATE(type, VectorRef)
#define VECTORFUNC(type, function) \
  CONCAT(VECTOR(type), function)

#define DECLARE_VECTORREF(T) \
  /* reference to vector of T */ \
  typedef struct VECTOR(T)* VECTORREF(T); \

#define DECLARE_VECTOR(T) \
  DECLARE_VECTORREF(T) \
  \
  AllocatorRef VECTORFUNC(T, default_allocator)(void); \
  \
  /* generate initialized vector */ \
  VECTORREF(T) VECTORFUNC(T, make_vector)(const T* src, size_t count, \
                                          AllocatorRef allocator); \
  \
  /* constructor */ \
  VECTORREF(T) VECTORFUNC(T, ctor)(AllocatorRef allocator); \
  /* destructor */ \
  void VECTORFUNC(T, dtor)(VECTORREF(T)* pself); \
  /* operator= */ \
  void VECTORFUNC(T, copy)(VECTORREF(T) self, VECTORREF(T) src); \
  /* assign */ \
  void VECTORFUNC(T, assign)(VECTORREF(T) self, const T* src, size_t count); \
  \
  /* at */ \
  /* undefined behavior if out of range */ \
  T VECTORFUNC(T, at)(VECTORREF(T) self, size_t index); \
  /* front */ \
  /* undefined behavior if empty */ \
  T VECTORFUNC(T, front)(VECTORREF(T) self); \
  /* front */ \
  /* undefined behavior if empty */ \
  T VECTORFUNC(T, back)(VECTORREF(T) self); \
  /* data */ \
  /* same as begin */ \
  T* VECTORFUNC(T, data)(VECTORREF(T) self); \
  /* begin */ \
  T* VECTORFUNC(T, begin)(VECTORREF(T) self); \
  /* end */ \
  T* VECTORFUNC(T, end)(VECTORREF(T) self); \
  \
  /* empty */ \
  bool VECTORFUNC(T, empty)(VECTORREF(T) self); \
  /* size */ \
  size_t VECTORFUNC(T, size)(VECTORREF(T) self); \
  /* reserve */ \
  void VECTORFUNC(T, reserve)(VECTORREF(T) self, size_t size); \
  /* capacity */ \
  size_t VECTORFUNC(T, capacity)(VECTORREF(T) self); \
  /* shrink_to_fit */ \
  void VECTORFUNC(T, shrink_to_fit)(VECTORREF(T) self); \
  \
  /* clear */ \
  void VECTORFUNC(T, clear)(VECTORREF(T) self); \
  /* insert */ \
  /* undefined behavior if index is out of range */ \
  void VECTORFUNC(T, insert)(VECTORREF(T) self, size_t index, \
                             const T* data, size_t count); \
  /* erase */ \
  /* undefined behavior if index is out of range */ \
  /* remove from index to the end if 'index + count' is out of range */ \
  void VECTORFUNC(T, erase)(VECTORREF(T) self, size_t index, size_t count); \
  /* push_back */ \
  void VECTORFUNC(T, push_back)(VECTORREF(T) self, T data); \
  /* pop_back */ \
  /* undefined behavior if empty */ \
  void VECTORFUNC(T, pop_back)(VECTORREF(T) self); \
  /* resize */ \
  void VECTORFUNC(T, resize)(VECTORREF(T) self, size_t size, T fill); \
  /* swap */ \
  void VECTORFUNC(T, swap)(VECTORREF(T) self, VECTORREF(T) other); \

#include "vector_impl.h"

#endif  /* INCLUDE_GUARD_UUID_7DB59410_A810_40B5_BB5F_19CB9E822A40 */
