#ifndef KMC_C89_COMPILER_AST_EXPRESSION_H
#define KMC_C89_COMPILER_AST_EXPRESSION_H

#include "../ast.h"

AstRef ast_make_primary_expression();
AstRef ast_make_postfix_expression();
AstRef ast_make_argument_expression_list();
AstRef ast_make_unary_expression();
AstRef ast_make_unary_operator();
AstRef ast_make_cast_expression();
AstRef ast_make_multiplicative_expression();
AstRef ast_make_additive_expression();
AstRef ast_make_shift_expression();
AstRef ast_make_relational_expression();
AstRef ast_make_equality_expression();
AstRef ast_make_and_expression();
AstRef ast_make_exclusive_or_expression();
AstRef ast_make_inclusive_or_expression();
AstRef ast_make_logical_and_expression();
AstRef ast_make_logical_or_expression();
AstRef ast_make_conditional_expression();
AstRef ast_make_assignment_expression();
AstRef ast_make_assignment_operator();
AstRef ast_make_expression();
AstRef ast_make_constant_expression();

#endif  /* KMC_C89_COMPILER_AST_EXPRESSION_H */
