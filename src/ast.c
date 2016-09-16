#include "ast.h"
#include <assert.h>

const char* ast_info(enum AstTag tag) {
  static const char* const tag_info[] = {
    "IDENTIFIER",
  };
  assert(sizeof(tag_info)/sizeof(char*) == AST_TAG_ENUM_END);
  return tag_info[tag];
}
