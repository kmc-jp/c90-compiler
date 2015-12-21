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
  AstRef specifier_qualifier_list;
  AstNullableRef abstract_declarator;
};

struct AstAbstractDeclarator {
  AstRef abstract_declarator;
};

struct AstNotPurePointerAbstractDeclarator {
};

struct AstDirectAbstractDeclarator {
};

struct AstArrayAbstractDeclarator {
};

struct AstFunctionAbstractDeclarator {
};

struct AstTypedefName {
};

struct AstInitializer {
};

struct AstInitializerList {
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

AstRef ast_make_type_name(AstRef specifier_qualifier_list,
    AstNullableRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_specifier_qualifier_list(specifier_qualifier_list) &&
      ast_is_abstract_declarator(abstract_declarator)) {
    AstTypeNameRef data = ast_palloc(struct AstTypeName);
    data->specifier_qualifier_list = specifier_qualifier_list;
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_TYPE_NAME;
    self->data.type_name = data;
  }
  return self;
}

AstRef ast_make_abstract_declarator(AstRef abstract_declarator) {
  AstRef self = NULL;
  if (ast_is_pointer(abstract_declarator) ||
      ast_is_not_pure_pointer_abstract_declarator(abstract_declarator)) {
    AstAbstractDeclaratorRef data = ast_palloc(struct AstAbstractDeclarator);
    data->abstract_declarator = abstract_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_ABSTRACT_DECLARATOR;
    self->data.abstract_declarator = data;
  }
  return self;
}
