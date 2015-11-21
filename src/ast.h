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
  AST_FUNCTION_DECLARATION,
  AST_FUNCTION_DEFINITION,
  AST_TRANSLATION_UNIT,
  AST_STRING_LITERAL,
  AST_ARGUMENT_EXPRESSION_LIST,
  AST_FUNCTION_CALL,
  AST_NULL_EXPRESSION,
  AST_EXPRESSION_STATEMENT,
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

struct AstFunctionDeclaration {
  struct AstIdentifier identifier;
  ASTVEC parameter_list;
};

struct AstFunctionDefinition {
  struct AstType type;
  struct AstIdentifier identifier;
  ASTVEC parameter_list;
};

struct AstStringLiteral {
  char* string;
};

struct AstFunctionCall {
  struct AstIdentifier identifier;
  ASTVEC argument_list;
};

struct Ast {
  enum AstTag tag;
  union AstBase {
    void* dummy;
    ASTVEC vec;
    struct AstType type;
    struct AstIdentifier identifier;
    struct AstDeclaration declaration;
    struct AstFunctionDeclaration function_declaration;
    struct AstFunctionDefinition function_definition;
    struct AstStringLiteral string_literal;
    struct AstFunctionCall function_call;
  } ast;
};

typedef struct Ast AST;

DECLARE_VECTOR(AST)
void AST_ctor(AST* value);
void AST_dtor(AST* value);
void AST_copy(AST* dst, const AST* src);

AST bad_ast(void);

#endif  /* KMC_C89_COMPILER_AST_H */
