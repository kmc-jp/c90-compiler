#ifndef KMC_C90_COMPILER_AST_STATEMENTS_H
#define KMC_C90_COMPILER_AST_STATEMENTS_H

#include "ast.h"

AstRef ast_make_statement(AstRef statement);
AstRef ast_make_labeled_statement(AstRef labeled_statement);
AstRef ast_make_identifier_labeled_statement(AstRef identifier, AstRef statement);
AstRef ast_make_case_labeled_statement(AstRef constant_expression, AstRef statement);
AstRef ast_make_default_labeled_statement(AstRef statement);
AstRef ast_make_compound_statement(AstRef declaration_list, AstRef statement_list);
AstRef ast_make_declaration_list(void);
AstRef ast_push_declaration_list(AstRef declaration_list, AstRef declaration);
AstRef ast_make_statement_list(void);
AstRef ast_push_statement_list(AstRef statement_list, AstRef statement);
AstRef ast_make_expression_statement(AstNullableRef expression);
AstRef ast_make_selection_statement(AstRef selection_statement);
AstRef ast_make_if_statement(AstRef expression, AstRef statement);
AstRef ast_make_if_else_statement(AstRef expression, AstRef statement_if, AstRef statement_else);
AstRef ast_make_switch_statement(AstRef expression, AstRef statement);
AstRef ast_make_iteration_statement(AstRef iteration_statement);
AstRef ast_make_while_statement(AstRef expression, AstRef statement);
AstRef ast_make_do_while_statement(AstRef statement, AstRef expression);
AstRef ast_make_for_statement(AstNullableRef expression_1, AstNullableRef expression_2, AstNullableRef expression_3, AstRef statement);
AstRef ast_make_jump_statement(AstRef jump_statement);
AstRef ast_make_goto_jump_statement(AstRef identifier);
AstRef ast_make_continue_jump_statement(void);
AstRef ast_make_break_jump_statement(void);
AstRef ast_make_return_jump_statement(AstRef expression);
AstRef ast_make_void_return_jump_statement(void);

#endif  /* KMC_C90_COMPILER_AST_STATEMENTS_H */
