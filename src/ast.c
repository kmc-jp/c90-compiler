#include "ast.h"

struct Ast {
  enum AstTag tag;
  union AstData {
  } data;
};
