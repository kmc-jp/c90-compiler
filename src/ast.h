#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

enum AstTag {
  AST_IDENTIFIER,
  AST_INTEGER_CONSTANT,
  AST_FLOATING_CONSTANT,
  AST_CHARACTER_CONSTANT,
  AST_STRING_LITERAL,
  AST_TAG_ENUM_END
};

typedef struct Ast* AstRef;

#endif  /* KMC_C89_COMPILER_AST_H */
