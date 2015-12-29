#include "pool.h"
#include <assert.h>
#include "../allocator_impl.h"
#include "../stdstring_impl.h"
#include "ast_impl.h"

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


static void* ast_string_allocate_container(void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(struct String, pool, 1);
}

static void* ast_string_allocate_element(size_t count, void* manager) {
  MemoryPoolRef pool = manager;
  return palloc(char, pool, count);
}

static void ast_string_deallocate(void* ptr, void* manager) {
  UNUSED(ptr);
  UNUSED(manager);
}

static struct Allocator g_string_allocator = {
  NULL,
  ast_string_allocate_container,
  ast_string_allocate_element,
  ast_string_deallocate
};

void ast_string_allocator_ctor(void) {
  g_string_allocator.manager_ = ast_pool();
}

AstRef ast_make_token(const char* src, size_t length) {
  AstRef self = ast_palloc(struct Ast);
  assert(src);
  self->tag = AST_TOKEN;
  self->data.token = make_string(src, length, &g_string_allocator);
  return self;
}


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
