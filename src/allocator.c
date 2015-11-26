#include "allocator.h"

struct Allocator {
  void* manager_;
  void* (*container_allocator_)(void* manager);
  void* (*element_allocator_)(size_t count, void* manager);
  void (*deallocator_)(void* ptr, void* manager);
};

void* allocate_container(AllocatorRef allocator) {
  return allocator->container_allocator_(allocator->manager_);
}
void* allocate_element(AllocatorRef allocator, size_t count) {
  return allocator->element_allocator_(count, allocator->manager_);
}
void deallocate(AllocatorRef allocator, void* ptr) {
  allocator->deallocator_(ptr, allocator->manager_);
}
