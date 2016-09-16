#ifndef KMC_C90_COMPILER_AST_H
#define KMC_C90_COMPILER_AST_H

enum AstTag {
  AST_IDENTIFIER,
  AST_TAG_ENUM_END
};

const char* ast_info(enum AstTag tag);

#endif  /* KMC_C90_COMPILER_AST_H */
