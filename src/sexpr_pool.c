#include "sexpr_pool.h"
#include <assert.h>
#include "allocator_impl.h"
#include "stdstring_impl.h"

static const size_t SEXPR_POOL_CHUNK_SIZE = 1024;
static MemoryPoolRef g_sexpr_pool = NULL;

static void* sexpr_symbol_allocate_container(void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(struct String, pool, 1);
}
static void* sexpr_symbol_allocate_element(size_t count, void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(char, pool, count);
}
static void sexpr_symbol_deallocate(void* ptr, void* manager) {
  UNUSED(ptr);
  UNUSED(manager);
}
static struct Allocator g_sexpr_symbol_allocator = {
  NULL,
  sexpr_symbol_allocate_container,
  sexpr_symbol_allocate_element,
  sexpr_symbol_deallocate,
};

MemoryPoolRef sexpr_pool(void) {
  assert(g_sexpr_pool);
  return g_sexpr_pool;
}

void sexpr_initialize_pool(void) {
  assert(!g_sexpr_pool);
  g_sexpr_pool = memory_pool_ctor(SEXPR_POOL_CHUNK_SIZE);
  g_sexpr_symbol_allocator.manager_ = g_sexpr_pool;
}

void sexpr_finalize_pool(void) {
  g_sexpr_symbol_allocator.manager_ = NULL;
  memory_pool_dtor(&g_sexpr_pool);
}

AllocatorRef sexpr_symbol_allocator(void) {
  assert(g_sexpr_symbol_allocator.manager_);
  return &g_sexpr_symbol_allocator;
}
