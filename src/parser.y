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
: %empty {
  $$ = NULL;
}
| identifier {
  $$ = $[identifier];
}
;

identifier
: IDENTIFIER {
  $$ = ast_make_identifier($[IDENTIFIER]);
  if (!$$) {
    AST_ERROR("identifier", "IDENTIFIER");
  }
}
;

constant
: floating-constant {
  $$ = ast_make_constant($[floating-constant]);
  if (!$$) {
    AST_ERROR("constant", "floating-constant");
  }
}
| integer-constant {
  $$ = ast_make_constant($[integer-constant]);
  if (!$$) {
    AST_ERROR("constant", "integer-constant");
  }
}
| enumeration-constant {
  $$ = ast_make_constant($[enumeration-constant]);
  if (!$$) {
    AST_ERROR("constant", "enumeration-constant");
  }
}
| character-constant {
  $$ = ast_make_constant($[character-constant]);
  if (!$$) {
    AST_ERROR("constant", "character-constant");
  }
}
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
: %empty {
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
: additive-expression {
  $$ = ast_make_shift_expression($[additive-expression]);
  if (!$$) {
    AST_ERROR("shift-expression", "additive-expression");
  }
}
| left-shift-expression {
  $$ = ast_make_shift_expression($[left-shift-expression]);
  if (!$$) {
    AST_ERROR("shift-expression", "left-shift-expression");
  }
}
| right-shift-expression {
  $$ = ast_make_shift_expression($[right-shift-expression]);
  if (!$$) {
    AST_ERROR("shift-expression", "right-shift-expression");
  }
}
;

left-shift-expression
: shift-expression "<<" additive-expression {
  $$ = ast_make_left_shift_expression($[shift-expression], $[additive-expression]);
  if (!$$) {
    AST_ERROR("left-shift-expression", "shift-expression \"<<\" additive-expression");
  }
}
;

right-shift-expression
: shift-expression ">>" additive-expression {
  $$ = ast_make_right_shift_expression($[shift-expression], $[additive-expression]);
  if (!$$) {
    AST_ERROR("right-shift-expression", "shift-expression \">>\" additive-expression");
  }
}
;

relational-expression
: shift-expression {
  $$ = ast_make_relational_expression($[shift-expression]);
  if (!$$) {
    AST_ERROR("relational-expression", "shift-expression");
  }
}
| less-than-expression {
  $$ = ast_make_relational_expression($[less-than-expression]);
  if (!$$) {
    AST_ERROR("relational-expression", "less-than-expression");
  }
}
| greater-than-expression {
  $$ = ast_make_relational_expression($[greater-than-expression]);
  if (!$$) {
    AST_ERROR("relational-expression", "greater-than-expression");
  }
}
| less-than-or-equal-to-expression {
  $$ = ast_make_relational_expression($[less-than-or-equal-to-expression]);
  if (!$$) {
    AST_ERROR("relational-expression", "less-than-or-equal-to-expression");
  }
}
| greater-than-or-equal-to-expression {
  $$ = ast_make_relational_expression($[greater-than-or-equal-to-expression]);
  if (!$$) {
    AST_ERROR("relational-expression", "greater-than-or-equal-to-expression");
  }
}
;

less-than-expression
: relational-expression '<' shift-expression {
  $$ = ast_make_less_than_expression($[relational-expression], $[shift-expression]);
  if (!$$) {
    AST_ERROR("less-than-expression", "relational-expression '<' shift-expression");
  }
}
;

greater-than-expression
: relational-expression '>' shift-expression {
  $$ = ast_make_greater_than_expression($[relational-expression], $[shift-expression]);
  if (!$$) {
    AST_ERROR("greater-than-expression", "relational-expression '>' shift-expression");
  }
}
;

less-than-or-equal-to-expression
: relational-expression "<=" shift-expression {
  $$ = ast_make_less_than_or_equal_to_expression($[relational-expression], $[shift-expression]);
  if (!$$) {
    AST_ERROR("less-than-or-equal-to-expression", "relational-expression \"<=\" shift-expression");
  }
}
;

greater-than-or-equal-to-expression
: relational-expression ">=" shift-expression {
  $$ = ast_make_greater_than_or_equal_to_expression($[relational-expression], $[shift-expression]);
  if (!$$) {
    AST_ERROR("greater-than-or-equal-to-expression", "relational-expression \">=\" shift-expression");
  }
}
;

equality-expression
: relational-expression {
  $$ = ast_make_equality_expression($[relational-expression]);
  if (!$$) {
    AST_ERROR("equality-expression", "relational-expression");
  }
}
| equal-to-expression {
  $$ = ast_make_equality_expression($[equal-to-expression]);
  if (!$$) {
    AST_ERROR("equality-expression", "equal-to-expression");
  }
}
| not-equal-to-expression {
  $$ = ast_make_equality_expression($[not-equal-to-expression]);
  if (!$$) {
    AST_ERROR("equality-expression", "not-equal-to-expression");
  }
}
;

equal-to-expression
: equality-expression "==" relational-expression {
  $$ = ast_make_equal_to_expression($[equality-expression], $[relational-expression]);
  if (!$$) {
    AST_ERROR("equal-to-expression", "equality-expression \"==\" relational-expression");
  }
}
;

not-equal-to-expression
: equality-expression "!=" relational-expression {
  $$ = ast_make_not_equal_to_expression($[equality-expression], $[relational-expression]);
  if (!$$) {
    AST_ERROR("not-equal-to-expression", "equality-expression \"!=\" relational-expression");
  }
}
;

bitwise-AND-expression
: equality-expression {
  $$ = ast_make_bitwise_and_expression($[equality-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-expression", "equality-expression");
  }
}
| bitwise-AND-operator-expression {
  $$ = ast_make_bitwise_and_expression($[bitwise-AND-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-expression", "bitwise-AND-operator-expression");
  }
}
;

bitwise-AND-operator-expression
: bitwise-AND-expression '&' equality-expression {
  $$ = ast_make_bitwise_and_operator_expression($[bitwise-AND-expression], $[equality-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-operator-expression", "bitwise-AND-expression '&' equality-expression");
  }
}
;

bitwise-XOR-expression
: bitwise-AND-expression {
  $$ = ast_make_bitwise_xor_expression($[bitwise-AND-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-expression", "bitwise-AND-expression");
  }
}
| bitwise-XOR-operator-expression {
  $$ = ast_make_bitwise_xor_expression($[bitwise-XOR-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-expression", "bitwise-XOR-operator-expression");
  }
}
;

bitwise-XOR-operator-expression
: bitwise-XOR-expression '^' bitwise-AND-expression {
  $$ = ast_make_bitwise_xor_operator_expression($[bitwise-XOR-expression], $[bitwise-AND-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-operator-expression", "bitwise-XOR-expression '^' bitwise-AND-expression");
  }
}
;

bitwise-OR-expression
: bitwise-XOR-expression {
  $$ = ast_make_bitwise_or_expression($[bitwise-XOR-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-expression", "bitwise-XOR-expression");
  }
}
| bitwise-OR-operator-expression {
  $$ = ast_make_bitwise_or_expression($[bitwise-OR-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-expression", "bitwise-OR-operator-expression");
  }
}
;

bitwise-OR-operator-expression
: bitwise-OR-expression '|' bitwise-XOR-expression {
  $$ = ast_make_bitwise_or_operator_expression($[bitwise-OR-expression], $[bitwise-XOR-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-operator-expression", "bitwise-OR-expression '|' bitwise-XOR-expression");
  }
}
;

logical-AND-expression
: bitwise-OR-expression {
  $$ = ast_make_logical_and_expression($[bitwise-OR-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-expression", "bitwise-OR-expression");
  }
}
| logical-AND-operator-expression {
  $$ = ast_make_logical_and_expression($[logical-AND-operator-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-expression", "logical-AND-operator-expression");
  }
}
;

logical-AND-operator-expression
: logical-AND-expression "&&" bitwise-OR-expression {
  $$ = ast_make_logical_and_operator_expression($[logical-AND-expression], $[bitwise-OR-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-operator-expression", "logical-AND-expression \"&&\" bitwise-OR-expression");
  }
}
;

logical-OR-expression
: logical-AND-expression {
  $$ = ast_make_logical_or_expression($[logical-AND-expression]);
  if (!$$) {
    AST_ERROR("logical-OR-expression", "logical-AND-expression");
  }
}
| logical-OR-operator-expression {
  $$ = ast_make_logical_or_expression($[logical-OR-operator-expression]);
  if (!$$) {
    AST_ERROR("logical-OR-expression", "logical-OR-operator-expression");
  }
}
;

logical-OR-operator-expression
: logical-OR-expression "||" logical-AND-expression {
  $$ = ast_make_logical_or_operator_expression($[logical-OR-expression], $[logical-AND-expression]);
  if (!$$) {
    AST_ERROR("logical-OR-operator-expression", "logical-OR-expression \"||\" logical-AND-expression");
  }
}
;

conditional-expression
: logical-OR-expression {
  $$ = ast_make_conditional_expression($[logical-OR-expression]);
  if (!$$) {
    AST_ERROR("conditional-expression", "logical-OR-expression");
  }
}
| conditional-operator-expression {
  $$ = ast_make_conditional_expression($[conditional-operator-expression]);
  if (!$$) {
    AST_ERROR("conditional-expression", "conditional-operator-expression");
  }
}
;

conditional-operator-expression
: logical-OR-expression '?' expression ':' conditional-expression {
  $$ = ast_make_conditional_operator_expression($[logical-OR-expression], $[expression], $[conditional-expression]);
  if (!$$) {
    AST_ERROR("conditional-operator-expression", "logical-OR-expression '?' expression ':' conditional-expression");
  }
}
;

assignment-expression
: conditional-expression {
  $$ = ast_make_assignment_expression($[conditional-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "conditional-expression");
  }
}
| basic-assignment-expression {
  $$ = ast_make_assignment_expression($[basic-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "basic-assignment-expression");
  }
}
| multiplication-assignment-expression {
  $$ = ast_make_assignment_expression($[multiplication-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "multiplication-assignment-expression");
  }
}
| division-assignment-expression {
  $$ = ast_make_assignment_expression($[division-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "division-assignment-expression");
  }
}
| modulo-assignment-expression {
  $$ = ast_make_assignment_expression($[modulo-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "modulo-assignment-expression");
  }
}
| addition-assignment-expression {
  $$ = ast_make_assignment_expression($[addition-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "addition-assignment-expression");
  }
}
| subtraction-assignment-expression {
  $$ = ast_make_assignment_expression($[subtraction-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "subtraction-assignment-expression");
  }
}
| left-shift-assignment-expression {
  $$ = ast_make_assignment_expression($[left-shift-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "left-shift-assignment-expression");
  }
}
| right-shift-assignment-expression {
  $$ = ast_make_assignment_expression($[right-shift-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "right-shift-assignment-expression");
  }
}
| bitwise-AND-assignment-expression {
  $$ = ast_make_assignment_expression($[bitwise-AND-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "bitwise-AND-assignment-expression");
  }
}
| bitwise-XOR-assignment-expression {
  $$ = ast_make_assignment_expression($[bitwise-XOR-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "bitwise-XOR-assignment-expression");
  }
}
| bitwise-OR-assignment-expression {
  $$ = ast_make_assignment_expression($[bitwise-OR-assignment-expression]);
  if (!$$) {
    AST_ERROR("assignment-expression", "bitwise-OR-assignment-expression");
  }
}
;

basic-assignment-expression
: unary-expression '=' assignment-expression {
  $$ = ast_make_basic_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("basic-assignment-expression", "unary-expression '=' assignment-expression");
  }
}
;

multiplication-assignment-expression
: unary-expression "*=" assignment-expression {
  $$ = ast_make_multiplication_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("multiplication-assignment-expression", "unary-expression \"*=\" assignment-expression");
  }
}
;

division-assignment-expression
: unary-expression "/=" assignment-expression {
  $$ = ast_make_division_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("division-assignment-expression", "unary-expression \"/=\" assignment-expression");
  }
}
;

modulo-assignment-expression
: unary-expression "%=" assignment-expression {
  $$ = ast_make_modulo_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("modulo-assignment-expression", "unary-expression \"%=\" assignment-expression");
  }
}
;

addition-assignment-expression
: unary-expression "+=" assignment-expression {
  $$ = ast_make_addition_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("addition-assignment-expression", "unary-expression \"+=\" assignment-expression");
  }
}
;

subtraction-assignment-expression
: unary-expression "-=" assignment-expression {
  $$ = ast_make_subtraction_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("subtraction-assignment-expression", "unary-expression \"-=\" assignment-expression");
  }
}
;

left-shift-assignment-expression
: unary-expression "<<=" assignment-expression {
  $$ = ast_make_left_shift_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("left-shift-assignment-expression", "unary-expression \"<<=\" assignment-expression");
  }
}
;

right-shift-assignment-expression
: unary-expression ">>=" assignment-expression {
  $$ = ast_make_right_shift_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("right-shift-assignment-expression", "unary-expression \">>=\" assignment-expression");
  }
}
;

bitwise-AND-assignment-expression
: unary-expression "&=" assignment-expression {
  $$ = ast_make_bitwise_and_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-assignment-expression", "unary-expression \"&=\" assignment-expression");
  }
}
;

bitwise-XOR-assignment-expression
: unary-expression "^=" assignment-expression {
  $$ = ast_make_bitwise_xor_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-assignment-expression", "unary-expression \"^=\" assignment-expression");
  }
}
;

bitwise-OR-assignment-expression
: unary-expression "|=" assignment-expression {
  $$ = ast_make_bitwise_or_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-assignment-expression", "unary-expression \"|=\" assignment-expression");
  }
}
;

expression.opt
: %empty {
  $$ = NULL;
}
| expression {
  $$ = $[expression];
}
;

expression
: assignment-expression {
  $$ = ast_make_expression($[assignment-expression]);
  if (!$$) {
    AST_ERROR("expression", "assignment-expression");
  }
}
| comma-expression {
  $$ = ast_make_expression($[comma-expression]);
  if (!$$) {
    AST_ERROR("expression", "comma-expression");
  }
}
;

comma-expression
: expression ',' assignment-expression {
  $$ = ast_make_comma_expression($[expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("comma-expression", "expression ',' assignment-expression");
  }
}
;

constant-expression.opt
: %empty {
  $$ = NULL;
}
| constant-expression {
  $$ = $[constant-expression];
}
;

constant-expression
: conditional-expression {
  $$ = ast_make_constant_expression($[conditional-expression]);
  if (!$$) {
    AST_ERROR("constant-expression", "conditional-expression");
  }
}
;

declaration
: declaration-specifier-list init-declarator-list.opt ';' {
  $$ = ast_make_declaration($[declaration-specifier-list], $[init-declarator-list.opt]);
  if (!$$) {
    AST_ERROR("declaration", "declaration-specifier-list init-declarator-list.opt ';'");
  }
}
;

declaration-specifier-list.opt
: %empty {
  $$ = ast_make_declaration_specifier_list();
}
| declaration-specifier-list {
  $$ = $[declaration-specifier-list];
}
;

declaration-specifier-list
: declaration-specifier declaration-specifier-list.opt {
  $$ = ast_push_declaration_specifier_list($[declaration-specifier-list.opt], $[declaration-specifier]);
  if (!$$) {
    AST_ERROR("declaration-specifier-list", "declaration-specifier declaration-specifier-list.opt");
  }
}
;

declaration-specifier
: storage-class-specifier {
  $$ = ast_make_declaration_specifier($[storage-class-specifier]);
  if (!$$) {
    AST_ERROR("declaration-specifier", "storage-class-specifier");
  }
}
| type-specifier {
  $$ = ast_make_declaration_specifier($[type-specifier]);
  if (!$$) {
    AST_ERROR("declaration-specifier", "type-specifier");
  }
}
| type-qualifier {
  $$ = ast_make_declaration_specifier($[type-qualifier]);
  if (!$$) {
    AST_ERROR("declaration-specifier", "type-qualifier");
  }
}
;

init-declarator-list.opt
: %empty {
  $$ = ast_make_init_declarator_list();
}
| init-declarator-list {
  $$ = $[init-declarator-list];
}
;

init-declarator-list
: init-declarator {
  $$ = ast_make_init_declarator_list();
  $$ = ast_push_init_declarator_list($$, $[init-declarator]);
  if (!$$) {
    AST_ERROR("init-declarator-list", "init-declarator");
  }
}
| init-declarator-list[src] ',' init-declarator {
  $$ = ast_push_init_declarator_list($[src], $[init-declarator]);
  if (!$$) {
    AST_ERROR("init-declarator-list", "init-declarator-list ',' init-declarator");
  }
}
;

init-declarator
: declarator {
  $$ = ast_make_init_declarator($[declarator]);
  if (!$$) {
    AST_ERROR("init-declarator", "declarator");
  }
}
| declarator-with-initializer {
  $$ = ast_make_init_declarator($[declarator-with-initializer]);
  if (!$$) {
    AST_ERROR("init-declarator", "declarator-with-initializer");
  }
}
;

declarator-with-initializer
: declarator '=' initializer {
  $$ = ast_make_declarator_with_initializer($[declarator], $[initializer]);
  if (!$$) {
    AST_ERROR("declarator-with-initializer", "declarator '=' initializer");
  }
}
;

storage-class-specifier
: "typedef"[typedef] {
  $$ = ast_make_storage_class_specifier($[typedef]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "typedef");
  }
}
| "extern"[extern] {
  $$ = ast_make_storage_class_specifier($[extern]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "extern");
  }
}
| "static"[static] {
  $$ = ast_make_storage_class_specifier($[static]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "static");
  }
}
| "auto"[auto] {
  $$ = ast_make_storage_class_specifier($[auto]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "auto");
  }
}
| "register"[register] {
  $$ = ast_make_storage_class_specifier($[register]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "register");
  }
}
;

type-specifier
: "void"[void] {
  $$ = ast_make_type_specifier($[void]);
  if (!$$) {
    AST_ERROR("type-specifier", "void");
  }
}
| "char"[char] {
  $$ = ast_make_type_specifier($[char]);
  if (!$$) {
    AST_ERROR("type-specifier", "char");
  }
}
| "short"[short] {
  $$ = ast_make_type_specifier($[short]);
  if (!$$) {
    AST_ERROR("type-specifier", "short");
  }
}
| "int"[int] {
  $$ = ast_make_type_specifier($[int]);
  if (!$$) {
    AST_ERROR("type-specifier", "int");
  }
}
| "long"[long] {
  $$ = ast_make_type_specifier($[long]);
  if (!$$) {
    AST_ERROR("type-specifier", "long");
  }
}
| "float"[float] {
  $$ = ast_make_type_specifier($[float]);
  if (!$$) {
    AST_ERROR("type-specifier", "float");
  }
}
| "double"[double] {
  $$ = ast_make_type_specifier($[double]);
  if (!$$) {
    AST_ERROR("type-specifier", "double");
  }
}
| "signed"[signed] {
  $$ = ast_make_type_specifier($[signed]);
  if (!$$) {
    AST_ERROR("type-specifier", "signed");
  }
}
| "unsigned"[unsigned] {
  $$ = ast_make_type_specifier($[unsigned]);
  if (!$$) {
    AST_ERROR("type-specifier", "unsigned");
  }
}
| struct-or-union-specifier {
  $$ = ast_make_type_specifier($[struct-or-union-specifier]);
  if (!$$) {
    AST_ERROR("type-specifier", "struct-or-union-specifier");
  }
}
| enum-specifier {
  $$ = ast_make_type_specifier($[enum-specifier]);
  if (!$$) {
    AST_ERROR("type-specifier", "enum-specifier");
  }
}
| typedef-name {
  $$ = ast_make_type_specifier($[typedef-name]);
  if (!$$) {
    AST_ERROR("type-specifier", "typedef-name");
  }
}
;

struct-or-union-specifier
: struct-or-union-definition {
  $$ = ast_make_struct_or_union_specifier($[struct-or-union-definition]);
  if (!$$) {
    AST_ERROR("struct-or-union-specifier", "struct-or-union-definition");
  }
}
| struct-or-union-declaration {
  $$ = ast_make_struct_or_union_specifier($[struct-or-union-declaration]);
  if (!$$) {
    AST_ERROR("struct-or-union-specifier", "struct-or-union-declaration");
  }
}
;

struct-or-union-definition
: struct-or-union identifier.opt '{' struct-declaration-list '}' {
  $$ = ast_make_struct_or_union_definition($[struct-or-union], $[identifier.opt], $[struct-declaration-list]);
  if (!$$) {
    AST_ERROR("struct-or-union-definition", "struct-or-union identifier.opt '{' struct-declaration-list '}'");
  }
}
;

struct-or-union-declaration
: struct-or-union identifier {
  $$ = ast_make_struct_or_union_declaration($[struct-or-union], $[identifier]);
  if (!$$) {
    AST_ERROR("struct-or-union-declaration", "struct-or-union identifier");
  }
}
;

struct-or-union
: "struct"[struct] {
  $$ = ast_make_struct_or_union($[struct]);
  if (!$$) {
    AST_ERROR("struct-or-union", "struct");
  }
}
| "union"[union] {
  $$ = ast_make_struct_or_union($[union]);
  if (!$$) {
    AST_ERROR("struct-or-union", "union");
  }
}
;

struct-declaration-list
: struct-declaration {
  $$ = ast_make_struct_declaration_list();
  $$ = ast_push_struct_declaration_list($$, $[struct-declaration]);
  if (!$$) {
    AST_ERROR("struct-declaration-list", "struct-declaration");
  }
}
| struct-declaration-list[src] struct-declaration {
  $$ = ast_push_struct_declaration_list($[src], $[struct-declaration]);
  if (!$$) {
    AST_ERROR("struct-declaration-list", "struct-declaration-list struct-declaration");
  }
}
;

struct-declaration
: specifier-qualifier-list struct-declarator-list ';' {
  $$ = ast_make_struct_declaration($[specifier-qualifier-list], $[struct-declarator-list]);
  if (!$$) {
    AST_ERROR("struct-declaration", "specifier-qualifier-list struct-declarator-list ';'");
  }
}
;

specifier-qualifier-list.opt
: %empty {
  $$ = ast_make_specifier_qualifier_list();
}
| specifier-qualifier-list {
  $$ = $[specifier-qualifier-list];
}
;

specifier-qualifier-list
: specifier-qualifier specifier-qualifier-list.opt {
  $$ = ast_push_specifier_qualifier_list($[specifier-qualifier-list.opt], $[specifier-qualifier]);
  if (!$$) {
    AST_ERROR("specifier-qualifier-list", "specifier-qualifier specifier-qualifier-list.opt");
  }
}
;

specifier-qualifier
: type-specifier {
  $$ = ast_make_specifier_qualifier($[type-specifier]);
  if (!$$) {
    AST_ERROR("specifier-qualifier", "type-specifier");
  }
}
| type-qualifier {
  $$ = ast_make_specifier_qualifier($[type-qualifier]);
  if (!$$) {
    AST_ERROR("specifier-qualifier", "type-qualifier");
  }
}
;

struct-declarator-list
: struct-declarator {
  $$ = ast_make_struct_declarator_list();
  $$ = ast_push_struct_declarator_list($$, $[struct-declarator]);
  if (!$$) {
    AST_ERROR("struct-declarator-list", "struct-declarator");
  }
}
| struct-declarator-list[src] ',' struct-declarator {
  $$ = ast_push_struct_declarator_list($[src], $[struct-declarator]);
  if (!$$) {
    AST_ERROR("struct-declarator-list", "struct-declarator-list ',' struct-declarator");
  }
}
;

struct-declarator
: declarator {
  $$ = ast_make_struct_declarator($[declarator]);
  if (!$$) {
    AST_ERROR("struct-declarator", "declarator");
  }
}
| bit-field-declarator {
  $$ = ast_make_struct_declarator($[bit-field-declarator]);
  if (!$$) {
    AST_ERROR("struct-declarator", "bit-field-declarator");
  }
}
;

bit-field-declarator
: declarator.opt ':' constant-expression {
  $$ = ast_make_bit_field_declarator($[declarator.opt], $[constant-expression]);
  if (!$$) {
    AST_ERROR("bit-field-declarator", "declarator.opt ':' constant-expression");
  }
}
;

enum-specifier
: enum-definition {
  $$ = ast_make_enum_specifier($[enum-definition]);
  if (!$$) {
    AST_ERROR("enum-specifier", "enum-definition");
  }
}
| enum-declaration {
  $$ = ast_make_enum_specifier($[enum-declaration]);
  if (!$$) {
    AST_ERROR("enum-specifier", "enum-declaration");
  }
}
;

enum-definition
: "enum" identifier.opt '{' enumerator-list '}' {
  $$ = ast_make_enum_definition($[identifier.opt], $[enumerator-list]);
  if (!$$) {
    AST_ERROR("enum-definition", "\"enum\" identifier.opt '{' enumerator-list '}'");
  }
}
;

enum-declaration
: "enum" identifier {
  $$ = ast_make_enum_declaration($[identifier]);
  if (!$$) {
    AST_ERROR("enum-declaration", "\"enum\" identifier");
  }
}
;

enumerator-list
: enumerator {
  $$ = ast_make_enumerator_list();
  $$ = ast_push_enumerator_list($$, $[enumerator]);
  if (!$$) {
    AST_ERROR("enumerator-list", "enumerator");
  }
}
| enumerator-list[src] ',' enumerator {
  $$ = ast_push_enumerator_list($[src], $[enumerator]);
  if (!$$) {
    AST_ERROR("enumerator-list", "enumerator-list ',' enumerator");
  }
}
;

enumerator
: enumeration-constant {
  $$ = ast_make_enumerator($[enumeration-constant]);
  if (!$$) {
    AST_ERROR("enumerator", "enumeration-constant");
  }
}
| enumerator-with-initializer {
  $$ = ast_make_enumerator($[enumerator-with-initializer]);
  if (!$$) {
    AST_ERROR("enumerator", "enumerator-with-initializer");
  }
}
;

enumerator-with-initializer
: enumeration-constant '=' constant-expression {
  $$ = ast_make_enumerator_with_initializer($[enumeration-constant], $[constant-expression]);
  if (!$$) {
    AST_ERROR("enumerator-with-initializer", "enumeration-constant '=' constant-expression");
  }
}
;

type-qualifier
: "const" {
  $$ = ast_make_type_qualifier($["const"]);
  if (!$$) {
    AST_ERROR("type-qualifier", "\"const\"");
  }
}
| "volatile" {
  $$ = ast_make_type_qualifier($["volatile"]);
  if (!$$) {
    AST_ERROR("type-qualifier", "\"volatile\"");
  }
}
;

declarator.opt
: /* empty */ {
  $$ = ast_make_declarator();
}
| declarator {
  $$ = $[declarator];
}
;

declarator
: pointer.opt direct-declarator {
  $$ = ast_make_declarator($[pointer.opt], $[direct-declarator]);
  if (!$$) {
    AST_ERROR("declarator", "pointer.opt direct-declarator");
  }
}
;

direct-declarator
: identifier {
  $$ = ast_make_direct_declarator($[identifier]);
  if (!$$) {
    AST_ERROR("direct-declarator", "identifier");
  }
}
| '(' declarator ')' {
  $$ = ast_make_direct_declarator($[declarator]);
  if (!$$) {
    AST_ERROR("direct-declarator", "'(' declarator ')'");
  }
}
| array-declarator {
  $$ = ast_make_direct_declarator($[array-declarator]);
  if (!$$) {
    AST_ERROR("direct-declarator", "array-declarator");
  }
}
| function-declarator {
  $$ = ast_make_direct_declarator($[function-declarator]);
  if (!$$) {
    AST_ERROR("direct-declarator", "function-declarator");
  }
}
| old-style-function-declarator {
  $$ = ast_make_direct_declarator($[old-style-function-declarator]);
  if (!$$) {
    AST_ERROR("direct-declarator", "old-style-function-declarator");
  }
}
;

array-declarator
: direct-declarator '[' constant-expression.opt ']' {
  $$ = ast_make_array_declarator($[direct-declarator], $[constant-expression.opt]);
  if (!$$) {
    AST_ERROR("array-declarator", "direct-declarator '[' constant-expression.opt ']'");
  }
}
;

function-declarator
: direct-declarator '(' parameter-type-list ')' {
  $$ = ast_make_function_declarator($[direct-declarator], $[parameter-type-list]);
  if (!$$) {
    AST_ERROR("function-declarator", "direct-declarator '(' parameter-type-list ')'");
  }
}
;

old-style-function-declarator
: direct-declarator '(' identifier-list.opt ')' {
  $$ = ast_make_old_style_function_declarator($[direct-declarator], $[identifier-list.opt]);
  if (!$$) {
    AST_ERROR("old-style-function-declarator", "direct-declarator '(' identifier-list.opt ')'");
  }
}
;

pointer.opt
: /* empty */ {
  $$ = ast_make_pointer();
}
| pointer {
  $$ = $[pointer];
}
;

pointer
: '*' type-qualifier-list.opt {
  $$ = ast_make_pointer($[type-qualifier-list.opt]);
  if (!$$) {
    AST_ERROR("pointer", "'*' type-qualifier-list.opt");
  }
}
| '*' type-qualifier-list.opt pointer {
  $$ = ast_make_pointer($[type-qualifier-list.opt], $[pointer]);
  if (!$$) {
    AST_ERROR("pointer", "'*' type-qualifier-list.opt pointer");
  }
}
;

type-qualifier-list.opt
: /* empty */ {
  $$ = ast_make_type_qualifier_list();
}
| type-qualifier-list {
  $$ = $[type-qualifier-list];
}
;

type-qualifier-list
: type-qualifier {
  $$ = ast_make_type_qualifier_list($[type-qualifier]);
  if (!$$) {
    AST_ERROR("type-qualifier-list", "type-qualifier");
  }
}
| type-qualifier-list type-qualifier {
  $$ = ast_make_type_qualifier_list($[type-qualifier-list], $[type-qualifier]);
  if (!$$) {
    AST_ERROR("type-qualifier-list", "type-qualifier-list type-qualifier");
  }
}
;

parameter-type-list.opt
: /* empty */ {
  $$ = ast_make_parameter_type_list();
}
| parameter-type-list {
  $$ = $[parameter-type-list];
}
;

parameter-type-list
: parameter-list {
  $$ = ast_make_parameter_type_list($[parameter-list]);
  if (!$$) {
    AST_ERROR("parameter-type-list", "parameter-list");
  }
}
| variadic-parameter-list {
  $$ = ast_make_parameter_type_list($[variadic-parameter-list]);
  if (!$$) {
    AST_ERROR("parameter-type-list", "variadic-parameter-list");
  }
}
;

variadic-parameter-list
: parameter-list ',' "..." {
  $$ = ast_make_variadic_parameter_list($[parameter-list], $["..."]);
  if (!$$) {
    AST_ERROR("variadic-parameter-list", "parameter-list ',' \"...\"");
  }
}
;

parameter-list
: parameter-declaration {
  $$ = ast_make_parameter_list($[parameter-declaration]);
  if (!$$) {
    AST_ERROR("parameter-list", "parameter-declaration");
  }
}
| parameter-list ',' parameter-declaration {
  $$ = ast_make_parameter_list($[parameter-list], $[parameter-declaration]);
  if (!$$) {
    AST_ERROR("parameter-list", "parameter-list ',' parameter-declaration");
  }
}
;

parameter-declaration
: parameter-concrete-declaration {
  $$ = ast_make_parameter_declaration($[parameter-concrete-declaration]);
  if (!$$) {
    AST_ERROR("parameter-declaration", "parameter-concrete-declaration");
  }
}
| parameter-abstract-declaration {
  $$ = ast_make_parameter_declaration($[parameter-abstract-declaration]);
  if (!$$) {
    AST_ERROR("parameter-declaration", "parameter-abstract-declaration");
  }
}
;

parameter-concrete-declaration
: declaration-specifier-list declarator {
  $$ = ast_make_parameter_concrete_declaration($[declaration-specifier-list], $[declarator]);
  if (!$$) {
    AST_ERROR("parameter-concrete-declaration", "declaration-specifier-list declarator");
  }
}
;

parameter-abstract-declaration
: declaration-specifier-list abstract-declarator.opt {
  $$ = ast_make_parameter_abstract_declaration($[declaration-specifier-list], $[abstract-declarator.opt]);
  if (!$$) {
    AST_ERROR("parameter-abstract-declaration", "declaration-specifier-list abstract-declarator.opt");
  }
}
;

identifier-list.opt
: /* empty */ {
  $$ = ast_make_identifier_list();
}
| identifier-list {
  $$ = $[identifier-list];
}
;

identifier-list
: identifier {
  $$ = ast_make_identifier_list($[identifier]);
  if (!$$) {
    AST_ERROR("identifier-list", "identifier");
  }
}
| identifier-list ',' identifier {
  $$ = ast_make_identifier_list($[identifier-list], $[identifier]);
  if (!$$) {
    AST_ERROR("identifier-list", "identifier-list ',' identifier");
  }
}
;

type-name
: specifier-qualifier-list abstract-declarator.opt {
  $$ = ast_make_type_name($[specifier-qualifier-list], $[abstract-declarator.opt]);
  if (!$$) {
    AST_ERROR("type-name", "specifier-qualifier-list abstract-declarator.opt");
  }
}
;

abstract-declarator.opt
: /* empty */ {
  $$ = ast_make_abstract_declarator();
}
| abstract-declarator {
  $$ = $[abstract-declarator];
}
;

abstract-declarator
: pointer {
  $$ = ast_make_abstract_declarator($[pointer]);
  if (!$$) {
    AST_ERROR("abstract-declarator", "pointer");
  }
}
| pointer-abstract-declarator {
  $$ = ast_make_abstract_declarator($[pointer-abstract-declarator]);
  if (!$$) {
    AST_ERROR("abstract-declarator", "pointer-abstract-declarator");
  }
}
;

pointer-abstract-declarator
: pointer.opt direct-abstract-declarator {
  $$ = ast_make_pointer_abstract_declarator($[pointer.opt], $[direct-abstract-declarator]);
  if (!$$) {
    AST_ERROR("pointer-abstract-declarator", "pointer.opt direct-abstract-declarator");
  }
}
;

direct-abstract-declarator.opt
: /* empty */ {
  $$ = ast_make_direct_abstract_declarator();
}
| direct-abstract-declarator {
  $$ = $[direct-abstract-declarator];
}
;

direct-abstract-declarator
: '(' abstract-declarator ')' {
  $$ = ast_make_direct_abstract_declarator($[abstract-declarator]);
  if (!$$) {
    AST_ERROR("direct-abstract-declarator", "'(' abstract-declarator ')'");
  }
}
| array-abstract-declarator {
  $$ = ast_make_direct_abstract_declarator($[array-abstract-declarator]);
  if (!$$) {
    AST_ERROR("direct-abstract-declarator", "array-abstract-declarator");
  }
}
| function-abstract-declarator {
  $$ = ast_make_direct_abstract_declarator($[function-abstract-declarator]);
  if (!$$) {
    AST_ERROR("direct-abstract-declarator", "function-abstract-declarator");
  }
}
;

array-abstract-declarator
: direct-abstract-declarator.opt '[' constant-expression.opt ']' {
  $$ = ast_make_array_abstract_declarator($[direct-abstract-declarator.opt], $[constant-expression.opt]);
  if (!$$) {
    AST_ERROR("array-abstract-declarator", "direct-abstract-declarator.opt '[' constant-expression.opt ']'");
  }
}
;

function-abstract-declarator
: direct-abstract-declarator.opt '(' parameter-type-list.opt ')' {
  $$ = ast_make_function_abstract_declarator($[direct-abstract-declarator.opt], $[parameter-type-list.opt]);
  if (!$$) {
    AST_ERROR("function-abstract-declarator", "direct-abstract-declarator.opt '(' parameter-type-list.opt ')'");
  }
}
;

typedef-name
: identifier {
  $$ = ast_make_typedef_name($[identifier]);
  if (!$$) {
    AST_ERROR("typedef-name", "identifier");
  }
}
;

initializer
: assignment-expression {
  $$ = ast_make_initializer($[assignment-expression]);
  if (!$$) {
    AST_ERROR("initializer", "assignment-expression");
  }
}
| '{' initializer-list '}' {
  $$ = ast_make_initializer($[initializer-list]);
  if (!$$) {
    AST_ERROR("initializer", "'{' initializer-list '}'");
  }
}
| '{' initializer-list ',' '}' {
  $$ = ast_make_initializer($[initializer-list]);
  if (!$$) {
    AST_ERROR("initializer", "'{' initializer-list ',' '}'");
  }
}
;

initializer-list
: initializer {
  $$ = ast_make_initializer_list($[initializer]);
  if (!$$) {
    AST_ERROR("initializer-list", "initializer");
  }
}
| initializer-list ',' initializer {
  $$ = ast_make_initializer_list($[initializer-list], $[initializer]);
  if (!$$) {
    AST_ERROR("initializer-list", "initializer-list ',' initializer");
  }
}
;

statement
: labeled-statement {
  $$ = ast_make_statement($[labeled-statement]);
  if (!$$) {
    AST_ERROR("statement", "labeled-statement");
  }
}
| compound-statement {
  $$ = ast_make_statement($[compound-statement]);
  if (!$$) {
    AST_ERROR("statement", "compound-statement");
  }
}
| expression-statement {
  $$ = ast_make_statement($[expression-statement]);
  if (!$$) {
    AST_ERROR("statement", "expression-statement");
  }
}
| selection-statement {
  $$ = ast_make_statement($[selection-statement]);
  if (!$$) {
    AST_ERROR("statement", "selection-statement");
  }
}
| iteration-statement {
  $$ = ast_make_statement($[iteration-statement]);
  if (!$$) {
    AST_ERROR("statement", "iteration-statement");
  }
}
| jump-statement {
  $$ = ast_make_statement($[jump-statement]);
  if (!$$) {
    AST_ERROR("statement", "jump-statement");
  }
}
;

labeled-statement
: identifier-labeled-statement {
  $$ = ast_make_labeled_statement($[identifier-labeled-statement]);
  if (!$$) {
    AST_ERROR("labeled-statement", "identifier-labeled-statement");
  }
}
| case-labeled-statement {
  $$ = ast_make_labeled_statement($[case-labeled-statement]);
  if (!$$) {
    AST_ERROR("labeled-statement", "case-labeled-statement");
  }
}
| default-labeled-statement {
  $$ = ast_make_labeled_statement($[default-labeled-statement]);
  if (!$$) {
    AST_ERROR("labeled-statement", "default-labeled-statement");
  }
}
;

identifier-labeled-statement
: identifier ':' statement {
  $$ = ast_make_identifier_labeled_statement($[identifier], $[statement]);
  if (!$$) {
    AST_ERROR("identifier-labeled-statement", "identifier ':' statement");
  }
}
;

case-labeled-statement
: "case" constant-expression ':' statement {
  $$ = ast_make_case_labeled_statement($[constant-expression], $[statement]);
  if (!$$) {
    AST_ERROR("case-labeled-statement", "\"case\" constant-expression ':' statement");
  }
}
;

default-labeled-statement
: "default" ':' statement {
  $$ = ast_make_default_labeled_statement($[statement]);
  if (!$$) {
    AST_ERROR("default-labeled-statement", "\"default\" ':' statement");
  }
}
;

compound-statement
: '{' declaration-list.opt statement-list.opt '}' {
  $$ = ast_make_compound_statement($[declaration-list.opt], $[statement-list.opt]);
  if (!$$) {
    AST_ERROR("compound-statement", "'{' declaration-list.opt statement-list.opt '}'");
  }
}
;

declaration-list.opt
: %empty {
  $$ = ast_make_declaration_list();
}
| declaration-list {
  $$ = $[declaration-list];
}
;

declaration-list
: declaration {
  $$ = ast_make_declaration_list();
  $$ = ast_push_declaration_list($$, $[declaration]);
  if (!$$) {
    AST_ERROR("declaration-list", "declaration");
  }
}
| declaration-list[src] declaration {
  $$ = ast_push_declaration_list($[src], $[declaration]);
  if (!$$) {
    AST_ERROR("declaration-list", "declaration-list declaration");
  }
}
;

statement-list.opt
: %empty {
  $$ = ast_make_statement_list();
}
| statement-list {
  $$ = $[statement-list];
}
;

statement-list
: statement {
  $$ = ast_make_statement_list();
  $$ = ast_push_statement_list($$, $[statement]);
  if (!$$) {
    AST_ERROR("statement-list", "statement");
  }
}
| statement-list[src] statement {
  $$ = ast_push_statement_list($[src], $[statement]);
  if (!$$) {
    AST_ERROR("statement-list", "statement-list statement");
  }
}
;

expression-statement
: expression.opt ';' {
  $$ = ast_make_expression_statement($[expression.opt]);
  if (!$$) {
    AST_ERROR("expression-statement", "expression.opt ';'");
  }
}
;

selection-statement
: if-statement {
  $$ = ast_make_selection_statement($[if-statement]);
  if (!$$) {
    AST_ERROR("selection-statement", "if-statement");
  }
}
| if-else-statement {
  $$ = ast_make_selection_statement($[if-else-statement]);
  if (!$$) {
    AST_ERROR("selection-statement", "if-else-statement");
  }
}
| switch-statement {
  $$ = ast_make_selection_statement($[switch-statement]);
  if (!$$) {
    AST_ERROR("selection-statement", "switch-statement");
  }
}
;

if-statement
: "if" '(' expression ')' statement {
  $$ = ast_make_if_statement($[expression], $[statement]);
  if (!$$) {
    AST_ERROR("if-statement", "\"if\" '(' expression ')' statement");
  }
}
;

if-else-statement
: "if" '(' expression ')' statement[if] "else" statement[else] {
  $$ = ast_make_if_else_statement($[expression], $[if], $[else]);
  if (!$$) {
    AST_ERROR("if-else-statement", "\"if\" '(' expression ')' statement \"else\" statement");
  }
}
;

switch-statement
: "switch" '(' expression ')' statement {
  $$ = ast_make_switch_statement($[expression], $[statement]);
  if (!$$) {
    AST_ERROR("switch-statement", "\"switch\" '(' expression ')' statement");
  }
}
;

iteration-statement
: while-statement {
  $$ = ast_make_iteration_statement($[while-statement]);
  if (!$$) {
    AST_ERROR("iteration-statement", "while-statement");
  }
}
| do-while-statement {
  $$ = ast_make_iteration_statement($[do-while-statement]);
  if (!$$) {
    AST_ERROR("iteration-statement", "do-while-statement");
  }
}
| for-statement {
  $$ = ast_make_iteration_statement($[for-statement]);
  if (!$$) {
    AST_ERROR("iteration-statement", "for-statement");
  }
}
;

while-statement
: "while" '(' expression ')' statement {
  $$ = ast_make_while_statement($[expression], $[statement]);
  if (!$$) {
    AST_ERROR("while-statement", "\"while\" '(' expression ')' statement");
  }
}
;

do-while-statement
: "do" statement "while" '(' expression ')' ';' {
  $$ = ast_make_do_while_statement($[statement], $[expression]);
  if (!$$) {
    AST_ERROR("do-while-statement", "\"do\" statement \"while\" '(' expression ')' ';'");
  }
}
;

for-statement
: "for" '(' expression.opt[expression_1] ';' expression.opt[expression_2] ';' expression.opt[expression_3] ')' statement {
  $$ = ast_make_for_statement($[expression_1], $[expression_2], $[expression_3], $[statement]);
  if (!$$) {
    AST_ERROR("for-statement", "\"for\" '(' expression.opt ';' expression.opt ';' expression.opt ')' statement");
  }
}
;

jump-statement
: goto-jump-statement {
  $$ = ast_make_jump_statement($[goto-jump-statement]);
  if (!$$) {
    AST_ERROR("jump-statement", "goto-jump-statement");
  }
}
| continue-jump-statement {
  $$ = ast_make_jump_statement($[continue-jump-statement]);
  if (!$$) {
    AST_ERROR("jump-statement", "continue-jump-statement");
  }
}
| break-jump-statement {
  $$ = ast_make_jump_statement($[break-jump-statement]);
  if (!$$) {
    AST_ERROR("jump-statement", "break-jump-statement");
  }
}
| return-jump-statement {
  $$ = ast_make_jump_statement($[return-jump-statement]);
  if (!$$) {
    AST_ERROR("jump-statement", "return-jump-statement");
  }
}
| void-return-jump-statement {
  $$ = ast_make_jump_statement($[void-return-jump-statement]);
  if (!$$) {
    AST_ERROR("jump-statement", "void-return-jump-statement");
  }
}
;

goto-jump-statement
: "goto" identifier ';' {
  $$ = ast_make_goto_jump_statement($[identifier]);
  if (!$$) {
    AST_ERROR("goto-jump-statement", "\"goto\" identifier ';'");
  }
}
;

continue-jump-statement
: "continue" ';' {
  $$ = ast_make_continue_jump_statement();
}
;

break-jump-statement
: "break" ';' {
  $$ = ast_make_break_jump_statement();
}
;

return-jump-statement
: "return" expression ';' {
  $$ = ast_make_return_jump_statement($[expression]);
  if (!$$) {
    AST_ERROR("return-jump-statement", "\"return\" expression ';'");
  }
}
;

void-return-jump-statement
: "return" ';' {
  $$ = ast_make_void_return_jump_statement();
}
;

translation-unit
: external-declaration {
  $$ = ast_make_translation_unit();
  $$ = ast_push_translation_unit($$, $[external-declaration]);
  if (!$$) {
    AST_ERROR("translation-unit", "external-declaration");
  }
}
| translation-unit[src] external-declaration {
  $$ = ast_push_translation_unit($[src], $[external-declaration]);
  if (!$$) {
    AST_ERROR("translation-unit", "translation-unit external-declaration");
  }
}
;

external-declaration
: function-definition {
  $$ = ast_make_external_declaration($[function-definition]);
  if (!$$) {
    AST_ERROR("external-declaration", "function-definition");
  }
}
| declaration {
  $$ = ast_make_external_declaration($[declaration]);
  if (!$$) {
    AST_ERROR("external-declaration", "declaration");
  }
}
;

function-definition
: declaration-specifier-list.opt declarator declaration-list.opt compound-statement {
  $$ = ast_make_function_definition($[declaration-specifier-list.opt], $[declarator],
      $[declaration-list.opt], $[compound-statement]);
  if (!$$) {
    AST_ERROR("function-definition", "declaration-specifier-list.opt declarator declaration-list.opt compound-statement");
  }
}
;

%%

void yyerror(const char* s) {
  fprintf(stderr, "%s\n", s);
}
