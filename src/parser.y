%{
%}

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
