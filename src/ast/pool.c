#include "pool.h"
#include <assert.h>

static MemoryPoolRef g_ast_pool = NULL;

void ast_pool_ctor(void) {
  assert(!g_ast_pool);
  g_ast_pool = memory_pool_ctor(AST_POOL_CHUNK_SIZE);
}

void ast_pool_dtor(void) {
  memory_pool_dtor(&g_ast_pool);
}

MemoryPoolRef ast_pool(void) {
  return g_ast_pool;
}
