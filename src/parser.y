%{
#include <stdio.h>
#include <llvm-c/Core.h>
#include "ast.h"
int yylex(void);
void yyerror(const char *);
static AST g_parser_result;
%}

%code requires {
#include "ast.h"
#include "use_vector.h"
AST parse(const char* file);
}

%union {
  char* null_terminated;
  AST ast;
}

%initial-action {
  initialize_vector();
}

%token ARROW INCREMENT DECREMENT LEFT_SHIFT RIGHT_SHIFT
%token EQUAL NOT_EQUAL LESS GREATER LESS_EQUAL GREATER_EQUAL
%token AND OR ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token LEFT_SHIFT_ASSIGN RIGHT_SHIFT_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN

%token AUTO "auto" BREAK "break" CASE "case" CHAR "char"
%token CONST "const" CONTINUE "continue" DEFAULT "default" DO "do"
%token DOUBLE "double" ELSE "else" ENUM "enum" EXTERN "extern"
%token FLOAT "float" FOR "for" GOTO "goto" IF "if"
%token INT "int" LONG "long" REGISTER "register" RETURN "return"
%token SHORT "short" SIGNED "signed" SIZEOF "sizeof" STATIC "static"
%token STRUCT "struct" SWITCH "switch" TYPEDEF "typedef" UNION "union"
%token UNSIGNED "unsigned" VOID "void" VOLATILE "volatile" WHILE "while"

%token <null_terminated> IDENTIFIER
%token INTEGER_CONSTANT
%token FLOATING_CONSTANT
%token CHARACTER_CONSTANT
%token STRING_LITERAL

%type <ast> declaration-specifiers
%type <ast> declaration-specifiers.opt
%type <ast> type-specifier
%type <ast> declarator
%type <ast> direct-declarator
%type <ast> parameter-type-list
%type <ast> parameter-list
%type <ast> parameter-declaration
%type <ast> translation-unit
%type <ast> external-declaration
%type <ast> function-definition

%start entry-point

%%

keyword
: "auto" | "break" | "case" | "char"
| "const" | "continue" | "default" | "do"
| "double" | "else" | "enum" | "extern"
| "float" | "for" | "goto" | "if"
| "int" | "long" | "register" | "return"
| "short" | "signed" | "sizeof" | "static"
| "struct" | "switch" | "typedef" | "union"
| "unsigned" | "void" | "volatile" | "while"

constant
: FLOATING_CONSTANT
| INTEGER_CONSTANT
| CHARACTER_CONSTANT
;

/* 6.3.1 Primary expression */
primary-expression
: IDENTIFIER
/* | constant */
| STRING_LITERAL
| '(' expression ')'
;

/* 6.3.2 Postfix operators */
postfix-expression
: primary-expression
/* | postfix-expression '[' expression ']' */
| postfix-expression '(' argument-expression-list.opt ')'
/* | postfix-expression '.' IDENTIFIER */
/* | postfix-expression '->' IDENTIFIER */
/* | postfix-expression "++" */
/* | postfix-expression "--" */
;

argument-expression-list
: assignment-expression
| argument-expression-list ',' assignment-expression
;

argument-expression-list.opt
: /* empty */
| argument-expression-list
;

/* 6.3.16 Assignment operators */
assignment-expression
  /* short cut */
: postfix-expression
/* : conditional-expression */
/* | unary-expression assignment-operator assignment-expression */
;

/* 6.3.17 Comma operator */
expression
: assignment-expression
/* | expression ',' assignment-expression */
;

expression.opt
: /* empty */
| expression
;

/* 6.5 Declarations */
declaration-specifiers
/* : storage-class-specifier declaration-specifiers.opt */
: type-specifier declaration-specifiers.opt {
  /* TODO */
  $$ = $[type-specifier];  /* ignore two or more specifiers */
}
/* | type-specifier declaration-specifiers.opt */
/* | type-qualifier declaration-specifiers.opt */
;

declaration-specifiers.opt
: /* empty */
| declaration-specifiers {
  $$ = $[declaration-specifiers];
}
;

/* 6.5.2 Type specifiers */
type-specifier
: "void" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_VOID;
  $$.ast.type.llvm = LLVMVoidType();
}
| "char" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_CHAR;
  $$.ast.type.llvm = LLVMInt8Type();
}
| "short" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_SHORT;
  $$.ast.type.llvm = LLVMInt16Type();
}
| "int" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_INT;
  $$.ast.type.llvm = LLVMInt32Type();
}
| "long" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_LONG;
  $$.ast.type.llvm = LLVMInt32Type();
}
| "float" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_FLOAT;
  $$.ast.type.llvm = LLVMFloatType();
}
| "double" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_DOUBLE;
  $$.ast.type.llvm = LLVMDoubleType();
}
| "signed" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_SIGNED;
  $$.ast.type.llvm = LLVMInt32Type();
}
| "unsigned" {
  $$.tag = AST_TYPE;
  $$.ast.type.tag = AST_TYPE_UNSIGNED;
  $$.ast.type.llvm = LLVMInt32Type();
}
/* | struct-or-union-specifier */
/* | enum-specifier */
/* | typedef-name */
;

/* 6.5.4 Declarators */
declarator
: pointer.opt direct-declarator {
  $$ = $[direct-declarator];
}
;

direct-declarator[lhs]
: IDENTIFIER {
  $$.tag = AST_IDENTIFIER;
  $$.ast.identifier.symbol = $[IDENTIFIER];
}
/* | '{' declarator '}' */
/* | direct-declarator '[' constant-expression.opt ']' */
| direct-declarator[rhs] '(' parameter-type-list ')' {
  $$.tag = AST_FUNCTION_DECLARATION;
  $[lhs].ast.function_declaration.identifier = $[rhs].ast.identifier;
  $$.ast.function_declaration.parameter_list = $[parameter-type-list].ast.vec;
}
/* | direct-declarator '(' identifier-list.opt')' */
;

pointer.opt
: /* empty */
/* | pointer */
;

parameter-type-list
: parameter-list {
  $$ = $[parameter-list];
}
/* | parameter-list ',' "..." */
;

parameter-list[lhs]
: parameter-declaration {
  $$.tag = AST_PARAMETER_LIST;
  $$.ast.vec = ASTFUNC(ctor)();
  ASTFUNC(push_back)($$.ast.vec, &$[parameter-declaration]);
}
| parameter-list[rhs] ',' parameter-declaration {
  $[lhs] = $[rhs];
  ASTFUNC(push_back)($$.ast.vec, &$[parameter-declaration]);
}
;

parameter-declaration
: declaration-specifiers declarator {
  $$.tag = AST_DECLARATION;
  $$.ast.declaration.specifier = $[declaration-specifiers].ast.type;
  $$.ast.declaration.identifier = $[declarator].ast.identifier;
}
| declaration-specifiers abstract-declarator.opt {
  $$.tag = AST_DECLARATION;
  $$.ast.declaration.specifier = $[declaration-specifiers].ast.type;
  $$.ast.declaration.identifier.symbol = "";
}
;

/* 6.5.5 Types names */
abstract-declarator.opt
: /* empty */
/* | abstruct-declarator */
;

/* 6.6 Statements */
statement
: compound-statement
/* : labeled-statement */
/* | compound-statement */
| expression-statement
/* | selection-statement */
/* | iteration-statement */
| jump-statement
;

/* 6.6.2 Compound statement, or block */
compound-statement
: '{' declaration-list.opt statement-list.opt '}'
;

declaration-list.opt
: /* empty */
/* | declaration-list */
;

statement-list
: statement
| statement-list statement
;

statement-list.opt
: /* empty */
| statement-list
;

/* 6.6.3 Expression and null statements  */
expression-statement
: expression.opt ';'
;

/* 6.6.6 Jump statements */
jump-statement
/* : "goto" IDENTIFIER ';' */
/* | "continue" ';' */
/* | "break" ';' */
/* | "return" expression.opt ';' */
: "return" expression.opt ';'
;

/* 6.7 External definitions */
translation-unit[lhs]
: external-declaration {
  $$.tag = AST_TRANSLATION_UNIT;
  $$.ast.vec = ASTFUNC(ctor)();
  ASTFUNC(push_back)($$.ast.vec, &$[external-declaration]);
}
| translation-unit[rhs] external-declaration {
  $[lhs] = $[rhs];
  ASTFUNC(push_back)($$.ast.vec, &$[external-declaration]);
}

external-declaration
: function-definition {
  $$ = $[function-definition];
}
/* | declaration */
;

/* 6.7.1 Function definitions */
function-definition
: declaration-specifiers.opt declarator declaration-list.opt compound-statement {
  if ($[declarator].tag != AST_FUNCTION_DECLARATION) {
    yyerror("invalid function definition");
    YYERROR;
  }
  $$.tag = AST_FUNCTION_DEFINITION;
  $$.ast.function_definition.type = $[declaration-specifiers.opt].ast.type;
  $$.ast.function_definition.identifier = $[declarator].ast.function_declaration.identifier;
  $$.ast.function_definition.parameter_list = $[declarator].ast.function_declaration.parameter_list;
}

entry-point
: translation-unit {
  g_parser_result = $[translation-unit];
}

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
AST parse(const char* file) {
  scan_from_file(file);
  const int result = yyparse();
  if (result == 0) {
    return g_parser_result;
  } else if (result == 1) {
    fprintf(stderr, "%s\n", "error: parsing failed because of invalid input");
  } else if (result == 2) {
    fprintf(stderr, "%s\n", "error: parsing failed due to memory exhaustion");
  }
  exit(EXIT_FAILURE);
}
