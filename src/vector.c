#include "vector.h"
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
