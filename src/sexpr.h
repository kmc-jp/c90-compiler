#ifndef KMC_C90_COMPILER_SEXPR_H
#define KMC_C90_COMPILER_SEXPR_H

struct Sexpr;
typedef struct Sexpr* SexprRef;

struct ConsData {
  SexprRef car;
  SexprRef cdr;
};

#endif  /* KMC_C90_COMPILER_SEXPR_H */
