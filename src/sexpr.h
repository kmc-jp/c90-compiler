#ifndef KMC_C90_COMPILER_SEXPR_H
#define KMC_C90_COMPILER_SEXPR_H

struct Sexpr;
typedef struct Sexpr* SexprRef;

enum SexprTag {
  SEXPR_CONS
};

struct ConsData {
  SexprRef car;
  SexprRef cdr;
};

struct Sexpr {
  enum SexprTag tag;
  union Data {
    struct ConsData cons;  /* SEXPR_CONS */
  } data;
};

#endif  /* KMC_C90_COMPILER_SEXPR_H */
