#include "sexpr.h"

bool sexpr_is_null(SexprRef sexpr) {
  return sexpr == NULL;
}
bool sexpr_is_pair(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag == SEXPR_CONS;
}
