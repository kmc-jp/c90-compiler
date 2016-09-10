#ifndef KMC_C90_COMPILER_SEXPR_POOL_H
#define KMC_C90_COMPILER_SEXPR_POOL_H

#include "allocator.h"
#include "memory_pool.h"

MemoryPoolRef sexpr_pool(void);
void sexpr_initialize_pool(void);
void sexpr_finalize_pool(void);

AllocatorRef sexpr_symbol_allocator(void);

#endif  /* KMC_C90_COMPILER_SEXPR_POOL_H */
