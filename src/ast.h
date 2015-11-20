#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

#include <llvm-c/Core.h>

enum AstTag {
  AST_VOID_TYPE,
  AST_CHAR_TYPE,
  AST_SHORT_TYPE,
  AST_INT_TYPE,
  AST_LONG_TYPE,
  AST_FLOAT_TYPE,
  AST_DOUBLE_TYPE,
  AST_SIGNED_TYPE,
  AST_UNSIGNED_TYPE,
  ASTTAG_ENUM_END
};

struct Ast {
  enum AstTag tag;
  union AstBase {
    LLVMTypeRef type;
  } ast;
};

typedef struct Ast AST;

#endif  /* KMC_C89_COMPILER_AST_H */
