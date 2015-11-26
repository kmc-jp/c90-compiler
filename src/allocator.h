#ifndef KMC_C89_COMPILER_ALLOCATOR_H
#define KMC_C89_COMPILER_ALLOCATOR_H

#include "utility.h"

/* reference to allocator */
typedef const struct Allocator* AllocatorRef;

void* allocate_container(AllocatorRef allocator);
void* allocate_element(AllocatorRef allocator, size_t count);
void deallocate(AllocatorRef allocator, void* ptr);

#endif  /* KMC_C89_COMPILER_ALLOCATOR_H */
