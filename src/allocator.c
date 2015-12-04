#include "allocator.h"
#include "allocator_impl.h"

void* allocate_container(AllocatorRef allocator) {
  return allocator->container_allocator_(allocator->manager_);
}
void* allocate_element(AllocatorRef allocator, size_t count) {
  return allocator->element_allocator_(count, allocator->manager_);
}
void deallocate(AllocatorRef allocator, void* ptr) {
  allocator->deallocator_(ptr, allocator->manager_);
}
