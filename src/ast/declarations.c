#include "declarations.h"
#include "ast_impl.h"
#include "is_method.h"
#include "get_method.h"
#include "pool.h"

struct AstDeclaration {
};

struct AstDeclarationSpecifiers {
};

struct AstInitDeclaratorList {
};

struct AstInitDeclarator {
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
  AstRef initializer;
};

struct AstInitializerList {
  AstVectorRef initializer_vector;
};

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

AstRef ast_make_initializer(AstRef initializer) {
  AstRef self = NULL;
  if (ast_is_assignment_expression(initializer) ||
      ast_is_initializer_list(initializer)) {
    AstInitializerRef data = ast_palloc(struct AstInitializer);
    data->initializer = initializer;
    self = ast_palloc(struct Ast);
    self->tag = AST_INITIALIZER;
    self->data.initializer = data;
  }
  return self;
}

AstRef ast_make_initializer_list(AstRef initializer_list, AstRef initializer) {
  AstRef self = NULL;
  if (initializer_list == NULL) {
    AstInitializerListRef data = ast_palloc(struct AstInitializerList);
    data->initializer_vector = ast_make_vector();
    initializer_list = ast_palloc(struct Ast);
    initializer_list->tag = AST_INITIALIZER_LIST;
    initializer_list->data.initializer_list = data;
  }
  if (ast_is_initializer_list(initializer_list) &&
      ast_is_initializer(initializer)) {
    AstInitializerListRef data = ast_get_initializer_list(initializer_list);
    ast_push_vector(data->initializer_vector, initializer);
    self = initializer_list;
  }
  return self;
}
