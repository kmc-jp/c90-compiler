#include "code_generator.h"
#include "variable_set.h"
#include "ast/statements_impl.h"
#include "ast/declarations_impl.h"
#include "ast/is_method.h"
#include "ast/get_method.h"
#include "ast/ast_impl.h"

void build_block_with_type(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstRef ast);

void build_block_with_type_init_declarator_list(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstInitDeclaratorListRef init_declarator_list) {
  AstVectorRef vector = init_declarator_list->init_declarator_vector;
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(vector);
  AstRef *end = AST_VECTOR_FUNC(end)(vector);
  for (itr = begin; itr != end; itr++) {
    build_block_with_type(module, builder, variable_set, base_type, *itr);
  }
}

void build_block_with_type_init_declarator(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstInitDeclaratorRef init_declarator) {
  build_block_with_type(
      module, builder, variable_set, base_type,
      init_declarator->init_declarator);
}

void build_block_with_type_declarator(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstDeclaratorRef declarator) {
  AstTokenRef name = get_name(declarator->direct_declarator);
  LLVMTypeRef type = base_type; /* get_type_with_type(declarator->direct_declarator); */
  LLVMValueRef variable = LLVMGetUndef(type);
  LLVMSetValueName(variable, string_data(name));
  ValueVectorFunc(push_back)(variable_set, variable);
}

void build_block_with_type_declarator_with_initializer(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstDeclaratorWithInitializerRef declarator) {
  AstTokenRef name = get_name(declarator->declarator);
  LLVMTypeRef type = base_type; /* get_type_with_type(declarator->declarator); */
  LLVMValueRef variable = make_value(module, builder, variable_set, type, declarator->initializer);
  LLVMSetValueName(variable, string_data(name));
  ValueVectorFunc(push_back)(variable_set, variable);
}

void build_block_with_type(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    LLVMTypeRef base_type, AstRef ast) {
  switch (ast->tag) {
    case AST_INIT_DECLARATOR_LIST:
      build_block_with_type_init_declarator_list(
          module, builder, variable_set, base_type,
          ast_get_init_declarator_list(ast));
      break;
    case AST_INIT_DECLARATOR:
      build_block_with_type_init_declarator(
          module, builder, variable_set, base_type,
          ast_get_init_declarator(ast));
      break;
    case AST_DECLARATOR:
      build_block_with_type_declarator(
          module, builder, variable_set, base_type,
          ast_get_declarator(ast));
      break;
    case AST_DECLARATOR_WITH_INITIALIZER:
      build_block_with_type_declarator_with_initializer(
          module, builder, variable_set, base_type,
          ast_get_declarator_with_initializer(ast));
      break;
    default:;
  }
}

void build_block_compound_statement(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstCompoundStatementRef compound_statement) {
  build_block(module, builder, variable_set, compound_statement->declaration_list);
  build_block(module, builder, variable_set, compound_statement->statement_list);
}

void build_block_declaration_list(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstDeclarationListRef declaration_list) {
  AstVectorRef declaration_vector = declaration_list->declaration_vector;
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(declaration_vector);
  AstRef *end = AST_VECTOR_FUNC(end)(declaration_vector);
  for (itr = begin; itr != end; itr++) {
    build_block(module, builder, variable_set, *itr);
  }
}

void build_block_declaration(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstDeclarationRef declaration) {
  LLVMTypeRef type = get_type(declaration->declaration_specifier_list);
  build_block_with_type(module, builder, variable_set, type, declaration->init_declarator_list);
}

void build_block_statement_list(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstStatementListRef statement_list) {
  AstVectorRef statement_vector = statement_list->statement_vector;
  AstRef *itr;
  AstRef *begin = AST_VECTOR_FUNC(begin)(statement_vector);
  AstRef *end = AST_VECTOR_FUNC(end)(statement_vector);
  for (itr = begin; itr != end; itr++) {
    build_block(module, builder, variable_set, *itr);
  }
}

void build_block_statement(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstStatementRef statement) {
  build_block(module, builder, variable_set, statement->statement);
}

void build_block_expression_statement(
    LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set,
    AstExpressionStatementRef expression_statement) {
  if (expression_statement->expression != NULL)
    build_expression(module, builder, variable_set, expression_statement->expression);
}

void build_block(LLVMModuleRef module, LLVMBuilderRef builder, ValueVectorRef variable_set, AstRef ast) {
  switch (ast->tag) {
    case AST_COMPOUND_STATEMENT:
      build_block_compound_statement(module, builder, variable_set, ast_get_compound_statement(ast)); break;
    case AST_DECLARATION_LIST:
      build_block_declaration_list(module, builder, variable_set, ast_get_declaration_list(ast)); break;
    case AST_DECLARATION:
      build_block_declaration(module, builder, variable_set, ast_get_declaration(ast)); break;
    case AST_STATEMENT_LIST:
      build_block_statement_list(module, builder, variable_set, ast_get_statement_list(ast)); break;
    case AST_STATEMENT:
      build_block_statement(module, builder, variable_set, ast_get_statement(ast)); break;
    case AST_EXPRESSION_STATEMENT:
      build_block_expression_statement(module, builder, variable_set, ast_get_expression_statement(ast)); break;
    default:;
  }
}
