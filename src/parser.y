%{
%}

%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO
%token DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF
%token INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC
%token STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE

%token IDENTIFIER
%token INTEGER_CONSTANT
%token FLOATING_CONSTANT
%token CHARACTER_CONSTANT
%token STRING_LITERAL

%start translation-unit

%%

keyword
: AUTO | BREAK | CASE | CHAR | CONST | CONTINUE | DEFAULT | DO
| DOUBLE | ELSE | ENUM | EXTERN | FLOAT | FOR | GOTO | IF
| INT | LONG | REGISTER | RETURN | SHORT | SIGNED | SIZEOF | STATIC
| STRUCT | SWITCH | TYPEDEF | UNION | UNSIGNED | VOID | VOLATILE | WHILE
;

constant
: FLOATING_CONSTANT
| INTEGER_CONSTANT
| CHARACTER_CONSTANT
;

translation-unit
: external-declaration
| translation-unit external-declaration

external-declaration
: function-definition
/* | declaration */
;

function-definition
: declaration-specifiers.opt declarator declaration-list.opt compound-statement
%%
