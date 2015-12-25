#include "statements.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstStatement {
  AstRef statement;
};

struct AstLabeledStatement {
};

struct AstIdentifierLabeledStatement {
};

struct AstCaseLabeledStatement {
};

struct AstDefaultLabeledStatement {
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
