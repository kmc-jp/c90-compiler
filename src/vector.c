#include "vector.h"
#include <assert.h>
#include <stdlib.h>

struct VM(Type) GV(Type);

void T(VectorInitialize, Type)(T(CtorMethod, Type) ctor,
                               T(DtorMethod, Type) dtor,
                               T(CopyMethod, Type) copy) {
  GV(Type).ctor_ = ctor;
  GV(Type).dtor_ = dtor;
  GV(Type).copy_ = copy;
}

VR(Type) VF(Ctor, Type)(void) {
  VR(Type) v = (VR(Type))malloc(sizeof(struct V(Type)));
  v->start_ = v->finish_ = v->end_ = NULL;
  return v;
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
