#ifndef KMC_C90_COMPILER_SEXPR_H
#define KMC_C90_COMPILER_SEXPR_H

#include "stdstring.h"
#include "utility.h"

struct Sexpr;
typedef struct Sexpr* SexprRef;

enum SexprTag {
  SEXPR_CONS, SEXPR_SYMBOL
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
  } data;
};

SexprRef cons(SexprRef car, SexprRef cdr);
SexprRef car(SexprRef sexpr);
SexprRef cdr(SexprRef sexpr);

bool sexpr_is_null(SexprRef sexpr);
bool sexpr_is_pair(SexprRef sexpr);
bool sexpr_is_atom(SexprRef sexpr);
bool sexpr_is_symbol(SexprRef sexpr);

SexprRef sexpr_make_symbol(StringRef symbol);
StringRef sexpr_get_symbol(SexprRef sexpr);

#endif  /* KMC_C90_COMPILER_SEXPR_H */
