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
