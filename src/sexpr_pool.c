#include "sexpr_pool.h"
#include <assert.h>

static const size_t SEXPR_POOL_CHUNK_SIZE = 1024;
static MemoryPoolRef g_sexpr_pool = NULL;

MemoryPoolRef sexpr_pool(void) {
  assert(g_sexpr_pool);
  return g_sexpr_pool;
}

void sexpr_initialize_pool(void) {
  assert(!g_sexpr_pool);
  g_sexpr_pool = memory_pool_ctor(SEXPR_POOL_CHUNK_SIZE);
}

void sexpr_finalize_pool(void) {
  memory_pool_dtor(&g_sexpr_pool);
}
