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
#include "general.hpp"
#include "graph.hpp"
#include "valueint.hpp"
#include "valuebool.hpp"
#include "valuestruct.hpp"
#include "valuestring.hpp"


void test(void)
{
/*	// Double dispatching
	PTR_Value varleft(new ValueInt(5));
	PTR_Value varright(new ValueInt(3));

	PTR_Value result = varleft->add(*varright);
	result->printVal();
	cout << endl;
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

	// Memory leaks
	/*
	Value* i = new ValueInt(5);
	Value* j = new ValueBool(true);
	Value* k = new ValueString("bagr");
	// delete j;
	delete i;
	// delete k;
	*/
}


int main(int argc, char** argv)
{
	test();

#ifdef CHECK_MEMORY_LEAKS
	BaseObject::printMemoryLeaks();
#endif // CHECK_MEMORY_LEAKS

	cout << "Total number of created objects: " << BaseObject::getMaxID() << endl;
	return 0;
}
