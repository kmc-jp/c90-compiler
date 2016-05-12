#ifndef KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_H
#define KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_H

#include "ast.h"

AstRef ast_make_translation_unit(void);
AstRef ast_push_translation_unit(AstRef translation_unit, AstRef external_declaration);
AstRef ast_make_external_declaration(AstRef external_declaration);
AstRef ast_make_function_definition(AstRef declaration_specifier_list, AstRef declarator, AstRef declaration_list, AstRef compound_statement);

#endif  /* KMC_C90_COMPILER_AST_EXTERNAL_DEFINITIONS_H */
