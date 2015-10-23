#include "vector.h"
#include <assert.h>
#include <stdlib.h>

/* size <= capacity && capacity == pow(2, n) */
size_t EnoughCapacity(size_t size) {
  size_t capacity = 1;
  while (capacity < size) {
    capacity *= 2;
  }
  return capacity;
}

struct VM(Type) GV(Type);

void T(VectorInitialize, Type)(T(CtorMethod, Type) ctor,
                               T(DtorMethod, Type) dtor,
                               T(CopyMethod, Type) copy) {
  GV(Type).ctor_ = ctor;
  GV(Type).dtor_ = dtor;
  GV(Type).copy_ = copy;
}

void VF(Nullify, Type)(VR(Type) v) {
  v->start_ = v->finish_ = v->end_ = NULL;
}
void VF(Delete, Type)(VR(Type) v) {
  VF(Clear, Type)(v);
  free(v->start_);
  VF(Nullify, Type)(v);
}
/* v->start_ must be free-ed */
void VF(Alloc, Type)(VR(Type) v, size_t size) {
  const size_t capacity = EnoughCapacity(size);
  v->start_ = (Type*)malloc(sizeof(Type) * capacity);
  v->finish_ = v->start_;
  v->end_ = v->start_ + capacity;
}
/* v->start_ must not be constructed */
void VF(Place, Type)(VR(Type) v, size_t count) {
  size_t i = 0;
  for (i = 0; i < count; ++i) {
    GV(Type).ctor_(v->start_ + i);
  }
  v->finish_ = v->start_ + count;
}

VR(Type) VF(Ctor, Type)(void) {
  VR(Type) v = (VR(Type))malloc(sizeof(struct V(Type)));
  VF(Nullify, Type)(v);
  return v;
}
void VF(Dtor, Type)(VR(Type)* pv) {
  assert(pv && *pv);
  VF(Delete, Type)(*pv);
  free(*pv);
  *pv = NULL;
}
Type* VF(Data, Type)(VR(Type) v) {
  assert(v);
  return v->start_;
}
bool VF(Empty, Type)(VR(Type) v) {
  assert(v);
  return v->start_ == v->finish_;
}
size_t VF(Size, Type)(VR(Type) v) {
  assert(v);
  return v->finish_ - v->start_;
}
size_t VF(Capacity, Type)(VR(Type) v) {
  assert(v);
  return v->end_ - v->start_;
}
void VF(Clear, Type)(VR(Type) v) {
  assert(v);
  while (!VF(Empty, Type)) {
    VF(Pop, Type)(v);
  }
}
void VF(Pop, Type)(VR(Type) v) {
  assert(v);
  --v->finish_;
  GV(Type).dtor_(v->finish_);
}
