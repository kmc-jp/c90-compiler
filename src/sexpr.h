#ifndef INCLUDE_GUARD_UUID_DC32CCE0_A68D_4F17_8621_17C2E13F96F3
#define INCLUDE_GUARD_UUID_DC32CCE0_A68D_4F17_8621_17C2E13F96F3

#include "ast.h"
#include "stdstring.h"
#include "utility.h"

struct Sexpr;
typedef struct Sexpr* SexprRef;

enum SexprTag {
  SEXPR_CONS, SEXPR_SYMBOL, SEXPR_AST
};

struct ConsData {
  SexprRef car;
  SexprRef cdr;
};

struct Sexpr {
  enum SexprTag tag;
  union Data {
    struct ConsData cons;  /* SEXPR_CONS */
    StringRef symbol;      /* SEXPR_SYMBOL */
    enum AstTag ast;       /* SEXPR_AST */
  } data;
};

SexprRef cons(SexprRef car, SexprRef cdr);
SexprRef car(SexprRef sexpr);
SexprRef cdr(SexprRef sexpr);

bool sexpr_is_null(SexprRef sexpr);
bool sexpr_is_pair(SexprRef sexpr);
bool sexpr_is_atom(SexprRef sexpr);
bool sexpr_is_symbol(SexprRef sexpr);
bool sexpr_is_ast(SexprRef sexpr);

SexprRef sexpr_new_symbol(const char* src, size_t length);
SexprRef sexpr_make_symbol(StringRef symbol);
StringRef sexpr_get_symbol(SexprRef sexpr);

SexprRef sexpr_make_ast(enum AstTag ast);
enum AstTag sexpr_get_ast(SexprRef sexpr);

#endif  /* INCLUDE_GUARD_UUID_DC32CCE0_A68D_4F17_8621_17C2E13F96F3 */
