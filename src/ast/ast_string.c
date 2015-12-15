#include "ast_string.h"
#include <assert.h>
#include "../allocator_impl.h"
#include "../stdstring_impl.h"
#include "../ast_method.h"
#include "ast_impl.h"
#include "pool.h"

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

StringRef ast_make_string(const char* src, size_t length) {
  return make_string(src, length, &g_string_allocator);
}

AstRef ast_make_token(const char* src, size_t length) {
  AstRef self = ast_palloc(struct Ast);
  assert(src);
  self->tag = AST_TOKEN;
  self->data.token = ast_make_string(src, length);
  return self;
}

bool ast_is_token(AstRef ast) {
  assert(ast);
  return ast->tag == AST_TOKEN;
}

StringRef ast_get_token(AstRef ast) {
  assert(ast);
  if (ast_is_token(ast)) {
    return ast->data.token;
  }
  return NULL;
}
