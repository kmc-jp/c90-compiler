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

void VF(Nullify, Type)(VR(Type) this) {
  this->start_ = this->finish_ = this->end_ = NULL;
}
void VF(Delete, Type)(VR(Type) this) {
  VF(Clear, Type)(this);
  free(this->start_);
  VF(Nullify, Type)(this);
}
/* this->start_ must not be allocated */
void VF(New, Type)(VR(Type) this, size_t size, Type* data, size_t count) {
  const size_t capacity = EnoughCapacity(size);
  Type* it = (Type*)malloc(sizeof(Type) * capacity);
  this->start_ = it;
  this->finish_ = it + count;
  this->end_ = it + capacity;
  for (; it != this->finish_; ++it, ++data) {
    GV(Type).ctor_(it);
    GV(Type).copy_(it, data);
  }
}

VR(Type) VF(Ctor, Type)(void) {
  VR(Type) this = (VR(Type))malloc(sizeof(struct V(Type)));
  VF(Nullify, Type)(this);
  return this;
}
void VF(Dtor, Type)(VR(Type)* pthis) {
  assert(pthis && *pthis);
  VF(Delete, Type)(*pthis);
  free(*pthis);
  *pthis = NULL;
}
void VF(Copy, Type)(VR(Type) this, VR(Type) src) {
  assert(this && src);
  VF(Assign, Type)(this, VF(Data, Type)(src), VF(Size, Type)(src));
}
void VF(Assign, Type)(VR(Type) this, Type* data, size_t count) {
  assert(this);
  if (count == 0) {
    return;
  }
  assert(data);
  if (VF(Capacity, Type)(this) < count) {
    VF(Clear, Type)(this);
    VF(Reserve, Type)(this, count);
  }
  {
    const size_t size = VF(Size, Type)(this);
    Type* const begin = VF(Begin, Type)(this);
    Type* const end = VF(End, Type)(this);
    Type* it = begin;
    this->finish_ = begin + count;
    if (count < size) {
      for (; it != this->finish_; ++it, ++data) {
        GV(Type).copy_(it, data);
      }
      for (; it != end; ++it) {
        GV(Type).dtor_(it);
      }
    } else {
      for (it = end; it != this->finish_; ++it) {
        GV(Type).ctor_(it);
      }
      for (it = begin; it != this->finish_; ++it, ++data) {
        GV(Type).copy_(it, data);
      }
    }
  }
}
Type* VF(Data, Type)(VR(Type) this) {
  assert(this);
  return this->start_;
}
Type* VF(Begin, Type)(VR(Type) this) {
  assert(this);
  return this->start_;
}
Type* VF(End, Type)(VR(Type) this) {
  assert(this);
  return this->finish_;
}
bool VF(Empty, Type)(VR(Type) this) {
  assert(this);
  return this->start_ == this->finish_;
}
size_t VF(Size, Type)(VR(Type) this) {
  assert(this);
  return this->finish_ - this->start_;
}
void VF(Reserve, Type)(VR(Type) this, size_t size) {
  assert(this);
  if (VF(Capacity, Type)(this) < size) {
    const size_t old_size = VF(Size, Type)(this);
    if (old_size == 0) {
      free(this->start_);
      VF(New, Type)(this, size, NULL, 0);
    } else {
      struct V(Type) tmp = *this;
      VR(Type) buffer = VF(Ctor, Type)();
      VF(New, Type)(buffer, size, VF(Data, Type)(this), old_size);
      *this = *buffer;
      buffer = &tmp;
      VF(Dtor, Type)(&buffer);
    }
  }
}
size_t VF(Capacity, Type)(VR(Type) this) {
  assert(this);
  return this->end_ - this->start_;
}
void VF(Clear, Type)(VR(Type) this) {
  assert(this);
  {
    Type* const begin = VF(Begin, Type)(this);
    Type* const end = VF(End, Type)(this);
    Type* it = begin;
    this->finish_ = begin;
    for (; it != end; ++it) {
      GV(Type).dtor_(it);
    }
  }
}
void VF(Insert, Type)(VR(Type) this, size_t pos, Type* data, size_t count) {
  assert(this);
  {
    const size_t size = VF(Size, Type)(this);
    assert(pos <= size);
    if (count == 0) {
      return;
    }
    assert(data);
    VF(Reserve, Type)(this, size + count);
    {
      Type* const begin = VF(Begin, Type)(this);
      Type* const end = VF(End, Type)(this);
      Type* const head = begin + pos;
      Type* const tail = head + count;
      Type* it = end;
      Type* src = end;
      this->finish_ = end + count;
      for (; it != this->finish_; ++it) {
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
void VF(Erase, Type)(VR(Type) this, size_t pos, size_t count) {
  assert(this);
  {
    const size_t size = VF(Size, Type)(this);
    assert(pos + count <= size);
    if (0 < count) {
      Type* const begin = VF(Begin, Type)(this);
      Type* const end = VF(End, Type)(this);
      Type* const head = begin + pos;
      Type* const tail = head + count;
      Type* it = head;
      Type* src = tail;
      this->finish_ = end - count;
      for (; it != this->finish_; ++it, ++src) {
        GV(Type).copy_(it, src);
      }
      for (; it != end; ++it) {
        GV(Type).dtor_(it);
      }
    }
  }
}
void VF(Push, Type)(VR(Type) this, Type* value) {
  assert(this && value);
  VF(Reserve, Type)(this, VF(Size, Type)(this) + 1);
  GV(Type).ctor_(this->finish_);
  GV(Type).copy_(this->finish_, value);
  ++this->finish_;
}
void VF(Pop, Type)(VR(Type) this) {
  assert(this);
  --this->finish_;
  GV(Type).dtor_(this->finish_);
}
void VF(Resize, Type)(VR(Type) this, size_t size, Type* value) {
  assert(this);
  {
    const size_t old_size = VF(Size, Type)(this);
    if (old_size < size) {
      assert(value);
      VF(Reserve, Type)(this, size);
    }
    {
      Type* const begin = VF(Begin, Type)(this);
      Type* const end = VF(End, Type)(this);
      Type* it = NULL;
      this->finish_ = begin + size;
      if (old_size < size) {
        for (it = end; it != this->finish_; ++it) {
          GV(Type).ctor_(it);
          GV(Type).copy_(it, value);
        }
      } else {
        for (it = this->finish_; it != end; ++it) {
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
