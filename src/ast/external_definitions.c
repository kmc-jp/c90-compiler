#include "external_definitions.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstTranslationUnit {
  AstVectorRef external_declaration_vector;
};

struct AstExternalDeclaration {
};

struct AstFunctionDefinition {
};

AstRef ast_make_translation_unit() {
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
