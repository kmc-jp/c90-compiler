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
/* v->start_ must not be allocated */
void VF(New, Type)(VR(Type) v, size_t size, Type* data, size_t count) {
  const size_t capacity = EnoughCapacity(size);
  Type* it = (Type*)malloc(sizeof(Type) * capacity);
  v->start_ = it;
  v->finish_ = it + count;
  v->end_ = it + capacity;
  for (; it != v->finish_; ++it, ++data) {
    GV(Type).ctor_(it);
    GV(Type).copy_(it, data);
  }
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
void VF(Copy, Type)(VR(Type) dst, VR(Type) src) {
  assert(dst && src);
  VF(Assign, Type)(dst, VF(Data, Type)(src), VF(Size, Type)(src));
}
void VF(Assign, Type)(VR(Type) v, Type* data, size_t count) {
  assert(v);
  if (count == 0) {
    return;
  }
  assert(data);
  if (VF(Capacity, Type)(v) < count) {
    VF(Clear, Type)(v);
    VF(Reserve, Type)(v, count);
  }
  {
    const size_t size = VF(Size, Type)(v);
    Type* const begin = VF(Begin, Type)(v);
    Type* const end = VF(End, Type)(v);
    Type* it = begin;
    v->finish_ = begin + count;
    if (count < size) {
      for (; it != v->finish_; ++it, ++data) {
        GV(Type).copy_(it, data);
      }
      for (; it != end; ++it) {
        GV(Type).dtor_(it);
      }
    } else {
      for (it = end; it != v->finish_; ++it) {
        GV(Type).ctor_(it);
      }
      for (it = begin; it != v->finish_; ++it, ++data) {
        GV(Type).copy_(it, data);
      }
    }
  }
}
Type* VF(Data, Type)(VR(Type) v) {
  assert(v);
  return v->start_;
}
Type* VF(Begin, Type)(VR(Type) v) {
  assert(v);
  return v->start_;
}
Type* VF(End, Type)(VR(Type) v) {
  assert(v);
  return v->finish_;
}
bool VF(Empty, Type)(VR(Type) v) {
  assert(v);
  return v->start_ == v->finish_;
}
size_t VF(Size, Type)(VR(Type) v) {
  assert(v);
  return v->finish_ - v->start_;
}
void VF(Reserve, Type)(VR(Type) v, size_t size) {
  assert(v);
  if (VF(Capacity, Type)(v) < size) {
    const size_t old_size = VF(Size, Type)(v);
    if (old_size == 0) {
      free(v->start_);
      VF(New, Type)(v, size, NULL, 0);
    } else {
      struct V(Type) tmp = *v;
      VR(Type) buffer = VF(Ctor, Type)();
      VF(New, Type)(buffer, size, VF(Data, Type)(v), old_size);
      *v = *buffer;
      buffer = &tmp;
      VF(Dtor, Type)(&buffer);
    }
  }
}
size_t VF(Capacity, Type)(VR(Type) v) {
  assert(v);
  return v->end_ - v->start_;
}
void VF(Clear, Type)(VR(Type) v) {
  assert(v);
  {
    Type* const begin = VF(Begin, Type)(v);
    Type* const end = VF(End, Type)(v);
    Type* it = begin;
    v->finish_ = begin;
    for (; it != end; ++it) {
      GV(Type).dtor_(it);
    }
  }
}
void VF(Insert, Type)(VR(Type) v, size_t pos, Type* data, size_t count) {
  assert(v);
  {
    const size_t size = VF(Size, Type)(v);
    assert(pos <= size);
    if (count == 0) {
      return;
    }
    assert(data);
    VF(Reserve, Type)(v, size + count);
    {
      Type* const begin = VF(Begin, Type)(v);
      Type* const end = VF(End, Type)(v);
      Type* const head = begin + pos;
      Type* const tail = head + count;
      Type* it = end;
      Type* src = end;
      v->finish_ = end + count;
      for (; it != v->finish_; ++it) {
        GV(Type).ctor_(it);
      }
      for (; it != tail; --it, --src) {
        GV(Type).copy_(it - 1, src - 1);
      }
      for (it = head; it != tail; ++it, ++data) {
        GV(Type).copy_(it, data);
      }
    }
  }
}
void VF(Erase, Type)(VR(Type) v, size_t pos, size_t count) {
  assert(v);
  {
    const size_t size = VF(Size, Type)(v);
    assert(pos + count <= size);
    if (0 < count) {
      Type* const begin = VF(Begin, Type)(v);
      Type* const end = VF(End, Type)(v);
      Type* const head = begin + pos;
      Type* const tail = head + count;
      Type* it = head;
      Type* src = tail;
      v->finish_ = end - count;
      for (; it != v->finish_; ++it, ++src) {
        GV(Type).copy_(it, src);
      }
      for (; it != end; ++it) {
        GV(Type).dtor_(it);
      }
    }
  }
}
void VF(Push, Type)(VR(Type) v, Type* value) {
  assert(v && value);
  VF(Reserve, Type)(v, VF(Size, Type)(v) + 1);
  GV(Type).ctor_(v->finish_);
  GV(Type).copy_(v->finish_, value);
  ++v->finish_;
}
void VF(Pop, Type)(VR(Type) v) {
  assert(v);
  --v->finish_;
  GV(Type).dtor_(v->finish_);
}
void VF(Resize, Type)(VR(Type) v, size_t size, Type* value) {
  assert(v);
  {
    const size_t old_size = VF(Size, Type)(v);
    if (old_size < size) {
      assert(value);
      VF(Reserve, Type)(v, size);
    }
    {
      Type* const begin = VF(Begin, Type)(v);
      Type* const end = VF(End, Type)(v);
      Type* it = NULL;
      v->finish_ = begin + size;
      if (old_size < size) {
        for (it = end; it != v->finish_; ++it) {
          GV(Type).ctor_(it);
          GV(Type).copy_(it, value);
        }
      } else {
        for (it = v->finish_; it != end; ++it) {
          GV(Type).dtor_(it);
        }
      }
    }
  }
}
void VF(Swap, Type)(VR(Type) lhs, VR(Type) rhs) {
  assert(lhs && rhs);
  {
    struct V(Type) tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
  }
}
