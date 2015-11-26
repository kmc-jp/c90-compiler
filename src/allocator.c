#include "allocator.h"

struct Allocator {
  void* manager_;
  void* (*container_allocator_)(void* manager);
  void* (*element_allocator_)(size_t count, void* manager);
  void (*deallocator_)(void* ptr, void* manager);
};
