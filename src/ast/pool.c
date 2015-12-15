#include "pool.h"

static MemoryPoolRef g_ast_pool = NULL;

MemoryPoolRef ast_pool(void) {
  return g_ast_pool;
}
