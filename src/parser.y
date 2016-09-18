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

expression
: assignment-expression
| expression ',' assignment-expression
;

constant-expression
: conditional-expression
;

declaration
: declaration-specifiers ';'
| declaration-specifiers init-declarator-list ';'
;

declaration-specifiers
: storage-class-specifier
| storage-class-specifier declaration-specifiers
| type-specifier
| type-specifier declaration-specifiers
| type-qualifier
| type-qualifier declaration-specifiers
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
: "typedef"
| "extern"
| "static"
| "auto"
| "register"
;

type-specifier
: "void"
| "char"
| "short"
| "int"
| "long"
| "float"
| "double"
| "signed"
| "unsigned"
| struct-or-union-specifier
| enum-specifier
| typedef-name
;

typedef-name
: identifier
;

struct-or-union-specifier
: struct-or-union identifier '{' struct-declaration-list '}'
| struct-or-union '{' struct-declaration-list '}'
| struct-or-union identifier
;

struct-or-union
: "struct"
| "union"
;

struct-declaration-list
: struct-declaration
| struct-declaration-list struct-declaration
;

struct-declaration
: specifier-qualifier-list struct-declarator-list ';'
;

specifier-qualifier-list
: specifier-qualifier
| specifier-qualifier specifier-qualifier-list
;

specifier-qualifier
: type-specifier
| type-qualifier
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
: "enum" '{' enumerator-list '}'
| "enum" identifier '{' enumerator-list '}'
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

declarator
: pointer-list direct-declarator
| direct-declarator
;

direct-declarator
: identifier
| '(' declarator ')'
| direct-declarator '[' constant-expression ']'
| direct-declarator '[' ']'
| direct-declarator '(' parameter-declaration-list ')'
| direct-declarator '(' parameter-declaration-list ',' "..." ')'
;

pointer-list.opt
: %empty
| pointer-list
;

pointer-list
: '*' pointer-list.opt
| '*' type-qualifier-list pointer-list.opt
;

type-qualifier-list
: type-qualifier
| type-qualifier-list type-qualifier
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
: specifier-qualifier-list
| specifier-qualifier-list abstract-declarator
;

abstract-declarator
: pointer-list
| direct-abstract-declarator
| pointer-list direct-abstract-declarator
;

direct-abstract-declarator
: '(' abstract-declarator ')'
| '[' ']'
| '[' constant-expression ']'
| direct-abstract-declarator '[' ']'
| direct-abstract-declarator '[' constant-expression ']'
| '(' parameter-declaration-list ')'
| '(' parameter-declaration-list ',' "..." ')'
| direct-abstract-declarator '(' parameter-declaration-list ')'
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
: '{' '}'
| '{' statement-list '}'
| '{' declaration-list '}'
| '{' declaration-list statement-list '}'
;

declaration-list
: declaration
| declaration-list declaration
;

statement-list
: statement
| statement-list statement
;

expression-statement
: ';'
| expression ';'
;

selection-statement
: "if" '(' expression ')' statement %prec ONLY_IF
| "if" '(' expression ')' statement "else" statement
| "switch" '(' expression ')' statement
;

iteration-statement
: "while" '(' expression ')' statement
| "do" statement "while" '(' expression ')' ';'
| "for" '(' expression-statement expression-statement ')' statement
| "for" '(' expression-statement expression-statement expression ')' statement
;

jump-statement
: "goto" identifier ';'
| "continue" ';'
| "break" ';'
| "return" ';'
| "return" expression ';'
;

translation-unit
: external-declaration
| translation-unit external-declaration
;

external-declaration
: function-definition
| declaration
;

function-definition
: declaration-specifiers declarator compound-statement
| declarator compound-statement
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
