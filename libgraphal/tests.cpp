/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "tests.h"
#include "logger.h"
#include "valueint.h"
#include "valuefloat.h"
#include "valuebool.h"
#include "valuestring.h"
#include "valuestruct.h"
#include "valuereference.h"
#include "valueidentifier.h"
#include "valuegraph.h"
#include "valuevertex.h"
#include "valueedge.h"
#include "lexan.h"
#include "context.h"
#include "nodeunarysub.h"
#include "nodeunarynot.h"
#include "nodebinaryadd.h"
#include "nodebinarysub.h"
#include "nodeblock.h"
#include "nodecondition.h"
#include "countptr.h"
#include "nodeemptycommand.h"
#include "nodefunctionscript.h"
#include "nodefunctioncall.h"
#include "nodebinaryass.h"
#include "nodevalue.h"
#include "nodebinarylt.h"
#include "nodeunaryreturn.h"
#include "nodebinarymult.h"
#include "valuearray.h"
#include "valueset.h"


/////////////////////////////////////////////////////////////////////////////
////

// Verify macro, like assert but without exiting
#define verify(expr)                                          \
{                                                             \
	bool cur_result = (expr);                                 \
	result = result && cur_result;                            \
	if(!cur_result)                                           \
	{                                                         \
		stringstream ss;                                      \
		ss << __FILE__ << ":" << __LINE__ << "   " << #expr;  \
		ERR(ss.str());                                        \
	}                                                         \
}

/////////////////////////////////////////////////////////////////////////////
////

Tests::Tests(void)
{

}


Tests::~Tests(void)
{

}

/////////////////////////////////////////////////////////////////////////////
////

void Tests::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Tests />" << endl;
}

ostream& operator<<(ostream& os, const Tests& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testResult(const string& testName, bool result)
{
	if(result)
		INFO(_("[ OK ]     ") + testName);
	else
		ERR(_("[ FAILED ] ") + testName);

	return result;
}

/////////////////////////////////////////////////////////////////////////////
////

void Tests::run(void)
{
	CodePosition tmp(STR2ID("tests"), 0);
	CONTEXT.pushLocal(STR2ID("tests"), &tmp);
	CONTEXT.setPosition(&tmp);

	uint failed = 0;
#ifdef CHECK_MEMORY_LEAKS
	failed += !testMemoryLeaks();
#endif // CHECK_MEMORY_LEAKS
	failed += !testDoubleDispatching();
	failed += !testValueStruct();
	failed += !testValueString();
	failed += !testValueReference();
	failed += !testValueIdentifier();
	failed += !testValueArray();
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
	failed += !testValueArrayIterator();
	failed += !testValueSet();
	failed += !testValueSetOperations();
	failed += !testValueSetRemove();

	// Template
	// failed += !test();

	stringstream ss;
	ss << _("Number of failed tests: ") << failed;
	INFO(ss.str());
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
	Value* j = new ValueFloat(3.14);
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

	CountPtr<Value> a(new ValueInt(5));
	CountPtr<Value> b(new ValueFloat(3.4f));
	CountPtr<Value> c(new ValueFloat(2.0f));

	verify(a->add(*b)->div(*c)->toString() == "4.2");// (5 + 3.4) / 2
	verify(a->mult(*c)->sub(*b)->toString() == "6.6");// (5 * 2) - 3.4

	return testResult(__FUNCTION__, result);
}


bool Tests::testValueStruct(void)
{
	bool result = true;

	ValueStruct vs;
	vs.setItem(STR2ID("int_42"), CountPtr<Value>(new ValueInt(42)));
	vs.setItem(STR2ID("bool_true"), VALUEBOOL_TRUE);
	vs.setItem(STR2ID("string_bagr"), CountPtr<Value>(new ValueString("bagr")));

	verify(vs.getItem(STR2ID("int_42"))->toString() == "42");
	verify(vs.getItem(STR2ID("bool_true"))->toString() == "true");
	verify(vs.getItem(STR2ID("string_bagr"))->toString() == "bagr");
	verify(vs.getItem(STR2ID("undefined"))->toString() == "NULL");

	return testResult(__FUNCTION__, result);
}


bool Tests::testValueString(void)
{
	bool result = true;

	CountPtr<Value> var_left(new ValueString("left "));
	CountPtr<Value> var_str(new ValueString("bagr"));
	CountPtr<Value> var_bool(VALUEBOOL_TRUE);
	CountPtr<Value> var_int(new ValueInt(3));
	CountPtr<Value> var_float(new ValueFloat(5.5f));

	verify(var_left->add(*var_str)->toString() == "left bagr");
	verify(var_left->add(*var_bool)->toString() == "left true");
	verify(var_left->add(*var_int)->toString() == "left 3");
	verify(var_left->add(*var_float)->toString() == "left 5.5");

	return testResult(__FUNCTION__, result);
}


bool Tests::testValueReference(void)
{
	bool result = true;

	CountPtr<Value> valref(CountPtr<Value>(new ValueReference(CountPtr<Value>(new ValueInt(5)))));
	CountPtr<Value> valref2(CountPtr<Value>(new ValueReference(CountPtr<Value>(new ValueFloat(5.5)))));
	CountPtr<Value> val(new ValueInt(3));

	verify(valref->add(*val)->toString() == "8");
	verify(valref->sub(*val)->toString() == "2");
	verify(val->add(*valref)->toString() == "8");
	verify(val->sub(*valref)->toString() == "-2");
	verify(valref->add(*valref2)->toString() == "10.5");
	verify(valref->sub(*valref2)->toString() == "-0.5");

	ValueReference* ref = dynamic_cast<ValueReference*>(&(*valref));
	assert(ref != NULL);
	ref->assign(CountPtr<Value>(new ValueFloat(3.14)));

	verify(valref->add(*val)->toString() == "6.14");
	verify(valref->sub(*val)->toString() == "0.14");
	verify(val->add(*valref)->toString() == "6.14");
	verify(val->sub(*valref)->toString() == "-0.14");
	verify(valref->add(*valref2)->toString() == "8.64");
	verify(valref->sub(*valref2)->toString() == "-2.36");

	return testResult(__FUNCTION__, result);
}


bool Tests::testValueIdentifier(void)
{
	bool result = true;

	CountPtr<Value> valref(CountPtr<Value>(new ValueIdentifier(STR2ID("var"))));
	CountPtr<Value> valref2(CountPtr<Value>(new ValueReference(CountPtr<Value>(new ValueFloat(5.5)))));
	CountPtr<Value> val(new ValueInt(3));

	valref->assign(CountPtr<Value>(new ValueInt(5)));

	verify(valref->add(*val)->toString() == "8");
	verify(valref->sub(*val)->toString() == "2");
	verify(val->add(*valref)->toString() == "8");
	verify(val->sub(*valref)->toString() == "-2");
	verify(valref->add(*valref2)->toString() == "10.5");
	verify(valref->sub(*valref2)->toString() == "-0.5");

	valref->assign(CountPtr<Value>(new ValueFloat(3.14)));

	verify(valref->add(*val)->toString() == "6.14");
	verify(valref->sub(*val)->toString() == "0.14");
	verify(val->add(*valref)->toString() == "6.14");
	verify(val->sub(*valref)->toString() == "-0.14");
	verify(valref->add(*valref2)->toString() == "8.64");
	verify(valref->sub(*valref2)->toString() == "-2.36");

	return testResult(__FUNCTION__, result);
}


bool Tests::testValueArray(void)
{
	bool result = true;

	/*
	// TODO: ??? gcc bug ???
	Tests::testValueArray()

	right.index(*this) in ValueArray::index(const Value& right) calls
	ValueInt::index(const Value& right)
	ValueFloat::index(const Value& right)
	etc.

	instead of
	ValueInt::index(const ValueArray& left)
	ValueFloat::index(const ValueArray& left)
	etc.

	There is no problem with indexing of ValueString, why? It is the same!

	Temporary fixed in Value::index() by dynamic_cast
	*/
	ValueArray* a = new ValueArray();
	a->resize(1);
	a->setItem(0, CountPtr<Value>(new ValueString("bagr")));

	//CountPtr<Value> array(new ValueString("abc"));
	CountPtr<Value> str(new ValueString("abc"));
	CountPtr<Value> array(a);
	CountPtr<Value> ind(new ValueInt(0));

	//str->index(*ind)->dump(cout, 0);
	//array->index(*ind)->dump(cout, 0);

	verify(str->index(*ind)->toString() != "NULL");
	verify(array->index(*ind)->toString() != "NULL");


	/////////////////


	identifier varid = STR2ID("brm");
	CountPtr<Value> ident(new ValueIdentifier(varid));

	a = new ValueArray();
	a->resize(1);
	ident->assign(CountPtr<Value>(a));
	// ident->dump(cout, 0);

	CountPtr<Value> index(new ValueInt(0));
	CountPtr<Value> val(new ValueInt(3));

	CountPtr<Value> indexval = ident->index(*index);
	// indexval->dump(cout, 0);

	verify(indexval->toString() == "NULL");
	verify(ident->toString() == "#Array");

	indexval->assign(val);
	// ident->dump(cout, 0);
	verify(indexval->toString() == "3");
	verify(ident->toString() == "#Array");


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

	CountPtr<Value> v1 = g.generateVertex();
	CountPtr<Value> v2 = g.generateVertex();
	CountPtr<Value> v3 = g.generateVertex();
	CountPtr<Value> v4 = g.generateVertex();

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 0);

	CountPtr<Value> e1 = g.generateEdge(v1, v2);
	CountPtr<Value> e2 = g.generateEdge(v2, v3);
	CountPtr<Value> e3 = g.generateEdge(v3, v4);


	verify(e1->toValueEdge()->getBeginVertex() == v1);
	verify(e1->toValueEdge()->getEndVertex() == v2);
	verify(e2->toValueEdge()->getBeginVertex() == v2);
	verify(e2->toValueEdge()->getEndVertex() == v3);
	verify(e3->toValueEdge()->getBeginVertex() == v3);
	verify(e3->toValueEdge()->getEndVertex() == v4);

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 3);
	verify(v1->toValueVertex()->getDegree() == 1);
	verify(v2->toValueVertex()->getDegree() == 2);
	verify(v3->toValueVertex()->getDegree() == 2);
	verify(v4->toValueVertex()->getDegree() == 1);

	g.deleteEdge(e1);

	verify(g.getNumVertices() == 4);
	verify(g.getNumEdges() == 2);
	verify(v1->toValueVertex()->getDegree() == 0);
	verify(v2->toValueVertex()->getDegree() == 1);
	verify(v3->toValueVertex()->getDegree() == 2);
	verify(v4->toValueVertex()->getDegree() == 1);

	g.deleteVertex(v2);

	verify(g.getNumVertices() == 3);
	verify(g.getNumEdges() == 1);
	verify(v1->toValueVertex()->getDegree() == 0);
	verify(v2->toValueVertex()->getDegree() == 0); // deleted
	verify(v3->toValueVertex()->getDegree() == 1);
	verify(v4->toValueVertex()->getDegree() == 1);

	return testResult(__FUNCTION__, result);
}



bool Tests::testGraphSet(void)
{
	bool result = true;

	// v1 ---- v2 ---- v3 ---- v4
	//     e1      e2      e3
	ValueGraph g(false);

	CountPtr<Value> v1 = g.generateVertex();
	CountPtr<Value> v2 = g.generateVertex();
	CountPtr<Value> v3 = g.generateVertex();
	CountPtr<Value> v4 = g.generateVertex();
	CountPtr<Value> e1 = g.generateEdge(v1, v2);
	CountPtr<Value> e2 = g.generateEdge(v2, v3);
	CountPtr<Value> e3 = g.generateEdge(v3, v4);


	CountPtr<Value> vvs(v1->toValueVertex()->getNeighbors());
	verify(vvs->toValueSet()->getSize() == 1);
	verify(!vvs->toValueSet()->contains(v1));
	verify(vvs->toValueSet()->contains(v2));
	verify(!vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));

	vvs = v2->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 2);
	verify(vvs->toValueSet()->contains(v1));
	verify(!vvs->toValueSet()->contains(v2));
	verify(vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));


	// v1 ----> v2 ----> v3 ----> v4
	//     e1       e2       e3
	g.setDirected(true);

	vvs = v1->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 1);
	verify(!vvs->toValueSet()->contains(v1));
	verify(vvs->toValueSet()->contains(v2));
	verify(!vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));

	vvs = v2->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 1);
	verify(!vvs->toValueSet()->contains(v1));
	verify(!vvs->toValueSet()->contains(v2));
	verify(vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));


	g.setDirected(false);


	ValueSet ves;
	ves.insert(e1);
	ves.insert(e2);
	verify(ves.getSize() == 2);
	verify(ves.contains(e1));
	verify(ves.contains(e2));

	ves.remove(e1);
	verify(ves.getSize() == 1);
	verify(!ves.contains(e1));
	verify(ves.contains(e2));

	ves.remove(e2);
	verify(ves.getSize() == 0);
	verify(!ves.contains(e1));
	verify(!ves.contains(e2));

	ves.insert(e3);
	verify(ves.getSize() == 1);
	ves.remove(e3);
	verify(ves.getSize() == 0);

	return testResult(__FUNCTION__, result);
}


bool Tests::testGraphInvertEdgesOrientation(void)
{
	bool result = true;

	// v1 ----> v2 ----> v3 ----> v4
	//     e1       e2       e3
	ValueGraph g(true);

	CountPtr<Value> v1 = g.generateVertex();
	CountPtr<Value> v2 = g.generateVertex();
	CountPtr<Value> v3 = g.generateVertex();
	CountPtr<Value> v4 = g.generateVertex();
	CountPtr<Value> e1 = g.generateEdge(v1, v2);
	CountPtr<Value> e2 = g.generateEdge(v2, v3);
	CountPtr<Value> e3 = g.generateEdge(v3, v4);

	// v1 <---- v2 <---- v3 <---- v4
	//      e1       e2       e3
	g.invertEdgesDirection();

	CountPtr<Value> vvs(v1->toValueVertex()->getNeighbors());

	verify(vvs->toValueSet()->getSize() == 0);
	verify(!vvs->toValueSet()->contains(v2));
	verify(!vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));

	vvs = v2->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 1);
	verify(vvs->toValueSet()->contains(v1));
	verify(!vvs->toValueSet()->contains(v3));
	verify(!vvs->toValueSet()->contains(v4));

	vvs = v3->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 1);
	verify(!vvs->toValueSet()->contains(v1));
	verify(vvs->toValueSet()->contains(v2));
	verify(!vvs->toValueSet()->contains(v4));

	vvs = v4->toValueVertex()->getNeighbors();
	verify(vvs->toValueSet()->getSize() == 1);
	verify(!vvs->toValueSet()->contains(v1));
	verify(!vvs->toValueSet()->contains(v2));
	verify(vvs->toValueSet()->contains(v3));

	verify(e1->toValueEdge()->getBeginVertex() == v2);
	verify(e1->toValueEdge()->getEndVertex() == v1);

	verify(e2->toValueEdge()->getBeginVertex() == v3);
	verify(e2->toValueEdge()->getEndVertex() == v2);

	verify(e3->toValueEdge()->getBeginVertex() == v4);
	verify(e3->toValueEdge()->getEndVertex() == v3);

	return testResult(__FUNCTION__, result);
}

/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testLexanTerminalSymbols(void)
{
	bool result = true;

	Lexan lexan(
		"function return if else while for foreach break continue { } ( ) [ ] "
		", ; . ! = += -= *= /= %= || && < > <= >= == != + - * / % ++ -- "
		"null true false ? :");

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
	tok = lexan.nextToken(); verify(tok == LEX_ADD_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_SUB_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_MUL_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_DIV_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_MOD_ASSIGN);
	tok = lexan.nextToken(); verify(tok == LEX_OR_OP);
	tok = lexan.nextToken(); verify(tok == LEX_AND_OP);
	tok = lexan.nextToken(); verify(tok == LEX_OP_LESS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_GREATER);
	tok = lexan.nextToken(); verify(tok == LEX_LE_OP);
	tok = lexan.nextToken(); verify(tok == LEX_GE_OP);
	tok = lexan.nextToken(); verify(tok == LEX_EQ_OP);
	tok = lexan.nextToken(); verify(tok == LEX_NE_OP);
	tok = lexan.nextToken(); verify(tok == LEX_OP_PLUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MINUS);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT);
	tok = lexan.nextToken(); verify(tok == LEX_OP_DIV);
	tok = lexan.nextToken(); verify(tok == LEX_OP_MOD);
	tok = lexan.nextToken(); verify(tok == LEX_INC_OP);
	tok = lexan.nextToken(); verify(tok == LEX_DEC_OP);
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
	Lexan lexan("2 26 999999999 2147483647 -2147483647 0 05 006 0362457 0x20 0x20e9 0xff 0x36a5d 25,356");

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
	Lexan lexan(". .= .1 .12 .12e6 0.12e6 0.0 .0 0. 25.3688 12e-1 12e+1 25e7");

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
		"  \"begin-\\112-end\"  \"begin-\\377-end\"  ");

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
	Lexan lexan("  /**/   /*  */   /***/   /* blem */   /***sf asf*sad/fasd*/  // :-) ");


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
		"/* EOF */");

	tok = lexan.nextToken(); verify(tok == LEX_FUNCTION);
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
	str = lexan.getString(); verify(str == "factorial");
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_RPA);
	tok = lexan.nextToken(); verify(tok == LEX_LVA);
	tok = lexan.nextToken(); verify(tok == LEX_IF);
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
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
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
	str = lexan.getString(); verify(str == "number");
	tok = lexan.nextToken(); verify(tok == LEX_OP_MULT);
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
	str = lexan.getString(); verify(str == "factorial");
	tok = lexan.nextToken(); verify(tok == LEX_LPA);
	tok = lexan.nextToken(); verify(tok == LEX_IDENTIFIER);
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

	NodeUnaryNot unot(new NodeValue(VALUEBOOL_TRUE));
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

	NodeCondition cond(new NodeValue(VALUEBOOL_TRUE), bl, NULL);

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testNodeVariable(void)
{
	bool result = true;

	string str;

	ValueIdentifier* var0 = new ValueIdentifier(STR2ID("var0"));
	ValueIdentifier* var1 = new ValueIdentifier(STR2ID("var1"));

	var0->assign(CountPtr<Value>(new ValueFloat(3.14f)));
	var1->assign(CountPtr<Value>(new ValueInt(15)));

	NodeBinaryAdd add(new NodeValue(new ValueInt(10)), new NodeValue(var0));
	str = add.execute()->toString();
	verify(str == "13.14");

	NodeBinarySub sub(new NodeValue(new ValueInt(20)), new NodeValue(var1));
	str = sub.execute()->toString();
	verify(str == "5");

	var1->assign(CountPtr<Value>(new ValueFloat(3.5f)));

	str = sub.execute()->toString();
	verify(str == "16.5");

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

	const uint func_id = STR2ID("func");
	const uint local_id = STR2ID("local");
	const uint factorial_id = STR2ID("factorial");
	const uint number_id = STR2ID("number");
	const uint freturn_id = STR2ID("freturn");
	const uint freturn_local_id = STR2ID("freturn_local");

	string str;

	/*
	function func()
	{
		local = 10;
	}
	*/
	NodeFunction* func =
		new NodeFunctionScript(func_id, new list<identifier>(),
			new NodeBinaryAss(
				new NodeValue(new ValueIdentifier(local_id)),
				new NodeValue(new ValueInt(10))
			),
			new CodePosition(STR2ID("unittest"), 0)
		);

	CONTEXT.addFunction(func);

	NodeFunctionCall func_call(func_id, NULL, new CodePosition(STR2ID("unittest"), 0));
	func_call.execute();



	/*
	function freturn()
	{
		return 5;
	}
	*/
	NodeFunction* freturn =
		new NodeFunctionScript(freturn_id, new list<identifier>(),
			new NodeUnaryReturn(
				new NodeValue(new ValueInt(5))
			),
			new CodePosition(STR2ID("unittest"), 0)
		);

	CONTEXT.addFunction(freturn);

	NodeFunctionCall freturn_call(freturn_id, NULL, new CodePosition(STR2ID("unittest"), 0));
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
			new NodeValue(new ValueIdentifier(local_id)),
			new NodeValue(new ValueInt(10))
		)
	);
	body->pushCommandToBack(
		new NodeUnaryReturn(
			new NodeValue(new ValueIdentifier(local_id))
		)
	);

	NodeFunction* freturn_local = new NodeFunctionScript(freturn_local_id,
		new list<identifier>(), body, new CodePosition(STR2ID("unittest"), 0));
	CONTEXT.addFunction(freturn_local);

	NodeFunctionCall freturn_local_call(freturn_local_id, NULL, new CodePosition(STR2ID("unittest"), 0));
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
	list<identifier>* param_names = new list<identifier>();
	param_names->push_back(number_id);

	NodeBlock* params = new NodeBlock();
	params->pushCommandToBack(
		new NodeBinarySub(
			new NodeValue(new ValueIdentifier(number_id)),
			new NodeValue(new ValueInt(1))
		)
	);

	NodeFunction* factorial =
		new NodeFunctionScript(factorial_id, param_names,
			new NodeCondition(
				new NodeBinaryLt(
					new NodeValue(new ValueIdentifier(number_id)),
					new NodeValue(new ValueInt(2))
				),
				new NodeUnaryReturn(
					new NodeValue(new ValueInt(1))
				),
				new NodeUnaryReturn(
					new NodeBinaryMult(
						new NodeValue(new ValueIdentifier(number_id)),
						new NodeFunctionCall(
							factorial_id,
							params,
							new CodePosition(STR2ID("unittest"), 0)
						)
					)
				)
			),
			new CodePosition(STR2ID("unittest"), 0)
		);

	CONTEXT.addFunction(factorial);

	NodeFunctionCall factorial_call(factorial_id,
		new NodeBlock(new NodeValue(new ValueInt(4))),
		new CodePosition(STR2ID("unittest"), 0));

	str = factorial_call.execute()->toString();
	verify(str == "24");

	CONTEXT.clear();
	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testValueArrayIterator(void)
{
	bool result = true;

	CountPtr<Value> array(new ValueArray(3));

	array->toValueArray()->setItem(0, CountPtr<Value>(new ValueInt(9)));
	array->toValueArray()->setItem(1, CountPtr<Value>(new ValueString("bagr")));
	array->toValueArray()->setItem(2, CountPtr<Value>(new ValueFloat(3.14f)));

	CountPtr<Value> iterator(array->iterator());

	// Check number of elements
	verify(array->toValueArray()->getSize() == 3);
	verify(iterator->toValueArray()->getSize() == 3);

	// Change value in array by iterator
	iterator->toValueArray()->setItem(0, CountPtr<Value>(new ValueFloat(5.5f)));
	verify(array->toValueArray()->getItem(0)->toString() == "5.5");

	// Change all values in array by iterator + check that all items were processed
	int num = 0;
	iterator->resetIterator();
	while(iterator->hasNext()->toBool())
			iterator->next()->toValueReference()->assign(CountPtr<Value>(new ValueInt(num++)));

	verify(num == 3);

	verify(array->toValueArray()->getItem(0)->toString() == "0");
	verify(array->toValueArray()->getItem(1)->toString() == "1");
	verify(array->toValueArray()->getItem(2)->toString() == "2");

	// Reallocate the array and verify that the iterator is still working
	array->toValueArray()->resize(5);
	verify(array->toValueArray()->getSize() == 5);
	verify(iterator->toValueArray()->getSize() == 3);

	iterator->resetIterator();

	verify(iterator->hasNext()->toBool());
	CountPtr<Value> tmp(iterator->next());
	verify(tmp->toString() == "0");

	verify(iterator->hasNext()->toBool());
	tmp = iterator->next();
	verify(tmp->toString() == "1");

	verify(iterator->hasNext()->toBool());
	tmp = iterator->next();
	verify(tmp->toString() == "2");

	verify(!iterator->hasNext()->toBool());

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testValueSet(void)
{
	bool result = true;

	ValueSet set;
	verify(set.getSize() == 0);

	CountPtr<Value> int_val(new ValueInt(5));
	verify(!set.contains(int_val));
	set.insert(int_val);
	verify(set.getSize() == 1);
	verify(set.contains(int_val));

	CountPtr<Value> float_val(new ValueFloat(3.14));
	verify(!set.contains(float_val));
	set.insert(float_val);
	verify(set.getSize() == 2);
	verify(set.contains(int_val));
	verify(set.contains(float_val));

	set.insert(float_val);
	verify(set.getSize() == 2);
	verify(set.contains(int_val));
	verify(set.contains(float_val));

	CountPtr<Value> int_val2(new ValueInt(5));
	set.insert(int_val2);
	verify(set.getSize() == 2);
	verify(set.contains(int_val));
	verify(set.contains(int_val2));
	verify(set.contains(float_val));

	set.remove(int_val);
	verify(set.getSize() == 1);
	verify(!set.contains(int_val));
	verify(!set.contains(int_val2));
	verify(set.contains(float_val));

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testValueSetOperations(void)
{
	bool result = true;

	ValueSet set1;
	ValueSet set2;

	CountPtr<Value> int_val(new ValueInt(5));
	CountPtr<Value> float_val(new ValueFloat(3.14));
	CountPtr<Value> string_val(new ValueString("bagr"));

	set1.insert(int_val);
	set1.insert(float_val);

	set2.insert(int_val);
	set2.insert(string_val);

	CountPtr<Value> union_val = set1.getUnion(set2);
	assert(union_val->toValueSet() != NULL);
	verify(union_val->toValueSet()->getSize() == 3);
	verify(union_val->toValueSet()->contains(int_val));
	verify(union_val->toValueSet()->contains(float_val));
	verify(union_val->toValueSet()->contains(string_val));

	CountPtr<Value> intersection_val = set1.getIntersection(set2);
	assert(intersection_val->toValueSet() != NULL);
	verify(intersection_val->toValueSet()->getSize() == 1);
	verify(intersection_val->toValueSet()->contains(int_val));
	verify(!intersection_val->toValueSet()->contains(float_val));
	verify(!intersection_val->toValueSet()->contains(string_val));

	CountPtr<Value> difference_val = set1.getDifference(set2);
	assert(difference_val->toValueSet() != NULL);
	verify(difference_val->toValueSet()->getSize() == 1);
	verify(!difference_val->toValueSet()->contains(int_val));
	verify(difference_val->toValueSet()->contains(float_val));
	verify(!difference_val->toValueSet()->contains(string_val));

	return testResult(__FUNCTION__, result);
}


/////////////////////////////////////////////////////////////////////////////
////

bool Tests::testValueSetRemove(void)
{
	bool result = true;

	ValueSet set1;
	ValueSet set2;

	CountPtr<Value> int_val(new ValueInt(5));
	CountPtr<Value> float_val(new ValueFloat(3.14));
	CountPtr<Value> string_val(new ValueString("bagr"));

	set1.insert(int_val);
	set1.insert(float_val);
	set2.insert(int_val);
	set2.insert(string_val);
	verify(set1.getSize() == 2);
	verify(set2.getSize() == 2);

	set1.remove(set2);

	verify(set1.getSize() == 1);
	verify(set2.getSize() == 2);

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
