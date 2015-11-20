#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

#include <llvm-c/Core.h>

enum AstTag {
  AST_TYPE,
  ASTTAG_ENUM_END
};

enum AstTypeTag {
  AST_TYPE_VOID,
  AST_TYPE_CHAR,
  AST_TYPE_SHORT,
  AST_TYPE_INT,
  AST_TYPE_LONG,
  AST_TYPE_FLOAT,
  AST_TYPE_DOUBLE,
  AST_TYPE_SIGNED,
  AST_TYPE_UNSIGNED,
  ASTTYPETAG_ENUM_END
};

struct AstType {
  enum AstTypeTag tag;
  LLVMTypeRef llvm;
};

struct Ast {
  enum AstTag tag;
  union AstBase {
    struct AstType type;
  } ast;
};

typedef struct Ast AST;

#endif  /* KMC_C89_COMPILER_AST_H */
