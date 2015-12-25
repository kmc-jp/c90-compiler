#include "ast_method.h"
#include "ast/pool.h"

void ast_initialize_pool(size_t size) {
  static bool is_first = true;
  if (is_first) {
    ast_pool_ctor(size);
    ast_string_allocator_ctor();
    ast_vector_allocator_ctor();
    is_first = false;
  }
}

void ast_finalize_pool(void) {
  ast_pool_dtor();
}
