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
#include "nodeblock.hpp"
#include "nodecondition.hpp"
#include "nodeemptycommand.hpp"
#include "nodefunctioncall.hpp"
#include "nodefunction.hpp"
#include "nodeloop.hpp"
#include "nodeunarynot.hpp"
#include "nodeunaryreturn.hpp"
#include "nodeunarysub.hpp"
#include "nodevalue.hpp"
#include "nodevariable.hpp"

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

int yylex(void);
void yyerror(char const *msg);
%}

%union
{
	int     int_val;
	float   float_val;
	string* string_val;
	Node*   node;
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

%type <node> primary_expression postfix_expression argument_expression_list unary_expression multiplicative_expression additive_expression relational_expression equality_expression logical_and_expression logical_or_expression conditional_expression assignment_expression expression

%error-verbose

%start expression

%%
/* http://www.cplusplus.com/doc/tutorial/operators.html */
/* http://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Companion/cxx_crib/precedence.html */

primary_expression
	: LEX_NULL { $$ = new NodeValue(new ValueNull()); }
	| LEX_TRUE { $$ = new NodeValue(new ValueBool(true)); }
	| LEX_FALSE { $$ = new NodeValue(new ValueBool(false)); }
	| LEX_INT { $$ = new NodeValue(new ValueInt($1)); }
	| LEX_NAME { $$ = new NodeVariable($1); } /* TODO: funkce! */
	| LEX_FLOAT { $$ = new NodeValue(new ValueFloat($1)); }
	| LEX_STRING { $$ = new NodeValue(new ValueString(*$1)); }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = $1; } /* TODO */
	| postfix_expression '(' ')' { $$ = $1; } /* TODO */
	| postfix_expression '(' argument_expression_list ')' { $$ = $1; } /* TODO */
	| postfix_expression '.' LEX_NAME { $$ = $1; } /* TODO */
	| postfix_expression INC_OP { $$ = $1; } /* TODO */
	| postfix_expression DEC_OP { $$ = $1; } /* TODO */
	;

argument_expression_list
	: assignment_expression { $$ = $1; } /* TODO */
	| argument_expression_list ',' assignment_expression { $$ = $1; } /* TODO */
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = $2; } /* TODO */
	| DEC_OP unary_expression { $$ = $2; } /* TODO */
	| '+' unary_expression { $$ = $2; }
	| '-' unary_expression { $$ = new NodeUnarySub($2); }
	| '!' unary_expression { $$ = new NodeUnaryNot($2); }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression { $$ = new NodeBinaryMult($1, $3); }
	| multiplicative_expression '/' unary_expression { $$ = new NodeBinaryDiv($1, $3); } /* TODO: division by zero */
	| multiplicative_expression '%' unary_expression { $$ = new NodeBinaryMod($1, $3); } /* TODO: division by zero */
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
	| logical_or_expression '?' expression ':' conditional_expression { $$ = $3; } /* TODO */
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
	: assignment_expression { $1->dump(cout, 0); delete $1; }
	;

%%

// Ja su ale prasatko :-)
static Lexan* g_lexan = NULL;
static Context* g_context = NULL;

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

void yyerror (char const *msg)
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
