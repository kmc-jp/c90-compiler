#ifndef KMC_C90_COMPILER_AST_STATEMENTS_IMPL_H
#define KMC_C90_COMPILER_AST_STATEMENTS_IMPL_H

#include "ast.h"

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
  AstNullableRef expression;
};

struct AstSelectionStatement {
  AstRef selection_statement;
};

struct AstIfStatement {
  AstRef expression;
  AstRef statement;
};

struct AstIfElseStatement {
  AstRef expression;
  AstRef statement_if;
  AstRef statement_else;
};

struct AstSwitchStatement {
  AstRef expression;
  AstRef statement;
};

struct AstIterationStatement {
  AstRef iteration_statement;
};

struct AstWhileStatement {
  AstRef expression;
  AstRef statement;
};

struct AstDoWhileStatement {
  AstRef statement;
  AstRef expression;
};

struct AstForStatement {
  AstNullableRef expression_1;
  AstNullableRef expression_2;
  AstNullableRef expression_3;
  AstRef statement;
};

struct AstJumpStatement {
  AstRef jump_statement;
};

struct AstGotoJumpStatement {
  AstRef identifier;
};

struct AstContinueJumpStatement {
  AstRef self;
};

struct AstBreakJumpStatement {
  AstRef self;
};

struct AstReturnJumpStatement {
  AstRef expression;
};

struct AstVoidReturnJumpStatement {
  AstRef self;
};

#endif  /* KMC_C90_COMPILER_AST_STATEMENTS_IMPL_H */
