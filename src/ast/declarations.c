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
  AstRef direct_declarator;
};

struct AstArrayDeclarator {
  AstRef direct_declarator;
  AstRef constant_expression; /* NULLABLE */
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

AstRef ast_make_direct_declarator(AstRef direct_declarator) {
  AstRef self = NULL;
  if (ast_is_identifier(direct_declarator) ||
      ast_is_declarator(direct_declarator) ||
      ast_is_array_declarator(direct_declarator) ||
      ast_is_function_declarator(direct_declarator)) {
    AstDirectDeclaratorRef data = ast_palloc(struct AstDirectDeclarator);
    data->direct_declarator = direct_declarator;
    self = ast_palloc(struct Ast);
    self->tag = AST_DIRECT_DECLARATOR;
    self->data.direct_declarator = data;
  }
  return self;
}

AstRef ast_make_array_declarator(AstRef direct_declarator,
    AstRef constant_expression) {
  AstRef self = NULL;
  if (ast_is_direct_declarator(direct_declarator) &&
      (constant_expression == NULL ||
       ast_is_constant_expression(constant_expression))) {
    AstArrayDeclaratorRef data = ast_palloc(struct AstArrayDeclarator);
    data->direct_declarator = direct_declarator;
    data->constant_expression = constant_expression;
    self = ast_palloc(struct Ast);
    self->tag = AST_ARRAY_DECLARATOR;
    self->data.array_declarator = data;
  }
  return self;
}
