#ifndef INCLUDE_GUARD_UUID_369AE7CB_59C4_44F9_827B_3680E4BE4CE3
#define INCLUDE_GUARD_UUID_369AE7CB_59C4_44F9_827B_3680E4BE4CE3

#include "utility.h"

/* reference to allocator */
typedef const struct Allocator* AllocatorRef;

void* allocate_container(AllocatorRef allocator);
void* allocate_element(AllocatorRef allocator, size_t count);
void deallocate(AllocatorRef allocator, void* ptr);

#endif  /* INCLUDE_GUARD_UUID_369AE7CB_59C4_44F9_827B_3680E4BE4CE3 */
