#include "pool.h"
#include <assert.h>

static MemoryPoolRef g_ast_pool = NULL;

void ast_pool_ctor(size_t size) {
  assert(!g_ast_pool);
  g_ast_pool = memory_pool_ctor(size);
}

void ast_pool_dtor(void) {
  memory_pool_dtor(&g_ast_pool);
}

MemoryPoolRef ast_pool(void) {
  return g_ast_pool;
}
