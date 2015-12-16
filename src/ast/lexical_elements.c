#include "make_method.h"
#include <assert.h>
#include "ast_impl.h"
#include "is_method.h"
#include "pool.h"

struct AstIdentifier {
  AstRef token;
};

struct AstConstant {
  AstRef constant;
};

struct AstFloatingConstant {
  AstRef token;
};

struct AstIntegerConstant {
  AstRef token;
};

struct AstEnumerationConstant {
  AstRef identifier;
};

struct AstCharacterConstant {
  AstRef token;
};

struct AstStringLiteral {
  AstRef token;
};

AstRef ast_make_identifier(AstRef token) {
  AstRef self = NULL;
  assert(token);
  if (ast_is_token(token)) {
    AstIdentifierRef data = ast_palloc(struct AstIdentifier);
    data->token = token;
    self = ast_palloc(struct Ast);
    self->tag = AST_IDENTIFIER;
    self->data.identifier = data;
  }
  return self;
}

AstRef ast_make_constant(AstRef constant) {
  AstRef self = NULL;
  assert(constant);
  if (ast_is_floating_constant(constant) ||
      ast_is_integer_constant(constant) ||
      ast_is_enumeration_constant(constant) ||
      ast_is_character_constant(constant)) {
    AstConstantRef data = ast_palloc(struct AstConstant);
    data->constant = constant;
    self = ast_palloc(struct Ast);
    self->tag = AST_CONSTANT;
    self->data.constant = data;
  }
  return self;
}

AstRef ast_make_floating_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  if (ast_is_token(token)) {
    AstFloatingConstantRef data = ast_palloc(struct AstFloatingConstant);
    data->token = token;
    self = ast_palloc(struct Ast);
    self->tag = AST_FLOATING_CONSTANT;
    self->data.floating_constant = data;
  }
  return self;
}

AstRef ast_make_integer_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  if (ast_is_token(token)) {
    AstIntegerConstantRef data = ast_palloc(struct AstIntegerConstant);
    data->token = token;
    self = ast_palloc(struct Ast);
    self->tag = AST_INTEGER_CONSTANT;
    self->data.integer_constant = data;
  }
  return self;
}

AstRef ast_make_enumeration_constant(AstRef identifier) {
  AstRef self = NULL;
  assert(identifier);
  if (ast_is_identifier(identifier)) {
    AstEnumerationConstantRef data = ast_palloc(struct AstEnumerationConstant);
    data->identifier = identifier;
    self = ast_palloc(struct Ast);
    self->tag = AST_ENUMERATION_CONSTANT;
    self->data.enumeration_constant = data;
  }
  return self;
}

AstRef ast_make_character_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  if (ast_is_token(token)) {
    AstCharacterConstantRef data = ast_palloc(struct AstCharacterConstant);
    data->token = token;
    self = ast_palloc(struct Ast);
    self->tag = AST_CHARACTER_CONSTANT;
    self->data.character_constant = data;
  }
  return self;
}

AstRef ast_make_string_literal(AstRef token) {
  AstRef self = NULL;
  assert(token);
  if (ast_is_token(token)) {
    AstStringLiteralRef data = ast_palloc(struct AstStringLiteral);
    data->token = token;
    self = ast_palloc(struct Ast);
    self->tag = AST_STRING_LITERAL;
    self->data.string_literal = data;
  }
  return self;
}
