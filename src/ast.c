#include "ast.h"

struct Ast {
  enum AstTag tag;
  union AstData {
    char* null_terminated;
  } data;
};
