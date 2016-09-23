#ifndef INCLUDE_GUARD_UUID_DD55EAEA_2431_4469_A0F8_24CDD9BF0180
#define INCLUDE_GUARD_UUID_DD55EAEA_2431_4469_A0F8_24CDD9BF0180

#include "allocator.h"
#include "memory_pool.h"

MemoryPoolRef sexpr_pool(void);
void sexpr_initialize_pool(void);
void sexpr_finalize_pool(void);

AllocatorRef sexpr_symbol_allocator(void);

#endif  /* INCLUDE_GUARD_UUID_DD55EAEA_2431_4469_A0F8_24CDD9BF0180 */
