#ifndef KMC_C89_COMPILER_AST_H
#define KMC_C89_COMPILER_AST_H

enum AstTag {
};

struct Ast {
  enum AstTag tag;
  union AstBase {
  } ast;
};

typedef struct Ast AST;

#endif  /* KMC_C89_COMPILER_AST_H */
