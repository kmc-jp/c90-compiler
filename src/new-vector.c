#include "new-vector.h"
#include "allocator_impl.h"
#include <assert.h>

/* vector of Type */
struct VECTOR(Type) {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
  AllocatorRef allocator_;
};

static void* VECTORFUNC(Type, default_allocate_container)(void* manager) {
  return safe_malloc(struct VECTOR(Type));
  UNUSED(manager);
}
static void* VECTORFUNC(Type, default_allocate_element)(size_t count,
                                                        void* manager) {
  return safe_array_malloc(Type, count);
  UNUSED(manager);
}
static void VECTORFUNC(Type, default_deallocate)(void* ptr, void* manager) {
  safe_free(ptr);
  UNUSED(manager);
}
static const struct Allocator g_vector_default_allocator = {
  NULL,
  VECTORFUNC(Type, default_allocate_container),
  VECTORFUNC(Type, default_allocate_element),
  VECTORFUNC(Type, default_deallocate)
};
AllocatorRef VECTORFUNC(Type, default_allocator)(void) {
  return &g_vector_default_allocator;
}


static VECTORREF(Type) VECTORFUNC(Type, vector_alloc)(AllocatorRef allocator) {
  const VECTORREF(Type) self = allocate_container(allocator);
  self->start_ = self->finish_ = self->end_ = NULL;
  self->allocator_ = allocator;
  return self;
}
static void VECTORFUNC(Type, vector_free)(VECTORREF(Type)* pself) {
  deallocate((*pself)->allocator_, *pself);
  *pself = NULL;
}
static void VECTORFUNC(Type, alloc)(VECTORREF(Type) self, size_t size) {
  const size_t capacity = enough_capacity(size);
  self->start_ = allocate_element(self->allocator_, capacity);
  self->finish_ = self->start_;
  self->end_ = self->start_ + capacity;
}
static void VECTORFUNC(Type, free)(VECTORREF(Type) self) {
  deallocate(self->allocator_, self->start_);
  self->start_ = self->finish_ = self->end_ = NULL;
}
static size_t VECTORFUNC(Type, get_size)(VECTORREF(Type) self) {
  return self->finish_ - self->start_;
}
static size_t VECTORFUNC(Type, get_capacity)(VECTORREF(Type) self) {
  return self->end_ - self->start_;
}
static Type* VECTORFUNC(Type, get_begin)(VECTORREF(Type) self) {
  return self->start_;
}
static Type* VECTORFUNC(Type, get_end)(VECTORREF(Type) self) {
  return self->finish_;
}
static void VECTORFUNC(Type, set_size)(VECTORREF(Type) self, size_t size) {
  self->finish_ = self->start_ + size;
}
static void VECTORFUNC(Type, fill)(Type* dst, Type fill, size_t count) {
  size_t i = 0;
  for (i = 0; i < count; ++i) {
    dst[i] = fill;
  }
}


VECTORREF(Type) VECTORFUNC(Type, make_vector)(AllocatorRef allocator,
                                              const Type* src, size_t count) {
  const VECTORREF(Type) self = VECTORFUNC(Type, ctor)(allocator);
  VECTORFUNC(Type, assign)(self, src, count);
  return self;
}
VECTORREF(Type) VECTORFUNC(Type, ctor)(AllocatorRef allocator) {
  if (!allocator) {
    allocator = VECTORFUNC(Type, default_allocator)();
  }
  return VECTORFUNC(Type, vector_alloc)(allocator);
}
void VECTORFUNC(Type, dtor)(VECTORREF(Type)* pself) {
  assert(pself);
  if (*pself) {
    VECTORFUNC(Type, free)(*pself);
    VECTORFUNC(Type, vector_free)(pself);
  }
}
void VECTORFUNC(Type, copy)(VECTORREF(Type) self, VECTORREF(Type) src) {
  assert(self && src);
  VECTORFUNC(Type, assign)(self, VECTORFUNC(Type, data)(src),
                           VECTORFUNC(Type, size)(src));
}
void VECTORFUNC(Type, assign)(VECTORREF(Type) self,
                              const Type* src, size_t count) {
  assert(self);
  assert(count == 0 || src);
  if (VECTORFUNC(Type, capacity)(self) < count) {
    VECTORFUNC(Type, free)(self);
    VECTORFUNC(Type, alloc)(self, count);
  }
  memory_copy(VECTORFUNC(Type, data)(self), src, sizeof(Type), count);
  VECTORFUNC(Type, set_size)(self, count);
}
Type VECTORFUNC(Type, at)(VECTORREF(Type) self, size_t index) {
  assert(self);
  return VECTORFUNC(Type, data)(self)[index];
}
Type VECTORFUNC(Type, front)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, begin)(self)[0];
}
Type VECTORFUNC(Type, back)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, end)(self)[-1];
}
Type* VECTORFUNC(Type, data)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, get_begin)(self);
}
Type* VECTORFUNC(Type, begin)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, get_begin)(self);
}
Type* VECTORFUNC(Type, end)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, get_end)(self);
}
bool VECTORFUNC(Type, empty)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, begin)(self) == VECTORFUNC(Type, end)(self);
}
size_t VECTORFUNC(Type, size)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, get_size)(self);
}
void VECTORFUNC(Type, reserve)(VECTORREF(Type) self, size_t size) {
  assert(self);
  if (VECTORFUNC(Type, capacity)(self) < size) {
    struct VECTOR(Type) original = *self;
    VECTORFUNC(Type, alloc)(self, size);
    VECTORFUNC(Type, copy)(self, &original);
    VECTORFUNC(Type, free)(&original);
  }
}
size_t VECTORFUNC(Type, capacity)(VECTORREF(Type) self) {
  assert(self);
  return VECTORFUNC(Type, get_capacity)(self);
}
void VECTORFUNC(Type, shrink_to_fit)(VECTORREF(Type) self) {
  assert(self);
  {
    const size_t size = VECTORFUNC(Type, size)(self);
    if (size < VECTORFUNC(Type, capacity)(self)) {
      struct VECTOR(Type) original = *self;
      VECTORFUNC(Type, alloc)(self, size);
      VECTORFUNC(Type, copy)(self, &original);
      VECTORFUNC(Type, free)(&original);
    }
  }
}
void VECTORFUNC(Type, clear)(VECTORREF(Type) self) {
  assert(self);
  VECTORFUNC(Type, set_size)(self, 0);
}
void VECTORFUNC(Type, insert)(VECTORREF(Type) self, size_t index,
                              const Type* data, size_t count) {
  assert(self);
  assert(count == 0 || data);
  if (0 < count) {
    const size_t size = VECTORFUNC(Type, size)(self);
    VECTORFUNC(Type, reserve)(self, size + count);
    {
      Type* const head = VECTORFUNC(Type, begin)(self) + index;
      Type* const tail = head + count;
      memory_move(tail, head, sizeof(Type), size - index);
      memory_copy(head, data, sizeof(Type), count);
      VECTORFUNC(Type, set_size)(self, size + count);
    }
  }
}
void VECTORFUNC(Type, erase)(VECTORREF(Type) self, size_t index, size_t count) {
  assert(self);
  {
    const size_t size = VECTORFUNC(Type, size)(self);
    if (size < index + count) {
      count = size - index;
    }
    {
      const size_t new_size = size - count;
      Type* const head = VECTORFUNC(Type, begin)(self) + index;
      Type* const tail = head + count;
      memory_move(head, tail, sizeof(Type), new_size - index);
      VECTORFUNC(Type, set_size)(self, new_size);
    }
  }
}
void VECTORFUNC(Type, push_back)(VECTORREF(Type) self, Type data) {
  assert(self);
  {
    const size_t new_size = VECTORFUNC(Type, size)(self) + 1;
    VECTORFUNC(Type, reserve)(self, new_size);
    *VECTORFUNC(Type, end)(self) = data;
    VECTORFUNC(Type, set_size)(self, new_size);
  }
}
void VECTORFUNC(Type, pop_back)(VECTORREF(Type) self) {
  assert(self);
  VECTORFUNC(Type, set_size)(self, VECTORFUNC(Type, size)(self) - 1);
}
void VECTORFUNC(Type, resize)(VECTORREF(Type) self, size_t size, Type fill) {
  assert(self);
  {
    const size_t old_size = VECTORFUNC(Type, size)(self);
    if (old_size < size) {
      VECTORFUNC(Type, reserve)(self, size);
      VECTORFUNC(Type, fill)(VECTORFUNC(Type, end)(self),
                             fill, size - old_size);
    }
    VECTORFUNC(Type, set_size)(self, size);
  }
}
void VECTORFUNC(Type, swap)(VECTORREF(Type) self, VECTORREF(Type) other) {
  assert(self);
  {
    struct VECTOR(Type) tmp = *self;
    *self = *other;
    *other = tmp;
  }
}
