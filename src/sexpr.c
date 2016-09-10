#include "sexpr.h"
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

bool sexpr_is_null(SexprRef sexpr) {
  return sexpr == NULL;
}
bool sexpr_is_pair(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag == SEXPR_CONS;
}
bool sexpr_is_atom(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag != SEXPR_CONS;
}
