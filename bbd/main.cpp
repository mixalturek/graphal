/*
 *      main.cpp
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

#include <typeinfo>
#include <stdexcept>
#include "general.hpp"
#include "logger.hpp"
#include "graph.hpp"
#include "valueint.hpp"
#include "valuebool.hpp"
#include "valuefloat.hpp"
#include "valuestruct.hpp"
#include "valuestring.hpp"
#include "graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"


void test(void)
{
/*	// Double dispatching
	PTR_Value varleft(new ValueInt(5));
	PTR_Value varright(new ValueFloat(3.4f));
	PTR_Value varsub(new ValueFloat(2.0f));

	cout << varleft->add(*varright)->div(*varsub)->toString() << endl; // 4.2
*/

/*	// Structs
	ValueStruct vs;
	vs.setValue("testi", new ValueInt(5));
	vs.setValue("testb", new ValueBool(true));
	vs.setValue("tests", new ValueString("bagr"));

	cout << vs.getValue("testi")->toString() << endl;
	cout << vs.getValue("asd")->toString() << endl;
	cout << vs.toString() << endl;
*/

/*	// Memory leaks

	Value* i = new ValueInt(5);
	Value* j = new ValueBool(true);
	Value* k = new ValueString("bagr");
	// delete j;
	delete i;
	// delete k;
*/

/*	// Graphs
	Graph g;

	cout << "------------------ new vertices" << endl;
	Vertex* v1 = g.generateVertex();
	cout << "v1->getID(): " << v1->getID() << endl;
	Vertex* v2 = g.generateVertex();
	cout << "v2->getID(): " << v2->getID() << endl;
	Vertex* v3 = g.generateVertex();
	cout << "v3->getID(): " << v3->getID() << endl;
	Vertex* v4 = g.generateVertex();
	cout << "v4->getID(): " << v4->getID() << endl;

	cout << "Vertices: " << g.getNumVertices() << " = 4" << endl;
	cout << "Edges: " << g.getNumEdges() << " = 0" << endl;

	cout << "------------------ new edges" << endl;
	Edge* e1 = g.generateEdge(v1, v2);
	cout << "e1->getID(): " << e1->getID() << endl;
	Edge* e2 = g.generateEdge(v2, v3);
	cout << "e2->getID(): " << e2->getID() << endl;
	Edge* e3 = g.generateEdge(v3, v4);
	cout << "e3->getID(): " << e3->getID() << endl;

	cout << "Vertices: " << g.getNumVertices() << " = 4" << endl;
	cout << "Edges: " << g.getNumEdges() << " = 3" << endl;
	cout << "Degree: " << v1->getDegree() << " = 1" << endl;
	cout << "Degree: " << v2->getDegree() << " = 2" << endl;
	cout << "Degree: " << v3->getDegree() << " = 2" << endl;
	cout << "Degree: " << v4->getDegree() << " = 1" << endl;

	cout << "------------------ delete edge" << endl;
	g.deleteEdge(e1); e1 = NULL;
	cout << "Vertices: " << g.getNumVertices() << " = 4" << endl;
	cout << "Edges: " << g.getNumEdges() << " = 2" << endl;
	cout << "Degree: " << v1->getDegree() << " = 0" << endl;
	cout << "Degree: " << v2->getDegree() << " = 1" << endl;
	cout << "Degree: " << v3->getDegree() << " = 2" << endl;
	cout << "Degree: " << v4->getDegree() << " = 1" << endl;

	cout << "------------------ delete vertex" << endl;
	g.deleteVertex(v2);	v2 = NULL;
	cout << "Vertices: " << g.getNumVertices() << " = 3" << endl;
	cout << "Edges: " << g.getNumEdges() << " = 1" << endl;
	cout << "Degree: " << v1->getDegree() << " = 0" << endl;
	// cout << "Degree: " << v2->getDegree() << " = 1" << endl;
	cout << "Degree: " << v3->getDegree() << " = 1" << endl;
	cout << "Degree: " << v4->getDegree() << " = 1" << endl;
*/
}


int main(int argc, char** argv)
{
	try
	{
		test();

#ifdef CHECK_MEMORY_LEAKS
		BaseObject::printMemoryLeaks();
#endif // CHECK_MEMORY_LEAKS

		cout << _("Total number of created objects: ") << BaseObject::getMaxID() << endl;
	}
	catch(runtime_error& ex)
	{
		ERROR << ex.what() << endl;
		return 1;
	}
	catch(exception& ex)
	{
		ERROR << ex.what() << endl;
		return 1;
	}
	catch(...)
	{
		ERROR << _("Unknown exception catched!") << endl;
		return 1;
	}

	return 0;
}
