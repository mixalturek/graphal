<?php
$g_title = 'Language grammar';
include 'p_begin.php';
?>

<p>See Bison source file <em>parser.y</em> for actions.</p>

<pre class="spec">
primary_expression
	: LEX_NULL
	| LEX_TRUE
	| LEX_FALSE
	| LEX_INT
	| LEX_IDENTIFIER
	| LEX_FLOAT
	| LEX_STRING
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| LEX_IDENTIFIER '(' ')'
	| LEX_IDENTIFIER '(' argument_expression_list ')'
	| postfix_expression '.' LEX_IDENTIFIER
	| postfix_expression '.' LEX_IDENTIFIER '(' ')'
	| postfix_expression '.' LEX_IDENTIFIER '(' argument_expression_list ')'
	| postfix_expression LEX_INC_OP
	| postfix_expression LEX_DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| LEX_INC_OP unary_expression
	| LEX_DEC_OP unary_expression
	| '+' unary_expression
	| '-' unary_expression
	| '!' unary_expression
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression
	| multiplicative_expression '/' unary_expression
	| multiplicative_expression '%' unary_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

relational_expression
	: additive_expression
	| relational_expression '<' additive_expression
	| relational_expression '>' additive_expression
	| relational_expression LEX_LE_OP additive_expression
	| relational_expression LEX_GE_OP additive_expression
	;

equality_expression
	: relational_expression
	| equality_expression LEX_EQ_OP relational_expression
	| equality_expression LEX_NE_OP relational_expression
	;

logical_and_expression
	: equality_expression
	| logical_and_expression LEX_AND_OP equality_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression LEX_OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression '=' assignment_expression
	| unary_expression LEX_MUL_ASSIGN assignment_expression
	| unary_expression LEX_DIV_ASSIGN assignment_expression
	| unary_expression LEX_MOD_ASSIGN assignment_expression
	| unary_expression LEX_ADD_ASSIGN assignment_expression
	| unary_expression LEX_SUB_ASSIGN assignment_expression
	| unary_expression LEX_REF_ASSIGN assignment_expression
	;

expression
	: assignment_expression
	;

statement
	: compound_statement
	| expression_statement
	/* "parser.y: conflicts: 1 shift/reduce" is ok */
	| LEX_IF '(' expression ')' statement
	| LEX_IF '(' expression ')' statement LEX_ELSE statement
	| LEX_WHILE '(' expression ')' statement
	| LEX_FOR '(' expression_statement expression_statement ')' statement
	| LEX_FOR '(' expression_statement expression_statement expression ')' statement
	| LEX_FOREACH '(' LEX_IDENTIFIER ';' expression ')' statement
	| LEX_BREAK ';'
	| LEX_CONTINUE ';'
	| LEX_RETURN ';'
	| LEX_RETURN expression ';'
	| LEX_GLOBAL LEX_IDENTIFIER ';'
	;

expression_statement
	: ';'
	| expression ';'
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: statement
	| block_item_list statement
	;

function_definition
	: function_and_name '(' parameter_list ')' compound_statement
	| function_and_name '(' ')' compound_statement
	;

function_and_name
	: LEX_FUNCTION LEX_IDENTIFIER
	;

parameter_list
	: LEX_IDENTIFIER
	| parameter_list ',' LEX_IDENTIFIER
	;

start
	: /* empty */
	| start function_definition
	;
</pre>

<?php
include 'p_end.php';
?>
