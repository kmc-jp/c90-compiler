#ifndef KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_IMPL_H
#define KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_IMPL_H

#include "ast.h"

struct AstTranslationUnit {
  AstVectorRef external_declaration_vector;
};

struct AstExternalDeclaration {
  AstRef external_declaration;
};

struct AstFunctionDefinition {
  AstRef declaration_specifier_list;
  AstRef declarator;
  AstRef declaration_list;
  AstRef compound_statement;
};

#endif  /* KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_IMPL_H */
