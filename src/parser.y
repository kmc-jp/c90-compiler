%code {
#include <stdio.h>
void yyerror(const char *);
}

%code provides {
int yylex(void);
}

%code requires {
#include "ast.h"
}

%define api.value.type { AstRef }

%token IDENTIFIER
%token INTEGER_CONSTANT
%token FLOATING_CONSTANT
%token CHARACTER_CONSTANT
%token STRING_LITERAL

%%

identifier
: IDENTIFIER
;

constant
: FLOATING_CONSTANT
| INTEGER_CONSTANT
| CHARACTER_CONSTANT
;

string-literal
: STRING_LITERAL
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
