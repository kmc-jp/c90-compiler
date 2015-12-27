#ifndef KMC_C89_COMPILER_AST_POOL_H
#define KMC_C89_COMPILER_AST_POOL_H

#include "../ast.h"
#include "../memory_pool.h"

#define ast_palloc(type) \
  palloc(type, ast_pool(), 1)

static const size_t AST_POOL_CHUNK_SIZE = 1024;

void ast_pool_ctor(void);
void ast_pool_dtor(void);
MemoryPoolRef ast_pool(void);

void ast_string_allocator_ctor(void);

AstRef ast_make_token(const char* src, size_t length);

#endif  /* KMC_C89_COMPILER_AST_POOL_H */
