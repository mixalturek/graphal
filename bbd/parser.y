%{
/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/* bison -v -d -o parser.cpp parser.y */

#include <cassert>
#include "general.hpp"
#include "lexan.hpp"

#include "node.hpp"
#include "nodebinaryadd.hpp"
#include "nodebinaryand.hpp"
#include "nodebinaryass.hpp"
#include "nodebinaryassadd.hpp"
#include "nodebinaryasssub.hpp"
#include "nodebinaryassmult.hpp"
#include "nodebinaryassdiv.hpp"
#include "nodebinaryassmod.hpp"
#include "nodebinarydiv.hpp"
#include "nodebinaryeq.hpp"
#include "nodebinaryge.hpp"
#include "nodebinarygt.hpp"
#include "nodebinaryle.hpp"
#include "nodebinarylt.hpp"
#include "nodebinarymod.hpp"
#include "nodebinarymult.hpp"
#include "nodebinaryne.hpp"
#include "nodebinaryor.hpp"
#include "nodebinarysub.hpp"
#include "nodebinaryindex.hpp"
#include "nodebinarymember.hpp"
#include "nodeblock.hpp"
#include "nodecondition.hpp"
#include "nodeemptycommand.hpp"
#include "nodefunctioncall.hpp"
#include "nodefunction.hpp"
#include "nodeloop.hpp"
#include "nodeunarynot.hpp"
#include "nodeunaryreturn.hpp"
#include "nodeunarysub.hpp"
#include "nodeunaryincpre.hpp"
#include "nodeunaryincpost.hpp"
#include "nodeunarydecpre.hpp"
#include "nodeunarydecpost.hpp"
#include "nodevalue.hpp"
#include "nodevariable.hpp"
#include "nodejumpbreak.hpp"
#include "nodejumpcontinue.hpp"

#include "valuebool.hpp"
#include "valueedge.hpp"
#include "valueedgeset.hpp"
#include "valuefloat.hpp"
#include "valuegraph.hpp"
#include "valueint.hpp"
#include "valuenull.hpp"
#include "valuereference.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"
#include "valuevertex.hpp"
#include "valuevertexset.hpp"

// Ja su ale prasatko :-)
static Lexan* g_lexan = NULL;
static Context* g_context = NULL;

int yylex(void);
void yyerror(char const *msg);
%}

%union
{
	int     int_val;
	float   float_val;
	string* string_val;
	Node*   node;
	NodeBlock* nodeblock;
	list<identifier>* list_ids;
}

%token LEX_ERROR
%token LEX_FUNCTION
%token LEX_RETURN
%token LEX_IF
%token LEX_ELSE
%token LEX_WHILE
%token LEX_FOR
%token LEX_FOREACH
%token LEX_BREAK
%token LEX_CONTINUE

%right SUB_ASSIGN ADD_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token INC_OP DEC_OP
%token EQ_OP NE_OP LE_OP GE_OP
%token OR_OP AND_OP

%token LEX_NULL
%token LEX_TRUE
%token LEX_FALSE
%token <int_val>    LEX_INT
%token <int_val>    LEX_NAME
%token <float_val>  LEX_FLOAT
%token <string_val> LEX_STRING

%type <node> primary_expression postfix_expression unary_expression
%type <node> multiplicative_expression additive_expression expression
%type <node> relational_expression equality_expression logical_and_expression
%type <node> logical_or_expression conditional_expression assignment_expression
%type <node> statement expression_statement compound_statement
%type <nodeblock> argument_expression_list block_item_list
%type <list_ids> parameter_list

%error-verbose

%start start

%%
/*
http://www.cplusplus.com/doc/tutorial/operators.html
http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Companion/cxx_crib/precedence.html
http://www.quut.com/c/ANSI-C-grammar-l-1998.html
http://www.quut.com/c/ANSI-C-grammar-y.html
*/

primary_expression
	: LEX_NULL { $$ = new NodeValue(new ValueNull()); }
	| LEX_TRUE { $$ = new NodeValue(new ValueBool(true)); }
	| LEX_FALSE { $$ = new NodeValue(new ValueBool(false)); }
	| LEX_INT { $$ = new NodeValue(new ValueInt($1)); }
	| LEX_NAME { $$ = new NodeVariable($1); }
	| LEX_FLOAT { $$ = new NodeValue(new ValueFloat($1)); }
	| LEX_STRING { $$ = new NodeValue(new ValueString(*$1)); }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new NodeBinaryIndex($1, $3); }
	| postfix_expression '(' ')'
	{
		// To je hnus velebnosti...
		NodeVariable* var = dynamic_cast<NodeVariable*>($1);
		if(var == NULL)
		{
			NodeBinaryMember* mem = dynamic_cast<NodeBinaryMember*>($1);
			if(mem == NULL)
			{
				delete $1;
				yyerror(_("Call operator expects identifier on the left"));
				YYABORT;
			}
			else // variable.f() -> f(variable)
			{
				var = dynamic_cast<NodeVariable*>(mem->getRight());
				assert(var != NULL);// LEX_NAME is always on the right

				$$ = new NodeFunctionCall(var->getName(), new NodeBlock(mem->getLeft()));
				mem->detachLeft();
				delete mem;
			}
		}
		else // f()
		{
			$$ = new NodeFunctionCall(var->getName(), NULL);
			delete $1;
		}
	}
	| postfix_expression '(' argument_expression_list ')'
	{
		// Vidis to, panenko Maria podsrpenska, vidis to?
		NodeVariable* var = dynamic_cast<NodeVariable*>($1);
		if(var == NULL)
		{
			NodeBinaryMember* mem = dynamic_cast<NodeBinaryMember*>($1);
			if(mem == NULL)
			{
				delete $1;
				delete $3;
				yyerror(_("Call operator expects identifier on the left"));
				YYABORT;
			}
			else // variable.f(parameters) -> f(variable, parameters)
			{
				var = dynamic_cast<NodeVariable*>(mem->getRight());
				assert(var != NULL);// LEX_NAME is always on the right

				$3->pushCommandToFront(mem->getLeft());
				$$ = new NodeFunctionCall(var->getName(), $3);
				mem->detachLeft();
				delete mem;
			}
		}
		else // f(parameters)
		{
			$$ = new NodeFunctionCall(var->getName(), $3);
			delete $1;
		}
	}
	| postfix_expression '.' LEX_NAME { $$ = new NodeBinaryMember($1, new NodeVariable($3)); }
	| postfix_expression INC_OP { $$ = new NodeUnaryIncPost($1); }
	| postfix_expression DEC_OP { $$ = new NodeUnaryDecPost($1); }
	;

argument_expression_list
	: assignment_expression { $$ = new NodeBlock($1); }
	| argument_expression_list ',' assignment_expression { $1->pushCommandToBack($3); $$ = $1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new NodeUnaryIncPre($2); }
	| DEC_OP unary_expression { $$ = new NodeUnaryDecPre($2); }
	| '+' unary_expression { $$ = $2; }
	| '-' unary_expression { $$ = new NodeUnarySub($2); }
	| '!' unary_expression { $$ = new NodeUnaryNot($2); }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression { $$ = new NodeBinaryMult($1, $3); }
	| multiplicative_expression '/' unary_expression { $$ = new NodeBinaryDiv($1, $3); }
	| multiplicative_expression '%' unary_expression { $$ = new NodeBinaryMod($1, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new NodeBinaryAdd($1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = new NodeBinarySub($1, $3); }
	;

relational_expression
	: additive_expression { $$ = $1; }
	| relational_expression '<' additive_expression { $$ = new NodeBinaryLt($1, $3); }
	| relational_expression '>' additive_expression { $$ = new NodeBinaryGt($1, $3); }
	| relational_expression LE_OP additive_expression { $$ = new NodeBinaryLe($1, $3); }
	| relational_expression GE_OP additive_expression { $$ = new NodeBinaryGe($1, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = new NodeBinaryEq($1, $3); }
	| equality_expression NE_OP relational_expression { $$ = new NodeBinaryNe($1, $3); }
	;

logical_and_expression
	: equality_expression { $$ = $1; }
	| logical_and_expression AND_OP equality_expression { $$ = new NodeBinaryAnd($1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new NodeBinaryOr($1, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new NodeCondition($1, $3, $5); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression { $$ = new NodeBinaryAss($1, $3); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new NodeBinaryAssMult($1, $3); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new NodeBinaryAssDiv($1, $3); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new NodeBinaryAssMod($1, $3); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new NodeBinaryAssAdd($1, $3); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new NodeBinaryAssSub($1, $3); }
	;

expression
	: assignment_expression { $$ = $1; }
	;

statement
	: compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	/* "parser.y: conflicts: 1 shift/reduce" is ok */
	| LEX_IF '(' expression ')' statement { $$ = new NodeCondition($3, $5, new NodeEmptyCommand()); }
	| LEX_IF '(' expression ')' statement LEX_ELSE statement { $$ = new NodeCondition($3, $5, $7); }
	| LEX_WHILE '(' expression ')' statement { $$ = new NodeLoop(new NodeEmptyCommand(), $3, new NodeEmptyCommand(), $5); }
	| LEX_FOR '(' expression_statement expression_statement ')' statement { $$ = new NodeLoop($3, $4, new NodeEmptyCommand(), $6); }
	| LEX_FOR '(' expression_statement expression_statement expression ')' statement { $$ = new NodeLoop($3, $4, $5, $7); }
	| LEX_BREAK ';' { $$ = new NodeJumpBreak(); }
	| LEX_CONTINUE ';' { $$ = new NodeJumpContinue(); }
	| LEX_RETURN ';' { $$ = new NodeUnaryReturn(new NodeEmptyCommand()); }
	| LEX_RETURN expression ';' { $$ = new NodeUnaryReturn($2); }
	;

expression_statement
	: ';' { $$ = new NodeEmptyCommand(); }
	| expression ';' { $$ = $1; }
	;

compound_statement
	: '{' '}' { $$ = new NodeEmptyCommand(); }
	| '{' block_item_list '}' { $$ = $2; }
	;

block_item_list
	: statement { $$ = new NodeBlock($1); }
	| block_item_list statement { $1->pushCommandToBack($2); $$ = $1; }
	;

function_definition
	: LEX_FUNCTION LEX_NAME '(' parameter_list ')' compound_statement { g_context->addFunction($2, new NodeFunction($4, $6)); }
	| LEX_FUNCTION LEX_NAME '(' ')'  compound_statement { g_context->addFunction($2, new NodeFunction(new list<identifier>(), $5)); }
	;

parameter_list
	: LEX_NAME { $$ = new list<identifier>(); $$->push_back($1); }
	| parameter_list ',' LEX_NAME { $1->push_back($3); $$ = $1; }
	;

start
	: /* empty */
	| start function_definition
	;
%%

int yylex(void)
{
	assert(g_lexan != NULL);
	int tok = g_lexan->nextToken();

	switch(tok)
	{
	case LEX_INT:
		yylval.int_val = g_lexan->getInt();
		break;
	case LEX_NAME:
		yylval.int_val = g_lexan->getIdentifier();
		break;
	case LEX_FLOAT:
		yylval.float_val = g_lexan->getFloat();
		break;
	case LEX_STRING:
		yylval.string_val = &g_lexan->getString();
		break;
	default:
		break;
	}

	return tok;
}

void yyerror(char const *msg)
{
	fprintf(stderr, "%s\n", msg);
}

int parseCode(const string& str, Context& context)
{
	g_lexan = new Lexan(str, &context.getStringTable(), false);
	g_context = &context;

	int ret = yyparse();

	if(ret != 0)
		cerr << "error while parsing" << endl;

	cout << context << endl;

	delete g_lexan;
	g_lexan = NULL;

	return ret;
}
