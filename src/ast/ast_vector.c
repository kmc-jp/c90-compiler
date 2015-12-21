#include "ast_vector.h"
#include <assert.h>
#include "../ast_method.h"
#include "ast_impl.h"
#include "pool.h"

DEFINE_VECTOR(AstRef)

static void* ast_vector_allocate_container(void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(struct VECTOR(AstRef), pool, 1);
}

static void* ast_vector_allocate_element(size_t count, void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(AstRef, pool, count);
}

static void ast_vector_deallocate(void* ptr, void* manager) {
  UNUSED(ptr);
  UNUSED(manager);
}

static struct Allocator g_ast_vector_allocator = {
  NULL,
  ast_vector_allocate_container,
  ast_vector_allocate_element,
  ast_vector_deallocate
};

void ast_vector_allocator_ctor(void) {
  g_ast_vector_allocator.manager_ = ast_pool();
}

AstVectorRef ast_make_vector(void) {
  return AST_VECTOR_FUNC(ctor)(&g_ast_vector_allocator);
}

void ast_push_vector(AstVectorRef vector, AstRef element) {
  assert(vector && element);
  AST_VECTOR_FUNC(push_back)(vector, element);
}
