#include "make_method.h"
#include <assert.h>
#include "ast_impl.h"
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
  {
    AstIdentifierRef data = ast_palloc(struct AstIdentifier);
    data->token = token;
  }
  return self;
}

AstRef ast_make_constant(AstRef constant) {
  AstRef self = NULL;
  assert(token);
  {
    AstConstantRef data = ast_palloc(struct AstConstant);
    data->constant = constant;
  }
  return self;
}

AstRef ast_make_floating_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  {
    AstFloatingConstantRef data = ast_palloc(struct AstFloatingConstant);
    data->token = token;
  }
  return self;
}

AstRef ast_make_integer_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  {
    AstIntegerConstantRef data = ast_palloc(struct AstIntegerConstant);
    data->token = token;
  }
  return self;
}

AstRef ast_make_enumeration_constant(AstRef identifier) {
  AstRef self = NULL;
  assert(token);
  {
    AstEnumerationConstantRef data = ast_palloc(struct AstEnumerationConstant);
    data->identifier = identifier;
  }
  return self;
}

AstRef ast_make_character_constant(AstRef token) {
  AstRef self = NULL;
  assert(token);
  {
    AstCharacterConstantRef data = ast_palloc(struct AstCharacterConstant);
    data->token = token;
  }
  return self;
}

AstRef ast_make_string_literal(AstRef token) {
  AstRef self = NULL;
  assert(token);
  {
    AstStringLiteralRef data = ast_palloc(struct AstStringLiteral);
    data->token = token;
  }
  return self;
}
