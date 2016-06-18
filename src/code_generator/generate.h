#ifndef KMC_C90_COMPILER_CODE_GENERATOR_GENERATE_H
#define KMC_C90_COMPILER_CODE_GENERATOR_GENERATE_H

#include "ast.h"

void generate_code(AstRef ast);
void error(const char* message, ...);

#endif  /* KMC_C90_COMPILER_CODE_GENERATOR_GENERATE_H */
