#ifndef KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H
#define KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H

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

#endif  /* KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_IMPL_H */
