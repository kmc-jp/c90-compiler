#include "declarations.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstDeclaration {
  AstRef declaration_specifier_list;
  AstRef init_declarator_list;
};

struct AstDeclarationSpecifierList {
  AstVectorRef declaration_specifier_vector;
};

struct AstDeclarationSpecifier {
  AstRef declaration_specifier;
};

struct AstInitDeclaratorList {
  AstVectorRef init_declarator_vector;
};

struct AstInitDeclarator {
  AstRef init_declarator;
};

struct AstDeclaratorWithInitializer {
  AstRef declarator;
  AstRef initializer;
};

struct AstStorageClassSpecifier {
  AstRef storage_class_specifier;
};

struct AstTypeSpecifier {
};

struct AstStructOrUnionSpecifier {
};

struct AstStructOrUnion {
};

struct AstStructDeclarationList {
};

struct AstStructDeclaration {
};

struct AstSpecifierQualifierList {
};

struct AstStructDeclaratorList {
};

struct AstStructDeclarator {
};

struct AstEnumSpecifier {
};

struct AstEnumeratorList {
};

struct AstEnumerator {
};

struct AstTypeQualifier {
};

struct AstDeclarator {
};

struct AstDirectDeclarator {
};

struct AstPointer {
};

struct AstTypeQualifierList {
};

struct AstParameterTypeList {
};

struct AstParameterList {
};

struct AstParameterDeclaration {
};

struct AstIdentifierList {
};

struct AstTypeName {
};

struct AstAbstractDeclarator {
};

struct AstDirectAbstractDeclarator {
};

struct AstTypedefName {
};

struct AstInitializer {
};

struct AstInitializerList {
};

AstRef ast_make_declaration(AstRef declaration_specifier_list, AstRef init_declarator_list) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_init_declarator_list(init_declarator_list)) {
    AstDeclarationRef data = ast_palloc(struct AstDeclaration);
    data->declaration_specifier_list = declaration_specifier_list;
    data->init_declarator_list = init_declarator_list;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATION;
    self->data.declaration = data;
  }
  return self;
}

AstRef ast_make_declaration_specifier_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstDeclarationSpecifierListRef data = ast_palloc(struct AstDeclarationSpecifierList);
  data->declaration_specifier_vector = ast_make_vector();
  self->tag = AST_DECLARATION_SPECIFIER_LIST;
  self->data.declaration_specifier_list = data;
  return self;
}

AstRef ast_push_declaration_specifier_list(
    AstRef declaration_specifier_list, AstRef declaration_specifier) {
  AstRef self = NULL;
  if (ast_is_declaration_specifier_list(declaration_specifier_list) &&
      ast_is_declaration_specifier(declaration_specifier)) {
    AstDeclarationSpecifierListRef data =
        ast_get_declaration_specifier_list(declaration_specifier_list);
    ast_push_vector(data->declaration_specifier_vector, declaration_specifier);
    self = declaration_specifier_list;
  }
  return self;
}

AstRef ast_make_declaration_specifier(AstRef declaration_specifier) {
  AstRef self = NULL;
  if (ast_is_storage_class_specifier(declaration_specifier) ||
      ast_is_type_specifier(declaration_specifier) ||
      ast_is_type_qualifier(declaration_specifier)) {
    AstDeclarationSpecifierRef data = ast_palloc(struct AstDeclarationSpecifier);
    data->declaration_specifier = declaration_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATION_SPECIFIER;
    self->data.declaration_specifier = data;
  }
  return self;
}

AstRef ast_make_init_declarator_list(void) {
  AstRef self = ast_palloc(struct Ast);
  AstInitDeclaratorListRef data = ast_palloc(struct AstInitDeclaratorList);
  data->init_declarator_vector = ast_make_vector();
  self->tag = AST_INIT_DECLARATOR_LIST;
  self->data.init_declarator_list = data;
  return self;
}

AstRef ast_push_init_declarator_list(
    AstRef init_declarator_list, AstRef init_declarator) {
  AstRef self = NULL;
  if (ast_is_init_declarator_list(init_declarator_list) &&
      ast_is_init_declarator(init_declarator)) {
    AstInitDeclaratorListRef data = ast_get_init_declarator_list(init_declarator_list);
    ast_push_vector(data->init_declarator_vector, init_declarator);
    self = init_declarator_list;
  }
  return self;
}

AstRef ast_make_init_declarator(AstRef init_declarator) {
  AstRef self = NULL;
  if (ast_is_declarator(init_declarator) ||
      ast_is_declarator_with_initializer(init_declarator)) {
    AstInitDeclaratorRef data = ast_palloc(struct AstInitDeclarator);
    data->init_declarator = init_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_INIT_DECLARATOR;
    self->data.init_declarator = data;
  }
  return self;
}

AstRef ast_make_declarator_with_initializer(
    AstRef declarator, AstRef initializer) {
  AstRef self = NULL;
  if (ast_is_declarator(declarator) && ast_is_initializer(initializer)) {
    AstDeclaratorWithInitializerRef data = ast_palloc(struct AstDeclaratorWithInitializer);
    data->declarator = declarator;
    data->initializer = initializer;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATOR_WITH_INITIALIZER;
    self->data.declarator_with_initializer = data;
  }
  return self;
}

AstRef ast_make_storage_class_specifier(AstRef storage_class_specifier) {
  AstRef self = NULL;
  if (ast_is_token(storage_class_specifier)) {
    AstStorageClassSpecifierRef data = ast_palloc(struct AstStorageClassSpecifier);
    data->storage_class_specifier = storage_class_specifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_STORAGE_CLASS_SPECIFIER;
    self->data.storage_class_specifier = data;
  }
  return self;
}
