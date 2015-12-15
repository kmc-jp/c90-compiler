#ifndef KMC_C89_COMPILER_AST_AST_IMPL_H
#define KMC_C89_COMPILER_AST_AST_IMPL_H

#include "../ast.h"

struct Ast {
  enum AstTag tag;
  union AstData {
    char* token;
  } data;
};

#endif  /* KMC_C89_COMPILER_AST_AST_IMPL_H */
