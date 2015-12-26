#include "statements.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstStatement {
  AstRef statement;
};

struct AstLabeledStatement {
  AstRef labeled_statement;
};

struct AstIdentifierLabeledStatement {
  AstRef identifier;
  AstRef statement;
};

struct AstCaseLabeledStatement {
  AstRef constant_expression;
  AstRef statement;
};

struct AstDefaultLabeledStatement {
  AstRef statement;
};

struct AstCompoundStatement {
  AstRef declaration_list;
  AstRef statement_list;
};

struct AstDeclarationList {
  AstVectorRef declaration_vector;
};

struct AstStatementList {
  AstVectorRef statement_vector;
};

struct AstExpressionStatement {
};

struct AstSelectionStatement {
};

struct AstIterationStatement {
};

struct AstJumpStatement {
};

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
