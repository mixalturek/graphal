/*
 *      tests.hpp
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


#ifndef TESTS_HPP
#define TESTS_HPP

#include "general.hpp"
#include "baseobject.hpp"

class Tests : public BaseObject
{
public:
	Tests();
	virtual ~Tests();

	virtual string toString(void) const { return "Tests"; }

	void run(void);

private:
	bool testResult(const string& testName, bool result);

#ifdef CHECK_MEMORY_LEAKS
	bool testMemoryLeaks(void);
#endif // CHECK_MEMORY_LEAKS

	bool testDoubleDispatching(void);
	bool testValueStruct(void);
	bool testGraph(void);
	bool testGraphSet(void);
	bool testGraphInvertEdgesOrientation(void);
	bool testLexanTerminalSymbols(void);
	bool testLexanInt(void);
	bool testLexanFloat(void);
	bool testLexanString(void);
	bool testLexanComments(void);
	bool testLexanSourceCode(void);
	bool testNodeUnary(void);
	bool testNodeBinary(void);
	bool testNodeBlock(void);
	bool testNodeVariable(void);
	bool testStringTable(void);
	bool testCountPtr(void);

	// Template
	// bool test(void);

};

#endif /* TESTS_HPP */
