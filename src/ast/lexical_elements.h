#ifndef KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_H
#define KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_H

#include "ast.h"

AstRef ast_make_identifier(AstRef token);
AstRef ast_make_constant(AstRef constant);
AstRef ast_make_floating_constant(AstRef token);
AstRef ast_make_integer_constant(AstRef token);
AstRef ast_make_enumeration_constant(AstRef identifier);
AstRef ast_make_character_constant(AstRef token);
AstRef ast_make_string_literal(AstRef token);

#endif  /* KMC_C90_COMPILER_AST_LEXICAL_ELEMENTS_H */
