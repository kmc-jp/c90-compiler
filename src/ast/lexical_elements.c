#include "make_method.h"
#include <assert.h>
#include <stddef.h>
#include "../ast.h"

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
  return self;
}

AstRef ast_make_constant(AstRef constant) {
  AstRef self = NULL;
  assert(token);
  return self;
}

AstRef ast_make_floating_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  return self;
}

AstRef ast_make_integer_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  return self;
}

AstRef ast_make_enumeration_constant(AstRef identifier) {
  AstRef self = NULL;
  assert(token);
  return self;
}

AstRef ast_make_character_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  return self;
}

AstRef ast_make_string_literal(AstRef token) {
  AstRef self = NULL;
  assert(token);
  return self;
}
