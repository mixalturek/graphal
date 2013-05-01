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


#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__

/////////////////////////////////////////////////////////////////////////////
//// Compiler switches

#ifndef NDEBUG
#define DEBUG
#ifndef QTGUI
#define CHECK_MEMORY_LEAKS
#define DISABLE_THREAD_SYNCHRONIZATION
#endif // QTGUI
#endif // NDEBUG


/////////////////////////////////////////////////////////////////////////////
//// Macros

// gettext
#define _(str) (str)

// throw alias
/*
#define THROW(obj)                                         \
{                                                          \
	cout << "[exception] " << __FILE__ << ":" << __LINE__  \
		<< " function " << __FUNCTION__ << "()" << endl;   \
	throw (obj);                                           \
}
*/
#define THROW(obj) { throw (obj); }

// Trace macro
#define TRACE(arg) cout << #arg << endl; arg
#define D(arg) cout << #arg " = [" << arg << "]" << endl;


/////////////////////////////////////////////////////////////////////////////
//// Includes

#include <iostream>
using namespace std;


/////////////////////////////////////////////////////////////////////////////
//// Data types

typedef unsigned int uint;
typedef unsigned int identifier;// Variable and function name ID


/////////////////////////////////////////////////////////////////////////////
//// Functions

inline string char2string(char ch)
{
	char tmp[2] = { ch, '\0' };
	return string(tmp);
}


/////////////////////////////////////////////////////////////////////////////
////

class DeleteObject
{
public:
	template <typename TYPE> void operator()(const TYPE* ptr) const
	{
		delete ptr;
		ptr = NULL;
	}
};

#endif // __GENERAL_HPP__
