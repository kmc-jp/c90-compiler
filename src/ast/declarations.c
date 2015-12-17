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
  AstRef pointer; /* NULLABLE */
  AstRef direct_declarator;
};

struct AstDirectDeclarator {
};

struct AstArrayDeclarator {
};

struct AstFunctionDeclarator {
};

struct AstOldStyleFunctionDeclarator {
};

struct AstPointer {
};

struct AstTypeQualifierList {
};

struct AstParameterTypeList {
};

struct AstVariadicParameterList {
};

struct AstParameterList {
};

struct AstParameterDeclaration {
};

struct AstParameterAbstractDeclaration {
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

AstRef ast_make_declarator(AstRef pointer, AstRef direct_declarator) {
  AstRef self = NULL;
  if ((pointer == NULL ||
       ast_is_pointer(pointer)) &&
      ast_is_direct_declarator(direct_declarator)) {
    AstDeclaratorRef data = ast_palloc(struct AstDeclarator);
    data->pointer = pointer;
    data->direct_declarator = direct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DECLARATOR;
    self->data.declarator = data;
  }
  return self;
}
