#include "statements.h"
#include "statements_impl.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

AstRef ast_make_statement(AstRef statement) {
  AstRef self = NULL;
  if (ast_is_labeled_statement(statement) ||
      ast_is_compound_statement(statement) ||
      ast_is_expression_statement(statement) ||
      ast_is_selection_statement(statement) ||
      ast_is_iteration_statement(statement) ||
      ast_is_jump_statement(statement)) {
    AstStatementRef data = ast_palloc(struct AstStatement);
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_STATEMENT;
    self->data.statement = data;
  }
  return self;
}

AstRef ast_make_labeled_statement(AstRef labeled_statement) {
  AstRef self = NULL;
  if (ast_is_identifier_labeled_statement(labeled_statement) ||
      ast_is_case_labeled_statement(labeled_statement) ||
      ast_is_default_labeled_statement(labeled_statement)) {
    AstLabeledStatementRef data = ast_palloc(struct AstLabeledStatement);
    data->labeled_statement = labeled_statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_LABELED_STATEMENT;
    self->data.labeled_statement = data;
  }
  return self;
}

AstRef ast_make_identifier_labeled_statement(
    AstRef identifier, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_identifier(identifier) && ast_is_statement(statement)) {
    AstIdentifierLabeledStatementRef data = ast_palloc(struct AstIdentifierLabeledStatement);
    data->identifier = identifier;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_IDENTIFIER_LABELED_STATEMENT;
    self->data.identifier_labeled_statement = data;
  }
  return self;
}

AstRef ast_make_case_labeled_statement(
    AstRef constant_expression, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_constant_expression(constant_expression) &&
      ast_is_statement(statement)) {
    AstCaseLabeledStatementRef data = ast_palloc(struct AstCaseLabeledStatement);
    data->constant_expression = constant_expression;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_CASE_LABELED_STATEMENT;
    self->data.case_labeled_statement = data;
  }
  return self;
}

AstRef ast_make_default_labeled_statement(AstRef statement) {
  AstRef self = NULL;
  if (ast_is_statement(statement)) {
    AstDefaultLabeledStatementRef data = ast_palloc(struct AstDefaultLabeledStatement);
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_DEFAULT_LABELED_STATEMENT;
    self->data.default_labeled_statement = data;
  }
  return self;
}

AstRef ast_make_compound_statement(
    AstRef declaration_list, AstRef statement_list) {
  AstRef self = NULL;
  if (ast_is_declaration_list(declaration_list) &&
      ast_is_statement_list(statement_list)) {
    AstCompoundStatementRef data = ast_palloc(struct AstCompoundStatement);
    data->declaration_list = declaration_list;
    data->statement_list = statement_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_COMPOUND_STATEMENT;
    self->data.compound_statement = data;
  }
  return self;
}

AstRef ast_make_declaration_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstDeclarationListRef data = ast_palloc(struct AstDeclarationList);
  data->declaration_vector = ast_make_vector();
  self->tag = AST_DECLARATION_LIST;
  self->data.declaration_list = data;
  return self;
}

AstRef ast_push_declaration_list(AstRef declaration_list, AstRef declaration) {
  AstRef self = NULL;
  if (ast_is_declaration_list(declaration_list) &&
      ast_is_declaration(declaration)) {
    AstDeclarationListRef data = ast_get_declaration_list(declaration_list);
    ast_push_vector(data->declaration_vector, declaration);
    self = declaration_list;
  }
  return self;
}

AstRef ast_make_statement_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstStatementListRef data = ast_palloc(struct AstStatementList);
  data->statement_vector = ast_make_vector();
  self->tag = AST_STATEMENT_LIST;
  self->data.statement_list = data;
  return self;
}

AstRef ast_push_statement_list(AstRef statement_list, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_statement_list(statement_list) &&
      ast_is_statement(statement)) {
    AstStatementListRef data = ast_get_statement_list(statement_list);
    ast_push_vector(data->statement_vector, statement);
    self = statement_list;
  }
  return self;
}

AstRef ast_make_expression_statement(AstNullableRef expression) {
  AstRef self = NULL;
  if (expression == NULL || ast_is_expression(expression)) {
    AstExpressionStatementRef data = ast_palloc(struct AstExpressionStatement);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_EXPRESSION_STATEMENT;
    self->data.expression_statement = data;
  }
  return self;
}

AstRef ast_make_selection_statement(AstRef selection_statement) {
  AstRef self = NULL;
  if (ast_is_if_statement(selection_statement) ||
      ast_is_if_else_statement(selection_statement) ||
      ast_is_switch_statement(selection_statement)) {
    AstSelectionStatementRef data = ast_palloc(struct AstSelectionStatement);
    data->selection_statement = selection_statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_SELECTION_STATEMENT;
    self->data.selection_statement = data;
  }
  return self;
}

AstRef ast_make_if_statement(AstRef expression, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_expression(expression) && ast_is_statement(statement)) {
    AstIfStatementRef data = ast_palloc(struct AstIfStatement);
    data->expression = expression;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_IF_STATEMENT;
    self->data.if_statement = data;
  }
  return self;
}

AstRef ast_make_if_else_statement(
    AstRef expression, AstRef statement_if, AstRef statement_else) {
  AstRef self = NULL;
  if (ast_is_expression(expression) &&
      ast_is_statement(statement_if) &&
      ast_is_statement(statement_else)) {
    AstIfElseStatementRef data = ast_palloc(struct AstIfElseStatement);
    data->expression = expression;
    data->statement_if = statement_if;
    data->statement_else = statement_else;
    self = ast_palloc(struct Ast);
    self->tag = AST_IF_ELSE_STATEMENT;
    self->data.if_else_statement = data;
  }
  return self;
}

AstRef ast_make_switch_statement(AstRef expression, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_expression(expression) && ast_is_statement(statement)) {
    AstSwitchStatementRef data = ast_palloc(struct AstSwitchStatement);
    data->expression = expression;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_SWITCH_STATEMENT;
    self->data.switch_statement = data;
  }
  return self;
}

AstRef ast_make_iteration_statement(AstRef iteration_statement) {
  AstRef self = NULL;
  if (ast_is_while_statement(iteration_statement) ||
      ast_is_do_while_statement(iteration_statement) ||
      ast_is_for_statement(iteration_statement)) {
    AstIterationStatementRef data = ast_palloc(struct AstIterationStatement);
    data->iteration_statement = iteration_statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_ITERATION_STATEMENT;
    self->data.iteration_statement = data;
  }
  return self;
}

AstRef ast_make_while_statement(AstRef expression, AstRef statement) {
  AstRef self = NULL;
  if (ast_is_expression(expression) && ast_is_statement(statement)) {
    AstWhileStatementRef data = ast_palloc(struct AstWhileStatement);
    data->expression = expression;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_WHILE_STATEMENT;
    self->data.while_statement = data;
  }
  return self;
}

AstRef ast_make_do_while_statement(AstRef statement, AstRef expression) {
  AstRef self = NULL;
  if (ast_is_statement(statement) && ast_is_expression(expression)) {
    AstDoWhileStatementRef data = ast_palloc(struct AstDoWhileStatement);
    data->statement = statement;
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_DO_WHILE_STATEMENT;
    self->data.do_while_statement = data;
  }
  return self;
}

AstRef ast_make_for_statement(
    AstNullableRef expression_1, AstNullableRef expression_2,
    AstNullableRef expression_3, AstRef statement) {
  AstRef self = NULL;
  if ((expression_1 == NULL || ast_is_expression(expression_1)) &&
      (expression_2 == NULL || ast_is_expression(expression_2)) &&
      (expression_3 == NULL || ast_is_expression(expression_3)) &&
      ast_is_statement(statement)) {
    AstForStatementRef data = ast_palloc(struct AstForStatement);
    data->expression_1 = expression_1;
    data->expression_2 = expression_2;
    data->expression_3 = expression_3;
    data->statement = statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_FOR_STATEMENT;
    self->data.for_statement = data;
  }
  return self;
}

AstRef ast_make_jump_statement(AstRef jump_statement) {
  AstRef self = NULL;
  if (ast_is_goto_jump_statement(jump_statement) ||
      ast_is_continue_jump_statement(jump_statement) ||
      ast_is_break_jump_statement(jump_statement) ||
      ast_is_return_jump_statement(jump_statement) ||
      ast_is_void_return_jump_statement(jump_statement)) {
    AstJumpStatementRef data = ast_palloc(struct AstJumpStatement);
    data->jump_statement = jump_statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_JUMP_STATEMENT;
    self->data.jump_statement = data;
  }
  return self;
}

AstRef ast_make_goto_jump_statement(AstRef identifier) {
  AstRef self = NULL;
  if (ast_is_identifier(identifier)) {
    AstGotoJumpStatementRef data = ast_palloc(struct AstGotoJumpStatement);
    data->identifier = identifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_GOTO_JUMP_STATEMENT;
    self->data.goto_jump_statement = data;
  }
  return self;
}

AstRef ast_make_continue_jump_statement(void) {
  AstRef self = ast_palloc(struct Ast);
  AstContinueJumpStatementRef data = ast_palloc(struct AstContinueJumpStatement);
  data->self = self;
  self->tag = AST_CONTINUE_JUMP_STATEMENT;
  self->data.continue_jump_statement = data;
  return self;
}

AstRef ast_make_break_jump_statement(void) {
  AstRef self = ast_palloc(struct Ast);
  AstBreakJumpStatementRef data = ast_palloc(struct AstBreakJumpStatement);
  data->self = self;
  self->tag = AST_BREAK_JUMP_STATEMENT;
  self->data.break_jump_statement = data;
  return self;
}

AstRef ast_make_return_jump_statement(AstRef expression) {
  AstRef self = NULL;
  if (ast_is_expression(expression)) {
    AstReturnJumpStatementRef data = ast_palloc(struct AstReturnJumpStatement);
    data->expression = expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_RETURN_JUMP_STATEMENT;
    self->data.return_jump_statement = data;
  }
  return self;
}

AstRef ast_make_void_return_jump_statement(void) {
  AstRef self = ast_palloc(struct Ast);
  AstVoidReturnJumpStatementRef data = ast_palloc(struct AstVoidReturnJumpStatement);
  data->self = self;
  self->tag = AST_VOID_RETURN_JUMP_STATEMENT;
  self->data.void_return_jump_statement = data;
  return self;
}
