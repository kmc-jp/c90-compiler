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

/* 6.5 Declarations */
declaration-specifiers
:
/* : storage-class-specifier declaration-specifiers.opt */
     type-specifier declaration-specifiers.opt
/* | type-specifier declaration-specifiers.opt */
/* | type-qualifier declaration-specifiers.opt */
;

declaration-specifiers.opt
: %empty
| declaration-specifiers
;

/* 6.5.2 Type specifiers */
type-specifier
: VOID
| CHAR
| SHORT
| INT
| LONG
| FLOAT
| DOUBLE
| SIGNED
| UNSIGNED
/* | struct-or-union-specifier */
/* | enum-specifier */
/* | typedef-name */
;

/* 6.5.4 Declarators */
declarator
: pointer.opt direct-declarator
;

direct-declarator
: IDENTIFIER
/* | '{' declarator '}' */
/* | direct-declarator '[' constant-expression.opt ']' */
| direct-declarator '(' parameter-type-list ')'
/* | direct-declarator '(' identifier-list.opt')' */
;

pointer.opt
: %empty
/* | pointer */
;

parameter-type-list
: parameter-list
/* | parameter-list ',' "..." */
;

parameter-list
: parameter-declaration
| parameter-list ',' parameter-declaration
;

parameter-declaration
: declaration-specifiers declarator
/* | declaration-specifiers abstract-declarator.opt */
;

/* 6.6.2 Compound statement, or block */
declaration-list.opt
: %empty
/* | declaration-list */
;

/* 6.7 External definitions */
translation-unit
: external-declaration
| translation-unit external-declaration

external-declaration
: function-definition
/* | declaration */
;

/* 6.7.1 Function definitions */
function-definition
: declaration-specifiers.opt declarator declaration-list.opt compound-statement

%%
