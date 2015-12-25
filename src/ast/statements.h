#ifndef KMC_C89_COMPILER_AST_STATEMENTS_H
#define KMC_C89_COMPILER_AST_STATEMENTS_H

#include "../ast.h"

AstRef ast_make_statement(AstRef statement);
AstRef ast_make_labeled_statement(AstRef labeled_statement);
AstRef ast_make_identifier_labeled_statement();
AstRef ast_make_case_labeled_statement();
AstRef ast_make_default_labeled_statement();
AstRef ast_make_compound_statement();
AstRef ast_make_declaration_list();
AstRef ast_make_statement_list();
AstRef ast_make_expression_statement();
AstRef ast_make_selection_statement();
AstRef ast_make_iteration_statement();
AstRef ast_make_jump_statement();

#endif  /* KMC_C89_COMPILER_AST_STATEMENTS_H */
