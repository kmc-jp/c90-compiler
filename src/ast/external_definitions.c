#include "external_definitions.h"
#include "external_definitions_impl.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

AstRef ast_make_translation_unit(void) {
  AstRef self = ast_palloc(struct Ast);
  AstTranslationUnitRef data = ast_palloc(struct AstTranslationUnit);
  data->external_declaration_vector = ast_make_vector();
  self->tag = AST_TRANSLATION_UNIT;
  self->data.translation_unit = data;
  return self;
}

AstRef ast_push_translation_unit(
    AstRef translation_unit, AstRef external_declaration) {
  AstRef self = NULL;
  if (ast_is_translation_unit(translation_unit) &&
      ast_is_external_declaration(external_declaration)) {
    AstTranslationUnitRef data = ast_get_translation_unit(translation_unit);
    ast_push_vector(data->external_declaration_vector, external_declaration);
    self = translation_unit;
  }
  return self;
}

AstRef ast_make_external_declaration(AstRef external_declaration) {
  AstRef self = NULL;
  if (ast_is_function_definition(external_declaration) ||
      ast_is_declaration(external_declaration)) {
    AstExternalDeclarationRef data = ast_palloc(struct AstExternalDeclaration);
    data->external_declaration = external_declaration;
    self = ast_palloc(struct Ast);
    self->tag = AST_EXTERNAL_DECLARATION;
    self->data.external_declaration = data;
  }
  return self;
}

AstRef ast_make_function_definition(
    AstRef declaration_specifier_list, AstRef declarator,
    AstRef declaration_list, AstRef compound_statement) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_declarator(declarator) &&
      ast_is_declaration_list(declaration_list) &&
      ast_is_compound_statement(compound_statement)) {
    AstFunctionDefinitionRef data = ast_palloc(struct AstFunctionDefinition);
    data->declaration_specifier_list = declaration_specifier_list;
    data->declarator = declarator;
    data->declaration_list = declaration_list;
    data->compound_statement = compound_statement;
    self = ast_palloc(struct Ast);
    self->tag = AST_FUNCTION_DEFINITION;
    self->data.function_definition = data;
  }
  return self;
}
