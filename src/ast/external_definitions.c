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
