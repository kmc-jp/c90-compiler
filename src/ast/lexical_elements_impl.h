#ifndef KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H
#define KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H

#include "ast.h"

struct AstIdentifier {
  AstRef token;
};

struct AstConstant {
  AstRef constant;
};

struct AstFloatingConstant {
  AstRef token;
};

struct AstIntegerConstant {
  AstRef token;
};

struct AstEnumerationConstant {
  AstRef identifier;
};

struct AstCharacterConstant {
  AstRef token;
};

struct AstStringLiteral {
  AstRef token;
};

#endif  /* KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H */
