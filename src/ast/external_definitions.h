#ifndef KMC_C89_COMPILER_AST_EXTERNAL_DEFINITIONS_H
#define KMC_C89_COMPILER_AST_EXTERNAL_DEFINITIONS_H

#include "../ast.h"

AstRef ast_make_translation_unit();
AstRef ast_push_translation_unit(AstRef translation_unit, AstRef external_declaration);
AstRef ast_make_external_declaration(AstRef external_declaration);
AstRef ast_make_function_definition();

#endif  /* KMC_C89_COMPILER_AST_EXTERNAL_DEFINITIONS_H */
