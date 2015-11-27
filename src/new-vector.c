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

static void* vector_default_allocate_container(void* manager) {
  return safe_malloc(struct VECTOR(Type));
  UNUSED(manager);
}
static void* vector_default_allocate_element(size_t count, void* manager) {
  return safe_array_malloc(Type, count);
  UNUSED(manager);
}
static void vector_default_deallocate(void* ptr, void* manager) {
  safe_free(ptr);
  UNUSED(manager);
}
static const struct Allocator g_vector_default_allocator = {
  NULL,
  vector_default_allocate_container,
  vector_default_allocate_element,
  vector_default_deallocate
};
AllocatorRef vector_default_allocator(void) {
  return &g_vector_default_allocator;
}


static VECTORREF(Type) vectorref_alloc(AllocatorRef allocator) {
  const VECTORREF(Type) self = allocate_container(allocator);
  self->start_ = self->finish_ = self->end_ = NULL;
  self->allocator_ = allocator;
  return self;
}
static void vectorref_free(VECTORREF(Type)* pself) {
  deallocate((*pself)->allocator_, *pself);
  *pself = NULL;
}
static void vector_alloc(VECTORREF(Type) self, size_t size) {
  const size_t capacity = enough_capacity(size);
  self->start_ = allocate_element(self->allocator_, capacity);
  self->finish_ = self->start_;
  self->end_ = self->start_ + capacity;
}
static void vector_free(VECTORREF(Type) self) {
  deallocate(self->allocator_, self->start_);
  self->start_ = self->finish_ = self->end_ = NULL;
}
static size_t vector_get_size(VECTORREF(Type) self) {
  return self->finish_ - self->start_;
}
static size_t vector_get_capacity(VECTORREF(Type) self) {
  return self->end_ - self->start_;
}
static Type* vector_get_begin(VECTORREF(Type) self) {
  return self->start_;
}
static Type* vector_get_end(VECTORREF(Type) self) {
  return self->finish_;
}
static void vector_set_size(VECTORREF(Type) self, size_t size) {
  self->finish_ = self->start_ + size;
}
static void vector_fill(Type* dst, Type fill, size_t count) {
  size_t i = 0;
  for (i = 0; i < count; ++i) {
    dst[i] = fill;
  }
}


VECTORREF(Type) make_vector(AllocatorRef allocator,
                      const Type* src, size_t count) {
  const VECTORREF(Type) self = vector_ctor(allocator);
  vector_assign(self, src, count);
  return self;
}
VECTORREF(Type) vector_ctor(AllocatorRef allocator) {
  if (!allocator) {
    allocator = vector_default_allocator();
  }
  return vectorref_alloc(allocator);
}
void vector_dtor(VECTORREF(Type)* pself) {
  assert(pself);
  if (*pself) {
    vector_free(*pself);
    vectorref_free(pself);
  }
}
void vector_copy(VECTORREF(Type) self, VECTORREF(Type) src) {
  assert(self && src);
  vector_assign(self, vector_data(src), vector_size(src));
}
void vector_assign(VECTORREF(Type) self, const Type* src, size_t count) {
  assert(self);
  assert(count == 0 || src);
  if (vector_capacity(self) < count) {
    vector_free(self);
    vector_alloc(self, count);
  }
  memory_copy(vector_data(self), src, sizeof(Type), count);
  vector_set_size(self, count);
}
Type vector_at(VECTORREF(Type) self, size_t index) {
  assert(self);
  return vector_data(self)[index];
}
Type vector_front(VECTORREF(Type) self) {
  assert(self);
  return vector_begin(self)[0];
}
Type vector_back(VECTORREF(Type) self) {
  assert(self);
  return vector_end(self)[-1];
}
Type* vector_data(VECTORREF(Type) self) {
  assert(self);
  return vector_get_begin(self);
}
Type* vector_begin(VECTORREF(Type) self) {
  assert(self);
  return vector_get_begin(self);
}
Type* vector_end(VECTORREF(Type) self) {
  assert(self);
  return vector_get_end(self);
}
bool vector_empty(VECTORREF(Type) self) {
  assert(self);
  return vector_begin(self) == vector_end(self);
}
size_t vector_size(VECTORREF(Type) self) {
  assert(self);
  return vector_get_size(self);
}
void vector_reserve(VECTORREF(Type) self, size_t size) {
  assert(self);
  if (vector_capacity(self) < size) {
    struct VECTOR(Type) original = *self;
    vector_alloc(self, size);
    vector_copy(self, &original);
    vector_free(&original);
  }
}
size_t vector_capacity(VECTORREF(Type) self) {
  assert(self);
  return vector_get_capacity(self);
}
void vector_shrink_to_fit(VECTORREF(Type) self) {
  assert(self);
  {
    const size_t size = vector_size(self);
    if (size < vector_capacity(self)) {
      struct VECTOR(Type) original = *self;
      vector_alloc(self, size);
      vector_copy(self, &original);
      vector_free(&original);
    }
  }
}
void vector_clear(VECTORREF(Type) self) {
  assert(self);
  vector_set_size(self, 0);
}
void vector_insert(VECTORREF(Type) self, size_t index,
                   const Type* data, size_t count) {
  assert(self);
  assert(count == 0 || data);
  if (0 < count) {
    const size_t size = vector_size(self);
    vector_reserve(self, size + count);
    {
      Type* const head = vector_begin(self) + index;
      Type* const tail = head + count;
      memory_move(tail, head, sizeof(Type), size - index);
      memory_copy(head, data, sizeof(Type), count);
      vector_set_size(self, size + count);
    }
  }
}
void vector_erase(VECTORREF(Type) self, size_t index, size_t count) {
  assert(self);
  {
    const size_t size = vector_size(self);
    if (size < index + count) {
      count = size - index;
    }
    {
      const size_t new_size = size - count;
      Type* const head = vector_begin(self) + index;
      Type* const tail = head + count;
      memory_move(head, tail, sizeof(Type), new_size - index);
      vector_set_size(self, new_size);
    }
  }
}
void vector_push_back(VECTORREF(Type) self, Type data) {
  assert(self);
  {
    const size_t new_size = vector_size(self) + 1;
    vector_reserve(self, new_size);
    *vector_end(self) = data;
    vector_set_size(self, new_size);
  }
}
void vector_pop_back(VECTORREF(Type) self) {
  assert(self);
  vector_set_size(self, vector_size(self) - 1);
}
void vector_resize(VECTORREF(Type) self, size_t size, Type fill) {
  assert(self);
  {
    const size_t old_size = vector_size(self);
    if (old_size < size) {
      vector_reserve(self, size);
      vector_fill(vector_end(self), fill, size - old_size);
    }
    vector_set_size(self, size);
  }
}
void vector_swap(VECTORREF(Type) self, VECTORREF(Type) other) {
  assert(self);
  {
    struct VECTOR(Type) tmp = *self;
    *self = *other;
    *other = tmp;
  }
}
