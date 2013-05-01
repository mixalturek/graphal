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


#ifndef BASEOBJECT_HPP
#define BASEOBJECT_HPP

#include "general.h"

#ifdef CHECK_MEMORY_LEAKS
#include <set>
#endif // CHECK_MEMORY_LEAKS

class BaseObject
{
public:
	BaseObject(void);
	virtual ~BaseObject(void);

	virtual void dump(ostream& os, uint indent) const = 0;
	static void dumpIndent(ostream& os, uint indent);

#ifdef CHECK_MEMORY_LEAKS
private:
	static set<BaseObject*> m_allocated_objects;

public:
	static uint getNumberOfLeaks(void) { return m_allocated_objects.size(); }
	static void printMemoryLeaks(uint number_of_static_objects);
#endif // CHECK_MEMORY_LEAKS
};

#endif /* BASEOBJECT_HPP */
