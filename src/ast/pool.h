#ifndef KMC_C89_COMPILER_AST_POOL_H
#define KMC_C89_COMPILER_AST_POOL_H

#include "../memory_pool.h"

#define ast_palloc(type) \
  palloc(type, ast_pool(), 1)

void ast_pool_ctor(size_t size);
void ast_pool_dtor(void);
MemoryPoolRef ast_pool(void);

#endif  /* KMC_C89_COMPILER_AST_POOL_H */
