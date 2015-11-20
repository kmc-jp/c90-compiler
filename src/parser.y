%{
#include <stdio.h>
#include <llvm-c/Core.h>
int yylex(void);
void yyerror(const char *);
%}

%code requires {
#include "ast.h"
}

%union {
  char* null_terminated;
  AST ast;
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
%type <ast> type-specifier
%type <ast> declarator
%type <ast> direct-declarator

%start translation-unit

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
| declaration-specifiers
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

direct-declarator
: IDENTIFIER {
  $$.tag = AST_IDENTIFIER;
  $$.ast.identifier.symbol = $[IDENTIFIER];
}
/* | '{' declarator '}' */
/* | direct-declarator '[' constant-expression.opt ']' */
| direct-declarator '(' parameter-type-list ')'
/* | direct-declarator '(' identifier-list.opt')' */
;

pointer.opt
: /* empty */
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
| declaration-specifiers abstract-declarator.opt
;

/* 6.5.5 Types names */
abstract-declarator.opt
: /* empty */
/* | abstruct-declarator */
;

/* 6.6.2 Compound statement, or block */
compound-statement
: '{' declaration-list.opt statement-list.opt '}'
;

declaration-list.opt
: /* empty */
/* | declaration-list */
;

statement-list.opt
: /* empty */
/* | statement-list */
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

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
