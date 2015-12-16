#ifndef KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_H
#define KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_H

#include "../ast.h"

AstRef ast_make_identifier();
AstRef ast_make_constant();
AstRef ast_make_floating_constant();
AstRef ast_make_integer_constant();
AstRef ast_make_enumeration_constant();
AstRef ast_make_character_constant();
AstRef ast_make_string_literal();

#endif  /* KMC_C89_COMPILER_AST_LEXICAL_ELEMENTS_H */
