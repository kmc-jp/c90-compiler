#include "vector.h"

struct VM(Type) GV(Type);

void T(VectorInitialize, Type)(T(CtorMethod, Type) ctor,
                               T(DtorMethod, Type) dtor,
                               T(CopyMethod, Type) copy) {
  GV(Type).ctor_ = ctor;
  GV(Type).dtor_ = dtor;
  GV(Type).copy_ = copy;
}
