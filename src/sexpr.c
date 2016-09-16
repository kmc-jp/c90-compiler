#include "sexpr.h"
#include <assert.h>
#include "allocator.h"
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
bool sexpr_is_ast(SexprRef sexpr) {
  return !sexpr_is_null(sexpr) && sexpr->tag == SEXPR_AST;
}

SexprRef sexpr_new_symbol(const char* src, size_t length) {
  AllocatorRef allocator = sexpr_symbol_allocator();
  StringRef string = make_string(src, length, allocator);
  return sexpr_make_symbol(string);
}
SexprRef sexpr_make_symbol(StringRef symbol) {
  SexprRef sexpr = new_sexpr();
  sexpr->tag = SEXPR_SYMBOL;
  sexpr->data.symbol = symbol;
  return sexpr;
}
StringRef sexpr_get_symbol(SexprRef sexpr) {
  assert(sexpr_is_symbol(sexpr));
  return sexpr->data.symbol;
}

SexprRef sexpr_make_ast(enum AstTag ast) {
  SexprRef sexpr = new_sexpr();
  sexpr->tag = SEXPR_AST;
  sexpr->data.ast = ast;
  return sexpr;
}
enum AstTag sexpr_get_ast(SexprRef sexpr) {
  assert(sexpr_is_ast(sexpr));
  return sexpr->data.ast;
}

static void indent(FILE* stream, int depth) {
  int i = 0;
  for (; i < depth; ++i) {
    fprintf(stream, " ");
  }
}
static void sexpr_print_impl(FILE* stream, SexprRef sexpr, int depth) {
  if (sexpr_is_pair(sexpr)) {
    if (sexpr_is_atom(car(sexpr))) {
      sexpr_print_impl(stream, car(sexpr), depth);
    } else {
      fprintf(stream, "(");
      sexpr_print_impl(stream, car(sexpr), depth + 1);
      fprintf(stream, ")");
    }
    if (sexpr_is_atom(cdr(sexpr))) {
      fprintf(stream, " . ");
      sexpr_print_impl(stream, cdr(sexpr), depth + 3);
    } else if (sexpr_is_pair(cdr(sexpr))) {
      fprintf(stream, "\n");
      indent(stream, depth);
      sexpr_print_impl(stream, cdr(sexpr), depth);
    }
  } else if (sexpr_is_symbol(sexpr)) {
    fprintf(stream, "%s", string_data(sexpr_get_symbol(sexpr)));
  } else if (sexpr_is_ast(sexpr)) {
    fprintf(stream, "%s", ast_info(sexpr_get_ast(sexpr)));
  }
}
void sexpr_print(FILE* stream, SexprRef sexpr) {
  if (sexpr_is_atom(sexpr)) {
    sexpr_print_impl(stream, sexpr, 0);
  } else {
    fprintf(stream, "(");
    sexpr_print_impl(stream, sexpr, 1);
    fprintf(stream, ")\n");
  }
}
