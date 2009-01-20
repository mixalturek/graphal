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
#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
#include "lexan.hpp"
#include "context.hpp"
#include "nodeunarysub.hpp"
#include "nodeunarynot.hpp"
#include "nodebinaryadd.hpp"
#include "nodebinarysub.hpp"
#include "nodeblock.hpp"
#include "nodecondition.hpp"
#include "nodevariable.hpp"
#include "stringtable.hpp"
#include "countptr.hpp"
#include "nodeemptycommand.hpp"
#include "nodefunction.hpp"
#include "nodefunctioncall.hpp"
#include "nodebinaryass.hpp"
#include "nodevalue.hpp"
#include "nodebinarylt.hpp"
#include "nodeunaryreturn.hpp"
#include "nodebinarymult.hpp"


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
	failed += !testValueStruct();
	failed += !testGraph();
	failed += !testGraphSet();
	failed += !testGraphInvertEdgesOrientation();
	failed += !testLexanTerminalSymbols();
	failed += !testLexanInt();
	failed += !testLexanFloat();
	failed += !testLexanString();
	failed += !testLexanComments();
	failed += !testLexanSourceCode();
	failed += !testNodeUnary();
	failed += !testNodeBinary();
	failed += !testNodeBlock();
	failed += !testNodeVariable();
	failed += !testStringTable();
	failed += !testCountPtr();
	failed += !testNodeFunction();

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

	// Number of allocated objects before the call of this function
	uint numobjects = BaseObject::getNumberOfLeaks();

	Value* i = new ValueInt(5);
	Value* j = new ValueBool(true);
	Value* k = new ValueString("bagr");

	delete i;
	i = NULL;

	verify(BaseObject::getNumberOfLeaks() == 2 + numobjects);

	delete j;
	delete k;
	j = NULL;
	k = NULL;

	verify(BaseObject::getNumberOfLeaks() == 0 + numobjects);

	return testResult(__FUNCTION__, result);
}
#endif // CHECK_MEMORY_LEAKS


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testDoubleDispatching(void)
{
	bool result = true;

	PTR_Value varleft(new ValueInt(5));
	PTR_Value varright(new ValueFloat(3.4f));
	PTR_Value varsub(new ValueFloat(2.0f));

	verify(varleft->add(*varright)->div(*varsub)->toString() == "4.2");
	return testResult(__FUNCTION__, result);
}


bool Tests::testValueStruct(void)
{
	bool result = true;

	ValueStruct vs;
	vs.setItem("testi", new ValueInt(42));
	vs.setItem("testb", new ValueBool(true));
	vs.setItem("tests", new ValueString("bagr"));

	verify(vs.getItem("testi")->toString() == "42");
	verify(vs.getItem("testb")->toString() == "true");
	verify(vs.getItem("tests")->toString() == "bagr");
	verify(vs.getItem("heh")->toString() == "NULL");

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testGraph(void)
{
	bool result = true;

	// v1 ---- v2 ---- v3 ---- v4
	//     e1      e2      e3
	ValueGraph g;

	ValueVertex* v1 = g.addVertex();
	ValueVertex* v2 = g.addVertex();
	ValueVertex* v3 = g.addVertex();
	ValueVertex* v4 = g.addVertex();

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 0);

	ValueEdge* e1 = g.addEdge(v1, v2);
	ValueEdge* e2 = g.addEdge(v2, v3);
	ValueEdge* e3 = g.addEdge(v3, v4);

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



bool Tests::testGraphSet(void)
{
	bool result = true;

	// v1 ---- v2 ---- v3 ---- v4
	//     e1      e2      e3
	ValueGraph g(false);

	ValueVertex* v1 = g.addVertex();
	ValueVertex* v2 = g.addVertex();
	ValueVertex* v3 = g.addVertex();
	ValueVertex* v4 = g.addVertex();
	ValueEdge* e1 = g.addEdge(v1, v2);
	ValueEdge* e2 = g.addEdge(v2, v3);
	ValueEdge* e3 = g.addEdge(v3, v4);


	ValueVertexSet vvs(&g);
	vvs = v1->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(vvs.contains(v2));
	verify(!vvs.contains(v3));
	verify(!vvs.contains(v4));

	vvs = v2->getNeighbors();
	verify(vvs.getNumVertices() == 2);
	verify(vvs.contains(v1));
	verify(vvs.contains(v3));
	verify(!vvs.contains(v4));


	// v1 ----> v2 ----> v3 ----> v4
	//     e1       e2       e3
	g.setOrientation(true);

	vvs = v1->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(vvs.contains(v2));
	verify(!vvs.contains(v3));
	verify(!vvs.contains(v4));

	vvs = v2->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(!vvs.contains(v1));
	verify(vvs.contains(v3));
	verify(!vvs.contains(v4));

	g.setOrientation(false);


	ValueEdgeSet ves(&g);
	ves.addEdge(e1);
	ves.addEdge(e2);
	verify(ves.getNumEdges() == 2);
	verify(ves.contains(e1));
	verify(ves.contains(e2));

	ves.deleteEdge(e1);
	verify(ves.getNumEdges() == 1);
	verify(!ves.contains(e1));
	verify(ves.contains(e2));

	ves.deleteEdge(e2);
	verify(ves.getNumEdges() == 0);
	verify(!ves.contains(e1));
	verify(!ves.contains(e2));

	ves.addEdge(e3);
	verify(ves.getNumEdges() == 1);
	ves.deleteEdge(e3);
	verify(ves.getNumEdges() == 0);

	return testResult(__FUNCTION__, result);
}


bool Tests::testGraphInvertEdgesOrientation(void)
{
	bool result = true;

	// v1 ----> v2 ----> v3 ----> v4
	//     e1       e2       e3
	ValueGraph g(true);

	ValueVertex* v1 = g.addVertex();
	ValueVertex* v2 = g.addVertex();
	ValueVertex* v3 = g.addVertex();
	ValueVertex* v4 = g.addVertex();
	ValueEdge* e1 = g.addEdge(v1, v2);
	ValueEdge* e2 = g.addEdge(v2, v3);
	ValueEdge* e3 = g.addEdge(v3, v4);

	// v1 <---- v2 <---- v3 <---- v4
	//      e1       e2       e3
	g.invertEdgesOrientation();

	ValueVertexSet vvs(&g);

	vvs = v1->getNeighbors();
	verify(vvs.getNumVertices() == 0);
	verify(!vvs.contains(v2));
	verify(!vvs.contains(v3));
	verify(!vvs.contains(v4));

	vvs = v2->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(vvs.contains(v1));
	verify(!vvs.contains(v3));
	verify(!vvs.contains(v4));

	vvs = v3->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(!vvs.contains(v1));
	verify(vvs.contains(v2));
	verify(!vvs.contains(v4));

	vvs = v4->getNeighbors();
	verify(vvs.getNumVertices() == 1);
	verify(!vvs.contains(v1));
	verify(!vvs.contains(v2));
	verify(vvs.contains(v3));

	verify(e1->getBeginVertex() == v2);
	verify(e1->getEndVertex() == v1);

	verify(e2->getBeginVertex() == v3);
	verify(e2->getEndVertex() == v2);

	verify(e3->getBeginVertex() == v4);
	verify(e3->getEndVertex() == v3);

	return testResult(__FUNCTION__, result);
}

/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testLexanTerminalSymbols(void)
{
	bool result = true;

	StringTable stringtable;
	Lexan lexan(
		"function return if else while for foreach break continue { } ( ) [ ] "
		", ; . ! = += -= *= /= %= || && < > <= >= == != + - * / % ++ -- "
		"null true false ? :", &stringtable, false);

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
	tok = lexan.nextToken(); verify(tok == ADD_ASSIGN);
	tok = lexan.nextToken(); verify(tok == SUB_ASSIGN);
	tok = lexan.nextToken(); verify(tok == MUL_ASSIGN);
	tok = lexan.nextToken(); verify(tok == DIV_ASSIGN);
	tok = lexan.nextToken(); verify(tok == MOD_ASSIGN);
	tok = lexan.nextToken(); verify(tok == OR_OP);
	tok = lexan.nextToken(); verify(tok == AND_OP);
	tok = lexan.nextToken(); verify(tok == LEX_OP_LESS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_GREATER);
	tok = lexan.nextToken(); verify(tok == LE_OP);
	tok = lexan.nextToken(); verify(tok == GE_OP);
	tok = lexan.nextToken(); verify(tok == EQ_OP);
	tok = lexan.nextToken(); verify(tok == NE_OP);
	tok = lexan.nextToken(); verify(tok == LEX_OP_PLUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_DIV);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MOD);
	tok = lexan.nextToken(); verify(tok == INC_OP);
	tok = lexan.nextToken(); verify(tok == DEC_OP);
	tok = lexan.nextToken(); verify(tok == LEX_NULL);
	tok = lexan.nextToken(); verify(tok == LEX_TRUE);
	tok = lexan.nextToken(); verify(tok == LEX_FALSE);
	tok = lexan.nextToken(); verify(tok == LEX_QUESTIONMARK);
	tok = lexan.nextToken(); verify(tok == LEX_COLON);

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

	StringTable stringtable;
	Lexan lexan(
		"2 26 999999999 2147483647 -2147483647 0 05 006 0362457 0x20 0x20e9 0xff 0x36a5d 25,356",
		&stringtable, false);

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

	StringTable stringtable;
	Lexan lexan(
		". .= .1 .12 .12e6 0.12e6 0.0 .0 0. 25.3688 12e-1 12e+1 25e7",
		&stringtable, false);

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

	StringTable stringtable;
	Lexan lexan(
		"  \"privet, mir\"  \"rm -rf c:\\\\windows\\\\\"  \"begin-\\x30-end\"  \"begin-\\x20-end\"  "
		"  \"begin-\\065-end\"  \"begin-\\066-end\"  \"begin-\\111-end\" "
		"  \"begin-\\112-end\"  \"begin-\\377-end\"  "
		, &stringtable, false);

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

	StringTable stringtable;
	Lexan lexan(
		"  /**/   /*  */   /***/   /* blem */   /***sf asf*sad/fasd*/  // :-) ",
		&stringtable, false);


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

	StringTable stringtable;
	Lexan lexan(
		"/* factorial function */"
		"function factorial(number)"
		"{"
		"	if(number < 2)"
		"		return 1;"
		"	else"
		"		return number * factorial(number - 1);"
		"}"
		"/* EOF */",
		&stringtable, false);

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


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testNodeUnary(void)
{
	bool result = true;

	string str;

	NodeUnarySub uminus(new NodeValue(new ValueInt(10)));
	str = uminus.execute()->toString();
	verify(str == "-10");

	NodeUnaryNot unot(new NodeValue(new ValueBool(true)));
	str = unot.execute()->toString();
	verify(str == "false");

	return testResult(__FUNCTION__, result);
}


bool Tests::testNodeBinary(void)
{
	bool result = true;

	string str;

	NodeBinaryAdd add(new NodeValue(new ValueInt(10)), new NodeValue(new ValueInt(5)));
	str = add.execute()->toString();
	verify(str == "15");

	NodeBinaryAdd add2(new NodeValue(new ValueInt(10)), new NodeValue(new ValueFloat(5.1f)));
	str = add2.execute()->toString();
	verify(str == "15.1");

	NodeBinaryAdd addsub(new NodeValue(new ValueInt(10)), new NodeUnarySub(new NodeValue(new ValueFloat(5.1f))));
	str = addsub.execute()->toString();
	verify(str == "4.9");

	return testResult(__FUNCTION__, result);
}


bool Tests::testNodeBlock(void)
{
	bool result = true;

	string str;
	NodeBlock* bl = new NodeBlock();// delete in cond destructor

	verify(bl->getNumberOfCommands() == 0);
	bl->pushCommandToBack(new NodeBinaryAdd(new NodeValue(new ValueInt(10)), new NodeValue(new ValueInt(5))));
	bl->pushCommandToBack(new NodeBinaryAdd(new NodeValue(new ValueInt(10)), new NodeValue(new ValueInt(5))));
	verify(bl->getNumberOfCommands() == 2);
	bl->pushCommandToBack(new NodeEmptyCommand());
	verify(bl->getNumberOfCommands() == 3);

	NodeCondition cond(new NodeValue(new ValueBool(true)), bl, NULL);

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testNodeVariable(void)
{
	bool result = true;

	string str;

	NodeVariable* var0 = new NodeVariable(0);
	NodeVariable* var1 = new NodeVariable(1);

	var0->setValue(CountPtr<Value>(new ValueFloat(3.14f)));
	var1->setValue(CountPtr<Value>(new ValueInt(15)));

	NodeBinaryAdd add(new NodeValue(new ValueInt(10)), var0);
	str = add.execute()->toString();
	verify(str == "13.14");

	NodeBinarySub sub(new NodeValue(new ValueInt(20)), var1);
	str = sub.execute()->toString();
	verify(str == "5");

	var1->setValue(CountPtr<Value>(new ValueFloat(3.5f)));
	str = sub.execute()->toString();
	verify(str == "16.5");

	verify(CONTEXT.getLocalVariable(2)->toString() == "NULL");
	verify(CONTEXT.getLocalVariable(57)->toString() == "NULL");

	// TODO:
	// a = b = c = 15;
	// a.member = 15;
	// a[9] = 15;

	CONTEXT.clear();
	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testStringTable(void)
{
	bool result = true;

	StringTable table;
	identifier id;
	verify(table.getNumStrings() == 0);

	id = table.getID("bagr");
	verify(table.getNumStrings() == 1);
	verify(table.getString(id) == "bagr");

	id = table.getID("test");
	verify(table.getNumStrings() == 2);
	verify(table.getString(id) == "test");

	id = table.getID("bagr");
	verify(table.getNumStrings() == 2);
	verify(table.getString(id) == "bagr");

	id = table.getID("test");
	verify(table.getNumStrings() == 2);
	verify(table.getString(id) == "test");

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testCountPtr(void)
{
	bool result = true;

	CountPtr<Value> obj(new ValueInt(5));
	verify(obj.getNumRefs() == 1);
	verify(obj->toString() == "5");

	CountPtr<Value> obj2(obj);
	verify(obj.getNumRefs() == 2);
	verify(obj->toString() == "5");
	verify(obj2.getNumRefs() == 2);
	verify(obj2->toString() == "5");

	CountPtr<Value> obj3 = obj;
	verify(obj.getNumRefs() == 3);
	verify(obj->toString() == "5");
	verify(obj2.getNumRefs() == 3);
	verify(obj2->toString() == "5");
	verify(obj3.getNumRefs() == 3);
	verify(obj3->toString() == "5");

	CountPtr<Value> obj4(new ValueFloat(3.14f));
	verify(obj->toString() == "5");
	verify(obj2->toString() == "5");
	verify(obj3->toString() == "5");
	verify(obj4->toString() == "3.14");

	obj = obj4;
	verify(obj.getNumRefs() == 2);
	verify(obj->toString() == "3.14");
	verify(obj2.getNumRefs() == 2);
	verify(obj2->toString() == "5");
	verify(obj3.getNumRefs() == 2);
	verify(obj3->toString() == "5");
	verify(obj4.getNumRefs() == 2);
	verify(obj4->toString() == "3.14");

	CountPtr<Value> obj5 = obj4;
	verify(obj.getNumRefs() == 3);
	verify(obj->toString() == "3.14");
	verify(obj2.getNumRefs() == 2);
	verify(obj2->toString() == "5");
	verify(obj3.getNumRefs() == 2);
	verify(obj3->toString() == "5");
	verify(obj4.getNumRefs() == 3);
	verify(obj4->toString() == "3.14");
	verify(obj5.getNumRefs() == 3);
	verify(obj5->toString() == "3.14");

	obj2 = CountPtr<Value>(new ValueString("bagr"));
	verify(obj.getNumRefs() == 3);
	verify(obj->toString() == "3.14");
	verify(obj2.getNumRefs() == 1);
	verify(obj2->toString() == "bagr");
	verify(obj3.getNumRefs() == 1);
	verify(obj3->toString() == "5");
	verify(obj4.getNumRefs() == 3);
	verify(obj4->toString() == "3.14");
	verify(obj5.getNumRefs() == 3);
	verify(obj5->toString() == "3.14");

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testNodeFunction(void)
{
	bool result = true;

	const uint func_id = 0;
	const uint local_id = 1;
//	const uint factorial_id = 2;
//	const uint number_id = 3;
	const uint freturn_id = 4;
	const uint freturn_local_id = 5;

	string str;

	/*
	function func()
	{
		local = 10;
	}
	*/
	NodeFunction* func =
		new NodeFunction(new list<identifier>(),
			new NodeBinaryAss(
				new NodeVariable(local_id),
				new NodeValue(new ValueInt(10))
			)
		);

	CONTEXT.addFunction(func_id, func);

	NodeFunctionCall func_call(func_id, NULL);
	func_call.execute();



	/*
	function freturn()
	{
		return 5;
	}
	*/
	NodeFunction* freturn =
		new NodeFunction(new list<identifier>(),
			new NodeUnaryReturn(
				new NodeValue(new ValueInt(5))
			)
		);

	CONTEXT.addFunction(freturn_id, freturn);

	NodeFunctionCall freturn_call(freturn_id, NULL);
	str = freturn_call.execute()->toString();
	verify(str == "5");


	/*
	function func()
	{
		local = 10;
		return local;
	}
	*/
	NodeBlock* body = new NodeBlock();

	body->pushCommandToBack(
		new NodeBinaryAss(
			new NodeVariable(local_id),
			new NodeValue(new ValueInt(10))
		)
	);
	body->pushCommandToBack(
		new NodeUnaryReturn(
			new NodeVariable(local_id)
		)
	);

	NodeFunction* freturn_local = new NodeFunction(new list<identifier>(), body);
	CONTEXT.addFunction(freturn_local_id, freturn_local);

	NodeFunctionCall freturn_local_call(freturn_local_id, NULL);
	str = freturn_local_call.execute()->toString();
	verify(str == "10");


	/*
	function factorial(number)
	{
		if(number < 2)
			return 1;
		else
			return number * factorial(number - 1);
	}
	*/
/*
	// TODO: Implement NodeJumpReturn
	list<identifier>* param_names = new list<identifier>();
	param_names->push_back(number_id);

	NodeBlock* params = new NodeBlock();
	params->pushCommandToBack(
		new NodeBinarySub(
			new NodeVariable(number_id),
			new NodeValue(new ValueInt(1))
		)
	);

	NodeFunction* factorial =
		new NodeFunction(param_names,
			new NodeCondition(
				new NodeBinaryLt(
					new NodeVariable(number_id),
					new NodeValue(new ValueInt(2))
				),
				new NodeUnaryReturn(
					new NodeValue(new ValueInt(1))
				),
				new NodeUnaryReturn(
					new NodeBinaryMult(
						new NodeVariable(number_id),
						new NodeFunctionCall(
							factorial_id,
							params
						)
					)
				)
			)
		);

	CONTEXT.addFunction(factorial_id, func);

	NodeBlock* init_param = new NodeBlock();
	params->pushCommandToBack(
		new NodeValue(new ValueInt(4))
	);

	NodeFunctionCall factorial_call(factorial_id, init_param);
	str = factorial_call.execute()->toString();
	cout << str << endl;
	verify(str == "24");// TODO:
*/

	CONTEXT.clear();
	return testResult(__FUNCTION__, result);
}


/*
// Template

/////////////////////////////////////////////////////////////////////////////
////

bool Tests::test(void)
{
	bool result = true;

	// Add code here
	verify(true);

	return testResult(__FUNCTION__, result);
}
*/
