#ifndef INCLUDE_GUARD_UUID_733C42B7_9635_4796_A825_357B2A199BA7
#define INCLUDE_GUARD_UUID_733C42B7_9635_4796_A825_357B2A199BA7

#include "utility.h"

struct Allocator {
  void* manager_;
  void* (*container_allocator_)(void* manager);
  void* (*element_allocator_)(size_t count, void* manager);
  void (*deallocator_)(void* ptr, void* manager);
};

#endif  /* INCLUDE_GUARD_UUID_733C42B7_9635_4796_A825_357B2A199BA7 */
