#include "new-vector.h"
#include <assert.h>

/* vector of Type */
struct Vector {
  Type* start_;  /* first data */
  Type* finish_;  /* last data */
  Type* end_;  /* end of storage */
};

static VectorRef vectorref_alloc(void) {
  const VectorRef self = safe_malloc(struct Vector);
  self->start_ = self->finish_ = self->end_ = NULL;
  return self;
}
static void vectorref_free(VectorRef self) {
  safe_free(self);
}
static void vector_alloc(VectorRef self, size_t size) {
  const size_t capacity = enough_capacity(size);
  self->start_ = safe_array_malloc(Type, capacity);
  self->finish_ = self->start_;
  self->end_ = self->start_ + capacity;
}
static void vector_free(VectorRef self) {
  safe_free(self->start_);
  self->finish_ = self->end_ = NULL;
}
static size_t vector_get_size(VectorRef self) {
  return self->finish_ - self->start_;
}
static size_t vector_get_capacity(VectorRef self) {
  return self->end_ - self->start_;
}
static Type* vector_get_begin(VectorRef self) {
  return self->start_;
}
static Type* vector_get_end(VectorRef self) {
  return self->finish_;
}
static void vector_extend(VectorRef self, size_t size) {
  if (vector_get_capacity(self) < size) {
    vector_free(self);
    vector_alloc(self, size);
  }
}
static void vector_set_size(VectorRef self, size_t size) {
  self->finish_ = self->start_ + size;
}


VectorRef vector_ctor(void) {
  return vectorref_alloc();
}
void vector_dtor(VectorRef self) {
  assert(self);
  vector_free(self);
  vectorref_free(self);
}
void vector_copy(VectorRef self, VectorRef src) {
  assert(self && src);
  vector_assign(self, vector_data(src), vector_size(src));
}
void vector_assign(VectorRef self, const Type* src, size_t count) {
  assert(self);
  assert(count == 0 || src);
  vector_extend(self, count);
  vector_set_size(self, count);
  VECTOR_MEMORY_COPY(vector_data(self), src, count);
}
Type vector_at(VectorRef self, size_t index) {
  assert(self);
  return vector_data(self)[index];
}
Type vector_front(VectorRef self) {
  assert(self);
  return vector_begin(self)[0];
}
Type vector_back(VectorRef self) {
  assert(self);
  return vector_end(self)[-1];
}
Type* vector_data(VectorRef self) {
  assert(self);
  return vector_get_begin(self);
}
Type* vector_begin(VectorRef self) {
  assert(self);
  return vector_get_begin(self);
}
Type* vector_end(VectorRef self) {
  assert(self);
  return vector_get_end(self);
}
bool vector_empty(VectorRef self) {
  assert(self);
  return vector_begin(self) == vector_end(self);
}
size_t vector_size(VectorRef self) {
  assert(self);
  return vector_get_size(self);
}
