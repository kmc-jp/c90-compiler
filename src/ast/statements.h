#ifndef KMC_C89_COMPILER_AST_STATEMENTS_H
#define KMC_C89_COMPILER_AST_STATEMENTS_H

#include "../ast.h"

AstRef ast_make_statement(AstRef statement);
AstRef ast_make_labeled_statement(AstRef labeled_statement);
AstRef ast_make_identifier_labeled_statement(AstRef identifier, AstRef statement);
AstRef ast_make_case_labeled_statement(AstRef constant_expression, AstRef statement);
AstRef ast_make_default_labeled_statement(AstRef statement);
AstRef ast_make_compound_statement();
AstRef ast_make_declaration_list();
AstRef ast_make_statement_list();
AstRef ast_make_expression_statement();
AstRef ast_make_selection_statement();
AstRef ast_make_iteration_statement();
AstRef ast_make_jump_statement(AstRef jump_statement);
AstRef ast_make_goto_jump_statement(AstRef identifier, AstRef statement);
AstRef ast_make_continue_jump_statement(AstRef statement);
AstRef ast_make_break_jump_statement(AstRef statement);
AstRef ast_make_return_jump_statement(AstRef expression, AstRef statement);
AstRef ast_make_void_return_jump_statement(AstRef statement);

#endif  /* KMC_C89_COMPILER_AST_STATEMENTS_H */
