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


#ifndef TESTS_HPP
#define TESTS_HPP

#include "general.h"
#include "baseobject.h"

class Tests : public BaseObject
{
public:
	Tests(void);
	virtual ~Tests(void);

	virtual void dump(ostream& os, uint indent) const;

	void run(void);

private:
	bool testResult(const string& testName, bool result);

#ifdef CHECK_MEMORY_LEAKS
	bool testMemoryLeaks(void);
#endif // CHECK_MEMORY_LEAKS

	bool testDoubleDispatching(void);
	bool testValueStruct(void);
	bool testValueString(void);
	bool testValueReference(void);
	bool testValueIdentifier(void);
	bool testValueArray(void);
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
	bool testNodeFunction(void);
	bool testValueArrayIterator(void);
	bool testValueSet(void);
	bool testValueSetOperations(void);
	bool testValueSetRemove(void);

	// Template
	// bool test(void);

};

ostream& operator<<(ostream& os, const Tests& node);

#endif /* TESTS_HPP */
