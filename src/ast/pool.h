#ifndef KMC_C90_COMPILER_AST_POOL_H
#define KMC_C90_COMPILER_AST_POOL_H

#include "ast.h"
#include "memory_pool.h"
#include "vector.h"

#define ast_palloc(type) \
  palloc(type, ast_pool(), 1)

#define AST_VECTOR_FUNC(function) \
  VECTORFUNC(AstRef, function)

DECLARE_VECTOR(AstRef)

static const size_t AST_POOL_CHUNK_SIZE = 1024;

MemoryPoolRef ast_pool(void);

AstRef ast_make_token(const char* src, size_t length);

AstVectorRef ast_make_vector(void);
void ast_push_vector(AstVectorRef vector, AstRef element);

void ast_initialize_pool(void);
void ast_finalize_pool(void);

#endif  /* KMC_C90_COMPILER_AST_POOL_H */
