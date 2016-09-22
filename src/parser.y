%code {
void yyerror(const char *);
}

%code provides {
int yylex(void);
void set_yyin_file(FILE* fp);
void set_yyin_string(const char *code);
}

%code requires {
#include <stdio.h>
#include "sexpr.h"
#define YYSTYPE SexprRef
}

%token TYPENAME
%token IDENTIFIER
%token FLOATING_CONSTANT
%token INTEGER_CONSTANT
%token CHARACTER_CONSTANT
%token STRING_LITERAL
%token ARROW "->"
%token INCREMENT "++"
%token DECREMENT "--"
%token LEFT_SHIFT "<<"
%token RIGHT_SHIFT ">>"
%token EQUAL "=="
%token NOT_EQUAL "!="
%token LESS_EQUAL "<="
%token GREATER_EQUAL ">="
%token AND "&&"
%token OR "||"
%token ADD_ASSIGN "+="
%token SUB_ASSIGN "-="
%token MUL_ASSIGN "*="
%token DIV_ASSIGN "/="
%token MOD_ASSIGN "%="
%token LEFT_SHIFT_ASSIGN "<<="
%token RIGHT_SHIFT_ASSIGN ">>="
%token AND_ASSIGN "&="
%token OR_ASSIGN "|="
%token XOR_ASSIGN "^="
%token ELLIPSIS "..."
%token AUTO "auto"
%token BREAK "break"
%token CASE "case"
%token CHAR "char"
%token CONST "const"
%token CONTINUE "continue"
%token DEFAULT "default"
%token DO "do"
%token DOUBLE "double"
%token ELSE "else"
%token ENUM "enum"
%token EXTERN "extern"
%token FLOAT "float"
%token FOR "for"
%token GOTO "goto"
%token IF "if"
%token INT "int"
%token LONG "long"
%token REGISTER "register"
%token RETURN "return"
%token SHORT "short"
%token SIGNED "signed"
%token SIZEOF "sizeof"
%token STATIC "static"
%token STRUCT "struct"
%token SWITCH "switch"
%token TYPEDEF "typedef"
%token UNION "union"
%token UNSIGNED "unsigned"
%token VOID "void"
%token VOLATILE "volatile"
%token WHILE "while"

%precedence ONLY_IF
%precedence ELSE

%start translation-unit

%%

typedef-name
: TYPENAME
;

identifier.opt
: %empty
| IDENTIFIER
;

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

primary-expression
: identifier
| constant
| string-literal
| '(' expression ')'
;

postfix-expression
: primary-expression
| postfix-expression '[' expression ']'
| postfix-expression '(' ')'
| postfix-expression '(' argument-expression-list ')'
| postfix-expression '.' identifier
| postfix-expression "->" identifier
| postfix-expression "++"
| postfix-expression "--"
;

argument-expression-list
: argument-expression
| argument-expression-list ',' argument-expression
;

argument-expression
: assignment-expression
;

unary-expression
: postfix-expression
| "++" unary-expression
| "--" unary-expression
| unary-operator cast-expression
| "sizeof" unary-expression
| "sizeof" '(' type-name ')'
;

unary-operator
: '&'
| '*'
| '+'
| '-'
| '~'
| '!'
;

cast-expression
: unary-expression
| '(' type-name ')' cast-expression
;

multiplicative-expression
: cast-expression
| multiplicative-expression '*' cast-expression
| multiplicative-expression '/' cast-expression
| multiplicative-expression '%' cast-expression
;

additive-expression
: multiplicative-expression
| additive-expression '+' multiplicative-expression
| additive-expression '-' multiplicative-expression
;

shift-expression
: additive-expression
| shift-expression "<<" additive-expression
| shift-expression ">>" additive-expression
;

relational-expression
: shift-expression
| relational-expression '<' shift-expression
| relational-expression '>' shift-expression
| relational-expression "<=" shift-expression
| relational-expression ">=" shift-expression
;

equality-expression
: relational-expression
| equality-expression "==" relational-expression
| equality-expression "!=" relational-expression
;

and-expression
: equality-expression
| and-expression '&' equality-expression
;

exclusive-or-expression
: and-expression
| exclusive-or-expression '^' and-expression
;

inclusive-or-expression
: exclusive-or-expression
| inclusive-or-expression '|' exclusive-or-expression
;

logical-and-expression
: inclusive-or-expression
| logical-and-expression "&&" inclusive-or-expression
;

logical-or-expression
: logical-and-expression
| logical-or-expression "||" logical-and-expression
;

conditional-expression
: logical-or-expression
| logical-or-expression '?' expression ':' conditional-expression
;

assignment-expression
: conditional-expression
| unary-expression assignment-operator assignment-expression
;

assignment-operator
: '='
| "*="
| "/="
| "%="
| "+="
| "-="
| "<<="
| ">>="
| "&="
| "^="
| "|="
;

expression.opt
: %empty
| expression
;

expression
: assignment-expression
| expression ',' assignment-expression
;

constant-expression.opt
: %empty
| constant-expression
;

constant-expression
: conditional-expression
;

type-declaration
: declaration-specifiers ';'
;

declaration
: declaration-specifiers init-declarator-list ';'
| storage-class-specifier declaration-specifiers init-declarator-list ';'
;

global-declaration
: declaration-specifiers init-declarator-list ';'
| linkage-specifier declaration-specifiers init-declarator-list ';'
;

typedef-declaration
: typedef-specifier declaration-specifiers declarator-list ';'
;

declaration-specifiers
: type-qualifier-list.opt type-specifier type-qualifier-list.opt
;

init-declarator-list
: init-declarator
| init-declarator-list ',' init-declarator
;

init-declarator
: declarator
| declarator '=' initializer
;

storage-class-specifier
: "static"
| "auto"
| "register"
;

linkage-specifier
: "extern"
| "static"
;

typedef-specifier
: "typedef"
;

int.opt
: %empty
| "int"
;

short-type
: "short" int.opt
| "signed" "short" int.opt
;

int-type
: "int"
| "signed" int.opt
;

long-type
: "long" int.opt
| "signed" "long" int.opt
;

long-long-type
: "long" "long" int.opt
| "signed" "long" "long" int.opt
;

fundamental-type-specifier
: "void"
| "char"
| "signed" "char"
| "unsigned" "char"
| short-type
| "unsigned" "short" int.opt
| int-type
| "unsigned" int.opt
| long-type
| "unsigned" "long" int.opt
| long-long-type
| "unsigned" "long" "long" int.opt
| "float"
| "double"
| "long" "double"
;

type-specifier
: fundamental-type-specifier
| struct-or-union-specifier
| enum-specifier
| typedef-name
;

struct-or-union-specifier
: struct-or-union identifier.opt '{' struct-declaration-list '}'
| struct-or-union identifier
;

struct-or-union
: "struct"
| "union"
;

struct-declaration-list.opt
: %empty
| struct-declaration-list
;

struct-declaration-list
: struct-declaration struct-declaration-list.opt
;

struct-declaration
: declaration-specifiers struct-declarator-list ';'
;

struct-declarator-list
: struct-declarator
| struct-declarator-list ',' struct-declarator
;

struct-declarator
: declarator
| ':' constant-expression
| declarator ':' constant-expression
;

enum-specifier
: "enum" identifier.opt '{' enumerator-list '}'
| "enum" identifier
;

enumerator-list
: enumerator
| enumerator-list ',' enumerator
;

enumerator
: identifier
| identifier '=' constant-expression
;

type-qualifier
: "const"
| "volatile"
;

declarator-list
: declarator
| declarator-list ',' declarator
;

declarator
: pointer-list.opt direct-declarator
| pointer-list.opt array-declarator
| pointer-list.opt function-declarator
| pointer-list.opt variadic-function-declarator
;

direct-declarator
: identifier
| '(' declarator ')'
;

array-declarator
: direct-declarator '[' constant-expression.opt ']'
| array-declarator '[' constant-expression.opt ']'
;

function-declarator
: direct-declarator '(' parameter-declaration-list ')'
;

variadic-function-declarator
: direct-declarator '(' parameter-declaration-list ',' "..." ')'
;

pointer-list.opt
: %empty
| pointer-list
;

pointer-list
: '*' type-qualifier-list.opt pointer-list.opt
;

type-qualifier-list.opt
: %empty
| type-qualifier-list
;

type-qualifier-list
: type-qualifier type-qualifier-list.opt
;

parameter-declaration-list
: parameter-declaration
| parameter-declaration-list ',' parameter-declaration
;

parameter-declaration
: declaration-specifiers declarator
| declaration-specifiers abstract-declarator
| declaration-specifiers
;

type-name
: declaration-specifiers
| declaration-specifiers abstract-declarator
;

abstract-declarator
: pointer-list
| pointer-list.opt direct-abstract-declarator
| pointer-list.opt array-abstract-declarator
| pointer-list.opt function-abstract-declarator
| pointer-list.opt variadic-function-abstract-declarator
;

direct-abstract-declarator
: '(' abstract-declarator ')'
;

array-abstract-declarator
: '[' constant-expression.opt ']'
| direct-abstract-declarator '[' constant-expression.opt ']'
| array-abstract-declarator '[' constant-expression.opt ']'
;

function-abstract-declarator
: '(' parameter-declaration-list ')'
| direct-abstract-declarator '(' parameter-declaration-list ')'
;

variadic-function-abstract-declarator
: '(' parameter-declaration-list ',' "..." ')'
| direct-abstract-declarator '(' parameter-declaration-list ',' "..." ')'
;

initializer
: assignment-expression
| '{' initializer-list '}'
| '{' initializer-list ',' '}'
;

initializer-list
: initializer
| initializer-list ',' initializer
;

statement
: labeled-statement
| compound-statement
| expression-statement
| selection-statement
| iteration-statement
| jump-statement
;

labeled-statement
: identifier ':' statement
| "case" constant-expression ':' statement
| "default" ':' statement
;

compound-statement
: '{' declaration-list.opt statement-list.opt '}'
;

declaration-list.opt
: %empty
| declaration-list
;

declaration-list
: declaration declaration-list.opt
;

statement-list.opt
: %empty
| statement-list
;

statement-list
: statement statement-list.opt
;

expression-statement
: expression.opt ';'
;

selection-statement
: "if" '(' expression ')' statement %prec ONLY_IF
| "if" '(' expression ')' statement "else" statement
| "switch" '(' expression ')' statement
;

iteration-statement
: "while" '(' expression ')' statement
| "do" statement "while" '(' expression ')' ';'
| "for" '(' expression.opt ';' expression.opt ';' expression.opt ')' statement
;

jump-statement
: "goto" identifier ';'
| "continue" ';'
| "break" ';'
| "return" expression.opt ';'
;

translation-unit
: external-declaration
| translation-unit external-declaration
;

external-declaration
: function-definition
| type-declaration
| global-declaration
| typedef-declaration
;

function-definition
: declaration-specifiers declarator compound-statement
| linkage-specifier declaration-specifiers declarator compound-statement
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
