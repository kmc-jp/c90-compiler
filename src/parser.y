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
: /* empty */ {
  $$ = ast_make_identifier();
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
  $$ = ast_make_bitwise_AND_expression($[equality-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-expression", "equality-expression");
  }
}
| bitwise-AND-operator-expression {
  $$ = ast_make_bitwise_AND_expression($[bitwise-AND-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-expression", "bitwise-AND-operator-expression");
  }
}
;

bitwise-AND-operator-expression
: bitwise-AND-expression '&' equality-expression {
  $$ = ast_make_bitwise_AND_operator_expression($[bitwise-AND-expression], $[equality-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-operator-expression", "bitwise-AND-expression '&' equality-expression");
  }
}
;

bitwise-XOR-expression
: bitwise-AND-expression {
  $$ = ast_make_bitwise_XOR_expression($[bitwise-AND-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-expression", "bitwise-AND-expression");
  }
}
| bitwise-XOR-operator-expression {
  $$ = ast_make_bitwise_XOR_expression($[bitwise-XOR-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-expression", "bitwise-XOR-operator-expression");
  }
}
;

bitwise-XOR-operator-expression
: bitwise-XOR-expression '^' bitwise-AND-expression {
  $$ = ast_make_bitwise_XOR_operator_expression($[bitwise-XOR-expression], $[bitwise-AND-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-operator-expression", "bitwise-XOR-expression '^' bitwise-AND-expression");
  }
}
;

bitwise-OR-expression
: bitwise-XOR-expression {
  $$ = ast_make_bitwise_OR_expression($[bitwise-XOR-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-expression", "bitwise-XOR-expression");
  }
}
| bitwise-OR-operator-expression {
  $$ = ast_make_bitwise_OR_expression($[bitwise-OR-operator-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-expression", "bitwise-OR-operator-expression");
  }
}
;

bitwise-OR-operator-expression
: bitwise-OR-expression '|' bitwise-XOR-expression {
  $$ = ast_make_bitwise_OR_operator_expression($[bitwise-OR-expression], $[bitwise-XOR-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-operator-expression", "bitwise-OR-expression '|' bitwise-XOR-expression");
  }
}
;

logical-AND-expression
: bitwise-OR-expression {
  $$ = ast_make_logical_AND_expression($[bitwise-OR-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-expression", "bitwise-OR-expression");
  }
}
| logical-AND-operator-expression {
  $$ = ast_make_logical_AND_expression($[logical-AND-operator-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-expression", "logical-AND-operator-expression");
  }
}
;

logical-AND-operator-expression
: logical-AND-expression "&&" bitwise-OR-expression {
  $$ = ast_make_logical_AND_operator_expression($[logical-AND-expression], $[bitwise-OR-expression]);
  if (!$$) {
    AST_ERROR("logical-AND-operator-expression", "logical-AND-expression \"&&\" bitwise-OR-expression");
  }
}
;

logical-OR-expression
: logical-AND-expression {
  $$ = ast_make_logical_OR_expression($[logical-AND-expression]);
  if (!$$) {
    AST_ERROR("logical-OR-expression", "logical-AND-expression");
  }
}
| logical-OR-operator-expression {
  $$ = ast_make_logical_OR_expression($[logical-OR-operator-expression]);
  if (!$$) {
    AST_ERROR("logical-OR-expression", "logical-OR-operator-expression");
  }
}
;

logical-OR-operator-expression
: logical-OR-expression "||" logical-AND-expression {
  $$ = ast_make_logical_OR_operator_expression($[logical-OR-expression], $[logical-AND-expression]);
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
  $$ = ast_make_subtraction_assignment_expression($[unary-expression], $["-="], $[assignment-expression]);
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
  $$ = ast_make_bitwise_AND_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-AND-assignment-expression", "unary-expression \"&=\" assignment-expression");
  }
}
;

bitwise-XOR-assignment-expression
: unary-expression "^=" assignment-expression {
  $$ = ast_make_bitwise_XOR_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-XOR-assignment-expression", "unary-expression \"^=\" assignment-expression");
  }
}
;

bitwise-OR-assignment-expression
: unary-expression "|=" assignment-expression {
  $$ = ast_make_bitwise_OR_assignment_expression($[unary-expression], $[assignment-expression]);
  if (!$$) {
    AST_ERROR("bitwise-OR-assignment-expression", "unary-expression \"|=\" assignment-expression");
  }
}
;

expression.opt
: /* empty */ {
  $$ = ast_make_expression();
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
: /* empty */ {
  $$ = ast_make_constant_expression();
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

storage-class-specifier
: "typedef" {
  $$ = ast_make_storage_class_specifier($["typedef"]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "\"typedef\"");
  }
}
| "extern" {
  $$ = ast_make_storage_class_specifier($["extern"]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "\"extern\"");
  }
}
| "static" {
  $$ = ast_make_storage_class_specifier($["static"]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "\"static\"");
  }
}
| "auto" {
  $$ = ast_make_storage_class_specifier($["auto"]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "\"auto\"");
  }
}
| "register" {
  $$ = ast_make_storage_class_specifier($["register"]);
  if (!$$) {
    AST_ERROR("storage-class-specifier", "\"register\"");
  }
}
;

type-specifier
: "void" {
  $$ = ast_make_type_specifier($["void"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"void\"");
  }
}
| "char" {
  $$ = ast_make_type_specifier($["char"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"char\"");
  }
}
| "short" {
  $$ = ast_make_type_specifier($["short"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"short\"");
  }
}
| "int" {
  $$ = ast_make_type_specifier($["int"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"int\"");
  }
}
| "long" {
  $$ = ast_make_type_specifier($["long"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"long\"");
  }
}
| "float" {
  $$ = ast_make_type_specifier($["float"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"float\"");
  }
}
| "double" {
  $$ = ast_make_type_specifier($["double"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"double\"");
  }
}
| "signed" {
  $$ = ast_make_type_specifier($["signed"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"signed\"");
  }
}
| "unsigned" {
  $$ = ast_make_type_specifier($["unsigned"]);
  if (!$$) {
    AST_ERROR("type-specifier", "\"unsigned\"");
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
: "struct" {
  $$ = ast_make_struct_or_union($["struct"]);
  if (!$$) {
    AST_ERROR("struct-or-union", "\"struct\"");
  }
}
| "union" {
  $$ = ast_make_struct_or_union($["union"]);
  if (!$$) {
    AST_ERROR("struct-or-union", "\"union\"");
  }
}
;

struct-declaration-list
: struct-declaration {
  $$ = ast_make_struct_declaration_list($[struct-declaration]);
  if (!$$) {
    AST_ERROR("struct-declaration-list", "struct-declaration");
  }
}
| struct-declaration-list struct-declaration {
  $$ = ast_make_struct_declaration_list($[struct-declaration-list], $[struct-declaration]);
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
: /* empty */ {
  $$ = ast_make_specifier_qualifier_list();
}
| specifier-qualifier-list {
  $$ = $[specifier-qualifier-list];
}
;

specifier-qualifier-list
: specifier-qualifier specifier-qualifier-list.opt {
  $$ = ast_make_specifier_qualifier_list($[specifier-qualifier], $[specifier-qualifier-list.opt]);
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
  $$ = ast_make_struct_declarator_list($[struct-declarator]);
  if (!$$) {
    AST_ERROR("struct-declarator-list", "struct-declarator");
  }
}
| struct-declarator-list ',' struct-declarator {
  $$ = ast_make_struct_declarator_list($[struct-declarator-list], $[struct-declarator]);
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
  $$ = ast_make_enum_definition($["enum"], $[identifier.opt], $[enumerator-list]);
  if (!$$) {
    AST_ERROR("enum-definition", "\"enum\" identifier.opt '{' enumerator-list '}'");
  }
}
;

enum-declaration
: "enum" identifier {
  $$ = ast_make_enum_declaration($["enum"], $[identifier]);
  if (!$$) {
    AST_ERROR("enum-declaration", "\"enum\" identifier");
  }
}
;

enumerator-list
: enumerator {
  $$ = ast_make_enumerator_list($[enumerator]);
  if (!$$) {
    AST_ERROR("enumerator-list", "enumerator");
  }
}
| enumerator-list ',' enumerator {
  $$ = ast_make_enumerator_list($[enumerator-list], $[enumerator]);
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
