#ifndef KMC_C89_COMPILER_ALLOCATOR_IMPL_H
#define KMC_C89_COMPILER_ALLOCATOR_IMPL_H

#include "utility.h"

struct Allocator {
  void* manager_;
  void* (*container_allocator_)(void* manager);
  void* (*element_allocator_)(size_t count, void* manager);
  void (*deallocator_)(void* ptr, void* manager);
};

#endif  /* KMC_C89_COMPILER_ALLOCATOR_IMPL_H */
