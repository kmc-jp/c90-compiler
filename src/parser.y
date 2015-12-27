%code {
#include <stdio.h>
#include "ast_method.h"
#include "utility.h"

#define AST_ERROR(lhs, rhs) \
  do { \
    yyerror("cannot parse `" lhs "` as `" rhs "`"); \
    YYERROR; \
  } while (false)

void yyerror(const char *);
}

%code provides {
int yylex(void);
void set_yyin_file(const char *filename);
void set_yyin_string(const char *code);
}

%code requires {
#include "ast.h"
#define YYSTYPE AstRef
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
%token LESS "<"
%token GREATER ">"
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

%start translation-unit

%%

identifier.opt
: /* empty */
| identifier
;

identifier
: IDENTIFIER
;

constant
: floating-constant
| integer-constant
| enumeration-constant
| character-constant
;

floating-constant
: FLOATING_CONSTANT {
  $$ = ast_make_floating_constant($[FLOATING_CONSTANT]);
  if (!$$) {
    AST_ERROR("floating-constant", "FLOATING_CONSTANT");
  }
}
;

integer-constant
: INTEGER_CONSTANT {
  $$ = ast_make_integer_constant($[INTEGER_CONSTANT]);
  if (!$$) {
    AST_ERROR("integer-constant", "INTEGER_CONSTANT");
  }
}
;

enumeration-constant
: identifier {
  $$ = ast_make_enumeration_constant($[identifier]);
  if (!$$) {
    AST_ERROR("enumeration-constant", "identifier");
  }
}
;

character-constant
: CHARACTER_CONSTANT {
  $$ = ast_make_character_constant($[CHARACTER_CONSTANT]);
  if (!$$) {
    AST_ERROR("character-constant", "CHARACTER_CONSTANT");
  }
}
;

string-literal
: STRING_LITERAL {
  $$ = ast_make_string_literal($[STRING_LITERAL]);
  if (!$$) {
    AST_ERROR("string-literal", "STRING_LITERAL");
  }
}
;

primary-expression
: identifier {
  $$ = ast_make_primary_expression($[identifier]);
  if (!$$) {
    AST_ERROR("primary-expression", "identifier");
  }
}
| constant {
  $$ = ast_make_primary_expression($[constant]);
  if (!$$) {
    AST_ERROR("primary-expression", "constant");
  }
}
| string-literal {
  $$ = ast_make_primary_expression($[string-literal]);
  if (!$$) {
    AST_ERROR("primary-expression", "string-literal");
  }
}
| '(' expression ')' {
  $$ = ast_make_expression($[expression]);
  if (!$$) {
    AST_ERROR("primary-expression", "'(' expression ')'");
  }
}
;

postfix-expression
: primary-expression {
  $$ = ast_make_postfix_expression($[primary-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "primary-expression");
  }
}
| array-subscript-expression {
  $$ = ast_make_postfix_expression($[array-subscript-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "array-subscript-expression");
  }
}
| function-call-expression {
  $$ = ast_make_postfix_expression($[function-call-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "function-call-expression");
  }
}
| member-access-expression {
  $$ = ast_make_postfix_expression($[member-access-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "member-access-expression");
  }
}
| member-access-through-pointer-expression {
  $$ = ast_make_postfix_expression($[member-access-through-pointer-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "member-access-through-pointer-expression");
  }
}
| postfix-increment-expression {
  $$ = ast_make_postfix_expression($[postfix-increment-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "postfix-increment-expression");
  }
}
| postfix-decrement-expression {
  $$ = ast_make_postfix_expression($[postfix-decrement-expression]);
  if (!$$) {
    AST_ERROR("postfix-expression", "postfix-decrement-expression");
  }
}
;

array-subscript-expression
: postfix-expression '[' expression ']' {
  $$ = ast_make_array_subscript_expression($[postfix-expression], $[expression]);
  if (!$$) {
    AST_ERROR("array-subscript-expression", "postfix-expression '[' expression ']'");
  }
}
;

function-call-expression
: postfix-expression '(' argument-expression-list.opt ')' {
  $$ = ast_make_function_call_expression($[postfix-expression], $[argument-expression-list.opt]);
  if (!$$) {
    AST_ERROR("function-call-expression", "postfix-expression '(' argument-expression-list.opt ')'");
  }
}
;

member-access-expression
: postfix-expression '.' identifier {
  $$ = ast_make_member_access_expression($[postfix-expression], $[identifier]);
  if (!$$) {
    AST_ERROR("member-access-expression", "postfix-expression '.' identifier");
  }
}
;

member-access-through-pointer-expression
: postfix-expression "->" identifier {
  $$ = ast_make_member_access_through_pointer_expression($[postfix-expression], $[identifier]);
  if (!$$) {
    AST_ERROR("member-access-through-pointer-expression", "postfix-expression \"->\" identifier");
  }
}
;

postfix-increment-expression
: postfix-expression "++" {
  $$ = ast_make_postfix_increment_expression($[postfix-expression]);
  if (!$$) {
    AST_ERROR("postfix-increment-expression", "postfix-expression \"++\"");
  }
}
;

postfix-decrement-expression
: postfix-expression "--" {
  $$ = ast_make_postfix_decrement_expression($[postfix-expression]);
  if (!$$) {
    AST_ERROR("postfix-decrement-expression", "postfix-expression \"--\"");
  }
}
;

argument-expression-list.opt
: /* empty */ {
  $$ = ast_make_argument_expression_list();
}
| argument-expression-list {
  $$ = $[argument-expression-list];
}
;

argument-expression-list
: assignment-expression {
  $$ = ast_make_argument_expression_list();
  $$ = ast_push_argument_expression_list($$, $[assignment-expression]);
  if (!$$) {
    AST_ERROR("argument-expression-list", "assignment-expression");
  }
}
| argument-expression-list[src] ',' assignment-expression {
  $$ = ast_push_argument_expression_list($[src], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("argument-expression-list", "argument-expression-list ',' assignment-expression");
  }
}
;

unary-expression
: postfix-expression {
  $$ = ast_make_unary_expression($[postfix-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "postfix-expression");
  }
}
| prefix-increment-expression {
  $$ = ast_make_unary_expression($[prefix-increment-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "prefix-increment-expression");
  }
}
| prefix-decrement-expression {
  $$ = ast_make_unary_expression($[prefix-decrement-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "prefix-decrement-expression");
  }
}
| address-of-expression {
  $$ = ast_make_unary_expression($[address-of-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "address-of-expression");
  }
}
| pointer-dereference-expression {
  $$ = ast_make_unary_expression($[pointer-dereference-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "pointer-dereference-expression");
  }
}
| unary-plus-expression {
  $$ = ast_make_unary_expression($[unary-plus-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "unary-plus-expression");
  }
}
| unary-minus-expression {
  $$ = ast_make_unary_expression($[unary-minus-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "unary-minus-expression");
  }
}
| bitwise-NOT-expression {
  $$ = ast_make_unary_expression($[bitwise-NOT-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "bitwise-NOT-expression");
  }
}
| logical-NOT-expression {
  $$ = ast_make_unary_expression($[logical-NOT-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "logical-NOT-expression");
  }
}
| sizeof-expression {
  $$ = ast_make_unary_expression($[sizeof-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "sizeof-expression");
  }
}
| sizeof-type-expression {
  $$ = ast_make_unary_expression($[sizeof-type-expression]);
  if (!$$) {
    AST_ERROR("unary-expression", "sizeof-type-expression");
  }
}
;

prefix-increment-expression
: "++" unary-expression {
  $$ = ast_make_prefix_increment_expression($[unary-expression]);
  if (!$$) {
    AST_ERROR("prefix-increment-expression", "\"++\" unary-expression");
  }
}
;

prefix-decrement-expression
: "--" unary-expression {
  $$ = ast_make_prefix_decrement_expression($[unary-expression]);
  if (!$$) {
    AST_ERROR("prefix-decrement-expression", "\"--\" unary-expression");
  }
}
;

address-of-expression
: '&' cast-expression {
  $$ = ast_make_address_of_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("address-of-expression", "'&' cast-expression");
  }
}
;

pointer-dereference-expression
: '*' cast-expression {
  $$ = ast_make_pointer_dereference_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("pointer-dereference-expression", "'*' cast-expression");
  }
}
;

unary-plus-expression
: '+' cast-expression {
  $$ = ast_make_unary_plus_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("unary-plus-expression", "'+' cast-expression");
  }
}
;

unary-minus-expression
: '-' cast-expression {
  $$ = ast_make_unary_minus_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("unary-minus-expression", "'-' cast-expression");
  }
}
;

bitwise-NOT-expression
: '~' cast-expression {
  $$ = ast_make_bitwise_not_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("bitwise-NOT-expression", "'~' cast-expression");
  }
}
;

logical-NOT-expression
: '!' cast-expression {
  $$ = ast_make_logical_not_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("logical-NOT-expression", "'!' cast-expression");
  }
}
;

sizeof-expression
: "sizeof" unary-expression {
  $$ = ast_make_sizeof_expression($[unary-expression]);
  if (!$$) {
    AST_ERROR("sizeof-expression", "\"sizeof\" unary-expression");
  }
}
;

sizeof-type-expression
: "sizeof" '(' type-name ')' {
  $$ = ast_make_sizeof_type_expression($[type-name]);
  if (!$$) {
    AST_ERROR("sizeof-type-expression", "\"sizeof\" '(' type-name ')'");
  }
}
;

cast-expression
: unary-expression {
  $$ = ast_make_cast_expression($[unary-expression]);
  if (!$$) {
    AST_ERROR("cast-expression", "unary-expression");
  }
}
| type-cast-expression {
  $$ = ast_make_cast_expression($[type-cast-expression]);
  if (!$$) {
    AST_ERROR("cast-expression", "type-cast-expression");
  }
}
;

type-cast-expression
: '(' type-name ')' cast-expression {
  $$ = ast_make_type_cast_expression($[type-name], $[cast-expression]);
  if (!$$) {
    AST_ERROR("type-cast-expression", "'(' type-name ')' cast-expression");
  }
}
;

multiplicative-expression
: cast-expression {
  $$ = ast_make_multiplicative_expression($[cast-expression]);
  if (!$$) {
    AST_ERROR("multiplicative-expression", "cast-expression");
  }
}
| product-expression {
  $$ = ast_make_multiplicative_expression($[product-expression]);
  if (!$$) {
    AST_ERROR("multiplicative-expression", "product-expression");
  }
}
| division-expression {
  $$ = ast_make_multiplicative_expression($[division-expression]);
  if (!$$) {
    AST_ERROR("multiplicative-expression", "division-expression");
  }
}
| modulo-expression {
  $$ = ast_make_multiplicative_expression($[modulo-expression]);
  if (!$$) {
    AST_ERROR("multiplicative-expression", "modulo-expression");
  }
}
;

product-expression
: multiplicative-expression '*' cast-expression {
  $$ = ast_make_product_expression($[multiplicative-expression], $[cast-expression]);
  if (!$$) {
    AST_ERROR("product-expression", "multiplicative-expression '*' cast-expression");
  }
}
;

division-expression
: multiplicative-expression '/' cast-expression {
  $$ = ast_make_division_expression($[multiplicative-expression], $[cast-expression]);
  if (!$$) {
    AST_ERROR("division-expression", "multiplicative-expression '/' cast-expression");
  }
}
;

modulo-expression
: multiplicative-expression '%' cast-expression {
  $$ = ast_make_modulo_expression($[multiplicative-expression], $[cast-expression]);
  if (!$$) {
    AST_ERROR("modulo-expression", "multiplicative-expression '%' cast-expression");
  }
}
;

additive-expression
: multiplicative-expression {
  $$ = ast_make_additive_expression($[multiplicative-expression]);
  if (!$$) {
    AST_ERROR("additive-expression", "multiplicative-expression");
  }
}
| addition-expression {
  $$ = ast_make_additive_expression($[addition-expression]);
  if (!$$) {
    AST_ERROR("additive-expression", "addition-expression");
  }
}
| subtraction-expression {
  $$ = ast_make_additive_expression($[subtraction-expression]);
  if (!$$) {
    AST_ERROR("additive-expression", "subtraction-expression");
  }
}
;

addition-expression
: additive-expression '+' multiplicative-expression {
  $$ = ast_make_addition_expression($[additive-expression], $[multiplicative-expression]);
  if (!$$) {
    AST_ERROR("addition-expression", "additive-expression '+' multiplicative-expression");
  }
}
;

subtraction-expression
: additive-expression '-' multiplicative-expression {
  $$ = ast_make_subtraction_expression($[additive-expression], $[multiplicative-expression]);
  if (!$$) {
    AST_ERROR("subtraction-expression", "additive-expression '-' multiplicative-expression");
  }
}
;

shift-expression
: additive-expression
| left-shift-expression
| right-shift-expression
;

left-shift-expression
: shift-expression "<<" additive-expression
;

right-shift-expression
: shift-expression ">>" additive-expression
;

relational-expression
: shift-expression
| less-than-expression
| greater-than-expression
| less-than-or-equal-to-expression
| greater-than-or-equal-to-expression
;

less-than-expression
: relational-expression '<' shift-expression
;

greater-than-expression
: relational-expression '>' shift-expression
;

less-than-or-equal-to-expression
: relational-expression "<=" shift-expression
;

greater-than-or-equal-to-expression
: relational-expression ">=" shift-expression
;

equality-expression
: relational-expression
| equal-to-expression
| not-equal-to-expression
;

equal-to-expression
: equality-expression "==" relational-expression
;

not-equal-to-expression
: equality-expression "!=" relational-expression
;

bitwise-AND-expression
: equality-expression
| bitwise-AND-operator-expression
;

bitwise-AND-operator-expression
: bitwise-AND-expression '&' equality-expression
;

bitwise-XOR-expression
: bitwise-AND-expression
| bitwise-XOR-operator-expression
;

bitwise-XOR-operator-expression
: bitwise-XOR-expression '^' bitwise-AND-expression
;

bitwise-OR-expression
: bitwise-XOR-expression
| bitwise-OR-operator-expression
;

bitwise-OR-operator-expression
: bitwise-OR-expression '|' bitwise-XOR-expression
;

logical-AND-expression
: bitwise-OR-expression
| logical-AND-operator-expression
;

logical-AND-operator-expression
: logical-AND-expression "&&" bitwise-OR-expression
;

logical-OR-expression
: logical-AND-expression
| logical-OR-operator-expression
;

logical-OR-operator-expression
: logical-OR-expression "||" logical-AND-expression
;

conditional-expression
: logical-OR-expression
| conditional-operator-expression
;

conditional-operator-expression
: logical-OR-expression '?' expression ':' conditional-expression
;

assignment-expression
: conditional-expression
| basic-assignment-expression
| multiplication-assignment-expression
| division-assignment-expression
| modulo-assignment-expression
| addition-assignment-expression
| subtraction-assignment-expression
| left-shift-assignment-expression
| right-shift-assignment-expression
| bitwise-AND-assignment-expression
| bitwise-XOR-assignment-expression
| bitwise-OR-assignment-expression
;

basic-assignment-expression
: unary-expression '=' assignment-expression
;

multiplication-assignment-expression
: unary-expression "*=" assignment-expression
;

division-assignment-expression
: unary-expression "/=" assignment-expression
;

modulo-assignment-expression
: unary-expression "%=" assignment-expression
;

addition-assignment-expression
: unary-expression "+=" assignment-expression
;

subtraction-assignment-expression
: unary-expression "-=" assignment-expression
;

left-shift-assignment-expression
: unary-expression "<<=" assignment-expression
;

right-shift-assignment-expression
: unary-expression ">>=" assignment-expression
;

bitwise-AND-assignment-expression
: unary-expression "&=" assignment-expression
;

bitwise-XOR-assignment-expression
: unary-expression "^=" assignment-expression
;

bitwise-OR-assignment-expression
: unary-expression "|=" assignment-expression
;

expression.opt
: /* empty */
| expression
;

expression
: assignment-expression
| comma-expression
;

comma-expression
: expression ',' assignment-expression
;

constant-expression.opt
: /* empty */
| constant-expression
;

constant-expression
: conditional-expression
;

declaration
: declaration-specifier-list init-declarator-list.opt ';'
;

declaration-specifier-list.opt
: /* empty */
| declaration-specifier-list
;

declaration-specifier-list
: declaration-specifier declaration-specifier-list.opt
;

declaration-specifier
: storage-class-specifier
| type-specifier
| type-qualifier
;

init-declarator-list.opt
: /* empty */
| init-declarator-list
;

init-declarator-list
: init-declarator
| init-declarator-list ',' init-declarator
;

init-declarator
: declarator
| declarator-with-initializer
;

declarator-with-initializer
: declarator '=' initializer
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

struct-or-union-specifier
: struct-or-union-definition
| struct-or-union-declaration
;

struct-or-union-definition
: struct-or-union identifier.opt '{' struct-declaration-list '}'
;

struct-or-union-declaration
: struct-or-union identifier
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

specifier-qualifier-list.opt
: /* empty */
| specifier-qualifier-list
;

specifier-qualifier-list
: specifier-qualifier specifier-qualifier-list.opt
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
| bit-field-declarator
;

bit-field-declarator
: declarator.opt ':' constant-expression
;

enum-specifier
: enum-definition
| enum-declaration
;

enum-definition
: "enum" identifier.opt '{' enumerator-list '}'
;

enum-declaration
: "enum" identifier
;

enumerator-list
: enumerator
| enumerator-list ',' enumerator
;

enumerator
: enumeration-constant
| enumerator-with-initializer
;

enumerator-with-initializer
: enumeration-constant '=' constant-expression
;

type-qualifier
: "const"
| "volatile"
;

declarator.opt
: /* empty */
| declarator
;

declarator
: pointer.opt direct-declarator
;

direct-declarator
: identifier
| '(' declarator ')'
| array-declarator
| function-declarator
| old-style-function-declarator
;

array-declarator
: direct-declarator '[' constant-expression.opt ']'
;

function-declarator
: direct-declarator '(' parameter-type-list ')'
;

old-style-function-declarator
: direct-declarator '(' identifier-list.opt ')'
;

pointer.opt
: /* empty */
| pointer
;

pointer
: '*' type-qualifier-list.opt
| '*' type-qualifier-list.opt pointer
;

type-qualifier-list.opt
: /* empty */
| type-qualifier-list
;

type-qualifier-list
: type-qualifier
| type-qualifier-list type-qualifier
;

parameter-type-list.opt
: /* empty */
| parameter-type-list
;

parameter-type-list
: parameter-list
| variadic-parameter-list
;

variadic-parameter-list
: parameter-list ',' "..."
;

parameter-list
: parameter-declaration
| parameter-list ',' parameter-declaration
;

parameter-declaration
: parameter-concrete-declaration
| parameter-abstract-declaration
;

parameter-concrete-declaration
: declaration-specifier-list declarator
;

parameter-abstract-declaration
: declaration-specifier-list abstract-declarator.opt
;

identifier-list.opt
: /* empty */
| identifier-list
;

identifier-list
: identifier
| identifier-list ',' identifier
;

type-name
: specifier-qualifier-list abstract-declarator.opt
;

abstract-declarator.opt
: /* empty */
| abstract-declarator
;

abstract-declarator
: pointer
| pointer-abstract-declarator
;

pointer-abstract-declarator
: pointer.opt direct-abstract-declarator
;

direct-abstract-declarator.opt
: /* empty */
| direct-abstract-declarator
;

direct-abstract-declarator
: '(' abstract-declarator ')'
| array-abstract-declarator
| function-abstract-declarator
;

array-abstract-declarator
: direct-abstract-declarator.opt '[' constant-expression.opt ']'
;

function-abstract-declarator
: direct-abstract-declarator.opt '(' parameter-type-list.opt ')'
;

typedef-name
: identifier
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
: identifier-labeled-statement
| case-labeled-statement
| default-labeled-statement
;

identifier-labeled-statement
: identifier ':' statement
;

case-labeled-statement
: "case" constant-expression ':' statement
;

default-labeled-statement
: "default" ':' statement
;

compound-statement
: '{' declaration-list.opt statement-list.opt '}'
;

declaration-list.opt
: /* empty */
| declaration-list
;

declaration-list
: declaration
| declaration-list declaration
;

statement-list.opt
: /* empty */
| statement-list
;

statement-list
: statement
| statement-list statement
;

expression-statement
: expression.opt ';'
;

selection-statement
: if-statement
| if-else-statement
| switch-statement
;

if-statement
: "if" '(' expression ')' statement
;

if-else-statement
: "if" '(' expression ')' statement "else" statement
;

switch-statement
: "switch" '(' expression ')' statement
;

iteration-statement
: while-statement
| do-while-statement
| for-statement
;

while-statement
: "while" '(' expression ')' statement
;

do-while-statement
: "do" statement "while" '(' expression ')' ';'
;

for-statement
: "for" '(' expression.opt ';' expression.opt ';' expression.opt ')' statement
;

jump-statement
: goto-jump-statement
| continue-jump-statement
| break-jump-statement
| return-jump-statement
| void-return-jump-statement
;

goto-jump-statement
: "goto" identifier ';'

continue-jump-statement
: "continue" ';'
;

break-jump-statement
: "break" ';'
;

return-jump-statement
: "return" expression ';'
;

void-return-jump-statement
: "return" ';'
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
: declaration-specifier-list.opt declarator declaration-list.opt compound-statement
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
