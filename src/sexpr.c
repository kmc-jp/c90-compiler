#include "sexpr.h"
#include <assert.h>
#include "memory_pool.h"
#include "sexpr_pool.h"

static SexprRef new_sexpr(void) {
  return palloc(struct Sexpr, sexpr_pool(), 1);
}

SexprRef cons(SexprRef car, SexprRef cdr) {
  SexprRef sexpr = new_sexpr();
  sexpr->tag = SEXPR_CONS;
  sexpr->data.cons.car = car;
  sexpr->data.cons.cdr = cdr;
  return sexpr;
}
SexprRef car(SexprRef sexpr) {
  assert(sexpr_is_pair(sexpr));
  return sexpr->data.cons.car;
}
SexprRef cdr(SexprRef sexpr) {
  assert(sexpr_is_pair(sexpr));
  return sexpr->data.cons.cdr;
}

bool sexpr_is_null(SexprRef sexpr) {
  return sexpr == NULL;
}
bool sexpr_is_pair(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag == SEXPR_CONS;
}
bool sexpr_is_atom(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag != SEXPR_CONS;
}
bool sexpr_is_symbol(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag == SEXPR_SYMBOL;
}

SexprRef sexpr_make_symbol(StringRef symbol) {
  SexprRef sexpr = new_sexpr();
  sexpr->tag = SEXPR_SYMBOL;
  sexpr->data.symbol = symbol;
  return sexpr;
}
