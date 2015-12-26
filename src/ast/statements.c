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
};

struct AstDeclarationList {
};

struct AstStatementList {
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
