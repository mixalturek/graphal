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

class Tests
{
public:
	Tests();
	virtual ~Tests();

	void run(void);

private:
	bool testResult(const string& testName, bool result);

#ifdef CHECK_MEMORY_LEAKS
	bool testMemoryLeaks(void);
#endif // CHECK_MEMORY_LEAKS

	bool testDoubleDispatching(void);
	bool testVariableStruct(void);
	bool testGraphs(void);
	bool testLexanTerminalSymbols(void);

	// Template
	// bool test(void);

};

#endif /* TESTS_HPP */
