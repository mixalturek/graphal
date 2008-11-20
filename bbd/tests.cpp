/*
 *      tests.cpp
 *
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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


#include "tests.hpp"
#include "logger.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuebool.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include "lexan.hpp"

/////////////////////////////////////////////////////////////////////////////
////

// TODO: check __STRING(expr) in non-Linux OS, see /usr/include/assert.h
// TODO: Try to use VERIFY() from MFC in MS Windows

// Verify macro, like assert but without exiting
#define verify(expr)                                                          \
	result = result && (expr);                                                \
	if(!(expr))                                                               \
		ERROR << __FILE__ << ":" << __LINE__ << "   " << __STRING(expr) << endl


/////////////////////////////////////////////////////////////////////////////
////

Tests::Tests()
{

}


Tests::~Tests()
{

}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testResult(const string& testName, bool result)
{
	if(result)
		INFO  << _("[ OK ]     ") << testName << endl;
	else
		ERROR << _("[ FAILED ] ") << testName << endl;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
////

void Tests::run(void)
{
	uint failed = 0;
	failed += !testMemoryLeaks();
	failed += !testDoubleDispatching();
	failed += !testVariableStruct();
	failed += !testGraphs();
	failed += !testLexanTerminalSymbols();
	failed += !testLexanInt();
	failed += !testLexanFloat();
	failed += !testLexanString();
	failed += !testLexanComments();
	failed += !testLexanSourceCode();

	// Template
	// failed += !test();

	INFO << _("Number of failed tests: ") << failed << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

#ifdef CHECK_MEMORY_LEAKS
bool Tests::testMemoryLeaks(void)
{
	bool result = true;

	Value* i = new ValueInt(5);
	Value* j = new ValueBool(true);
	Value* k = new ValueString("bagr");

	delete i;
	i = NULL;

	verify(BaseObject::getNumberOfLeaks() == 2);

	delete j;
	delete k;
	j = NULL;
	k = NULL;

	verify(BaseObject::getNumberOfLeaks() == 0);

	return testResult(__FUNCTION__, result);
}
#endif // CHECK_MEMORY_LEAKS


bool Tests::testDoubleDispatching(void)
{
	bool result = true;

	PTR_Value varleft(new ValueInt(5));
	PTR_Value varright(new ValueFloat(3.4f));
	PTR_Value varsub(new ValueFloat(2.0f));

	verify(varleft->add(*varright)->div(*varsub)->toString() == "4.2");
	return testResult(__FUNCTION__, result);
}


bool Tests::testVariableStruct(void)
{
	bool result = true;

	ValueStruct vs;
	vs.setValue("testi", new ValueInt(42));
	vs.setValue("testb", new ValueBool(true));
	vs.setValue("tests", new ValueString("bagr"));

	verify(vs.getValue("testi")->toString() == "42");
	verify(vs.getValue("testb")->toString() == "true");
	verify(vs.getValue("tests")->toString() == "bagr");
	verify(vs.getValue("heh")->toString() == "NULL");

	return testResult(__FUNCTION__, result);
}


bool Tests::testGraphs(void)
{
	bool result = true;

	Graph g;
	Vertex* v1 = g.generateVertex();
	Vertex* v2 = g.generateVertex();
	Vertex* v3 = g.generateVertex();
	Vertex* v4 = g.generateVertex();

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 0);

	Edge* e1 = g.generateEdge(v1, v2);
	Edge* e2 = g.generateEdge(v2, v3);
	Edge* e3 = g.generateEdge(v3, v4);

	verify(e1->getBeginVertex() == v1);
	verify(e1->getEndVertex() == v2);
	verify(e2->getBeginVertex() == v2);
	verify(e2->getEndVertex() == v3);
	verify(e3->getBeginVertex() == v3);
	verify(e3->getEndVertex() == v4);

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 3);
	verify(v1->getDegree() == 1);
	verify(v2->getDegree() == 2);
	verify(v3->getDegree() == 2);
	verify(v4->getDegree() == 1);

	g.deleteEdge(e1);
	e1 = NULL;

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 2);
	verify(v1->getDegree() == 0);
	verify(v2->getDegree() == 1);
	verify(v3->getDegree() == 2);
	verify(v4->getDegree() == 1);

	g.deleteVertex(v2);
	v2 = NULL;

	verify(g.getNumVertices() == 3);
	verify(g.getNumEdges() == 1);
	verify(v1->getDegree() == 0);
	// verify(v2->getDegree() == 1); // deleted
	verify(v3->getDegree() == 1);
	verify(v4->getDegree() == 1);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanTerminalSymbols(void)
{
	bool result = true;

	Lexan lexan(
		"function return if else while for foreach break continue { } ( ) [ ] "
		", ; . ! = += -= *= /= %= || && < > <= >= == != + - * / % ++ -- "
		"null true false", false);

	LEXTOKEN tok;

	tok = lexan.nextToken(); verify(tok == LEX_FUNCTION);
	tok = lexan.nextToken(); verify(tok == LEX_RETURN);
	tok = lexan.nextToken(); verify(tok == LEX_IF);
	tok = lexan.nextToken(); verify(tok == LEX_ELSE);
	tok = lexan.nextToken(); verify(tok == LEX_WHILE);
	tok = lexan.nextToken(); verify(tok == LEX_FOR);
	tok = lexan.nextToken(); verify(tok == LEX_FOREACH);
	tok = lexan.nextToken(); verify(tok == LEX_BREAK);
	tok = lexan.nextToken(); verify(tok == LEX_CONTINUE);
	tok = lexan.nextToken(); verify(tok == LEX_LVA);
	tok = lexan.nextToken(); verify(tok == LEX_RVA);
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_RPA);
	tok = lexan.nextToken(); verify(tok == LEX_LSA);
	tok = lexan.nextToken(); verify(tok == LEX_RSA);
	tok = lexan.nextToken(); verify(tok == LEX_COMMA);
	tok = lexan.nextToken(); verify(tok == LEX_SEMICOLON);
	tok = lexan.nextToken(); verify(tok == LEX_DOT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_NOT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_OP_PLUS_AS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS_AS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT_AS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_DIV_AS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MOD_AS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_OR);
	tok = lexan.nextToken(); verify(tok == LEX_OP_AND);
	tok = lexan.nextToken(); verify(tok == LEX_OP_LESS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_GREATER);
	tok = lexan.nextToken(); verify(tok == LEX_OP_LESS_EQ);
	tok = lexan.nextToken(); verify(tok == LEX_OP_GREATER_EQ);
	tok = lexan.nextToken(); verify(tok == LEX_OP_EQUAL);
	tok = lexan.nextToken(); verify(tok == LEX_OP_NOT_EQ);
	tok = lexan.nextToken(); verify(tok == LEX_OP_PLUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_DIV);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MOD);
	tok = lexan.nextToken(); verify(tok == LEX_OP_PLUS_PLUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_NULL);
	tok = lexan.nextToken(); verify(tok == LEX_TRUE);
	tok = lexan.nextToken(); verify(tok == LEX_FALSE);

	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanInt(void)
{
	bool result = true;
	LEXTOKEN tok;
	int i;

	Lexan lexan(
		"2 26 999999999 2147483647 -2147483647 0 05 006 0362457 0x20 0x20e9 0xff 0x36a5d 25,356", false);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 2);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 26);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 999999999);

	// INT_MAX
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 2147483647);

	// INT_MIN
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 2147483647);

	// OCT
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 05);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 006);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0362457);

	// HEX
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0x20);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0x20e9);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0xff);

	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 0x36a5d);

	// This is not float (comma instead of dot)
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 25);
	tok = lexan.nextToken(); verify(tok == LEX_COMMA);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 356);

	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanFloat(void)
{
	bool result = true;
	LEXTOKEN tok;
	float f;

	Lexan lexan(
		". .= .1 .12 .12e6 0.12e6 0.0 .0 0. 25.3688 12e-1 12e+1 25e7", false);

	tok = lexan.nextToken(); verify(tok == LEX_DOT);
	tok = lexan.nextToken(); verify(tok == LEX_DOT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 0.1f);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f > 0.11999999f && f < 1.12000001f);
	// DBG << f << endl; // Displays 0.12
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f > 119999.99 && f < 120000.01);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f > 119999.99 && f < 120000.01);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 0.0f);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 0.0f);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 0.0f);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f > 25.36879f && f < 25.368801f);

	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 12e-1f);
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 12e+1f);

	// This is mapped to float
	tok = lexan.nextToken(); verify(tok == LEX_FLOAT);
	f = lexan.getFloat(); verify(f == 25e7);

	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanString(void)
{
	bool result = true;
	LEXTOKEN tok;
	string str;

	Lexan lexan(
		"  \"privet, mir\"  \"rm -rf c:\\\\windows\\\\\"  \"begin-\\x30-end\"  \"begin-\\x20-end\"  "
		"  \"begin-\\065-end\"  \"begin-\\066-end\"  \"begin-\\111-end\" "
		"  \"begin-\\112-end\"  \"begin-\\377-end\"  "
		, false);

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "privet, mir");

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "rm -rf c:\\windows\\");

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\x30-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-0-end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\x20-end");
	// DBG << "'" << str  << "'" << endl; // 'begin- -end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\065-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-5-end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\066-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-6-end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\111-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-I-end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\112-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-J-end'

	tok = lexan.nextToken(); verify(tok == LEX_STRING);
	str = lexan.getString(); verify(str == "begin-\377-end");
	// DBG << "'" << str  << "'" << endl; // 'begin-˙-end'

	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanComments(void)
{
	bool result = true;
	LEXTOKEN tok;

	Lexan lexan(
		"  /**/   /*  */   /***/   /* blem */   /***sf asf*sad/fasd*/  // :-) "
		, false);


	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}


bool Tests::testLexanSourceCode(void)
{
	bool result = true;
	LEXTOKEN tok;
	string str;
	int i;

	Lexan lexan(
		"/* factorial function */"
		"function factorial(number)"
		"{"
		"	if(number < 2)"
		"		return 1;"
		"	else"
		"		return number * factorial(number - 1);"
		"}"
		"/* EOF */"
		, false);

	tok = lexan.nextToken(); verify(tok == LEX_FUNCTION);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "factorial");
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_RPA);
	tok = lexan.nextToken(); verify(tok == LEX_LVA);
	tok = lexan.nextToken(); verify(tok == LEX_IF);
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_OP_LESS);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 2);
	tok = lexan.nextToken(); verify(tok == LEX_RPA);
	tok = lexan.nextToken(); verify(tok == LEX_RETURN);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 1);
	tok = lexan.nextToken(); verify(tok == LEX_SEMICOLON);
	tok = lexan.nextToken(); verify(tok == LEX_ELSE);
	tok = lexan.nextToken(); verify(tok == LEX_RETURN);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "factorial");
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_NAME);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_INT);
	i = lexan.getInt(); verify(i == 1);
	tok = lexan.nextToken(); verify(tok == LEX_RPA);
	tok = lexan.nextToken(); verify(tok == LEX_SEMICOLON);
	tok = lexan.nextToken(); verify(tok == LEX_RVA);

	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);
	tok = lexan.nextToken(); verify(tok == LEX_EOF);

	return testResult(__FUNCTION__, result);
}

// TODO: include, define...


/*
// Template
bool Tests::test(void)
{
	bool result = true;

	// Add code here
	verify(true);

	return testResult(__FUNCTION__, result);
}
*/
