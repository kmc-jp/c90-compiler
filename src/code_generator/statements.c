#include "code_generator.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

void build_block_compound_statement(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstCompoundStatementRef compound_statement) {
  build_block(module, builder, compound_statement->declaration_list);
  build_block(module, builder, compound_statement->statement_list);
}

void build_block_declaration_list(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstDeclarationListRef declaration_list) {
  AstVectorRef declaration_vector = declaration_list->declaration_vector;
  int i;
  for (i = 0; i < AST_VECTOR_FUNC(size)(declaration_vector); i++) {
    build_block(AST_VECTOR_FUNC(at)(declaration_vector, i));
  }
}

void build_block_statement_list(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstStatementListRef statement_list) {
  AstVectorRef statement_vector = statement_list->statement_vector;
  int i;
  for (i = 0; i < AST_VECTOR_FUNC(size)(statement_vector); i++) {
    build_block(AST_VECTOR_FUNC(at)(statement_vector, i));
  }
}

void build_block_statement_list(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstStatementListRef statement_list) {
}

void build_block_statement(
    LLVMModuleRef module, LLVMBuilderRef builder,
    AstStatement statement) {
}

void build_block(LLVMModuleRef module, LLVMBuilderRef builder, AstRef ast) {
  switch (ast->tag) {
    case AST_COMPOUND_STATEMENT:
      build_block_compound_statement(module, builder, ast_get_compound_statement(ast)); break;
    case AST_DECLARATION_LIST:
      build_block_declaration_list(module, builder, ast_get_declaration_list(ast)); break;
    case AST_STATEMENT_LIST:
      build_block_statement_list(module, builder, ast_get_statement_list(ast)); break;
    case AST_STATEMENT:
      build_block_statement(module, builder, ast_get_statement(ast)); break;
    default:
  }
}
