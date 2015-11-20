#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

#include <llvm-c/Core.h>
#include "vector.h"

#define ASTVEC VECTORREF(AST)
#define ASTFUNC(function) VECTORFUNC(AST, function)
typedef struct VECTOR(AST)* VECTORREF(AST);

enum AstTag {
  AST_TYPE,
  AST_IDENTIFIER,
  AST_DECLARATION,
  AST_PARAMETER_LIST,
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

struct AstIdentifier {
  char* symbol;
};

struct AstDeclaration {
  struct AstType specifier;
  struct AstIdentifier identifier;
};

struct Ast {
  enum AstTag tag;
  union AstBase {
    void* dummy;
    ASTVEC vec;
    struct AstType type;
    struct AstIdentifier identifier;
    struct AstDeclaration declaration;
  } ast;
};

typedef struct Ast AST;

DECLARE_VECTOR(AST)
void AST_ctor(AST* value);
void AST_dtor(AST* value);
void AST_copy(AST* dst, const AST* src);

AST bad_ast(void);

#endif  /* KMC_C89_COMPILER_AST_H */
