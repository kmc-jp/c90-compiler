#include "pool.h"
#include "vector_impl.h"
#include <assert.h>

static MemoryPoolRef g_codegen_pool = NULL;

void codegen_pool_ctor(void) {
  assert(!g_codegen_pool);
  g_codegen_pool = memory_pool_ctor(CODEGEN_POOL_CHUNK_SIZE);
}

void codegen_pool_dtor(void) {
  memory_pool_dtor(&g_codegen_pool);
}

MemoryPoolRef codegen_pool(void) {
  return g_codegen_pool;
}

DEFINE_VECTOR(LLVMTypeRef)
DEFINE_VECTOR(LLVMValueRef)
