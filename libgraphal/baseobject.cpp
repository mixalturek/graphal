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


#include "baseobject.h"

#ifdef CHECK_MEMORY_LEAKS
#include <typeinfo>
#include "logger.h"
#endif // CHECK_MEMORY_LEAKS


/////////////////////////////////////////////////////////////////////////////
////

BaseObject::BaseObject(void)
{
#ifdef CHECK_MEMORY_LEAKS
	// TODO: GUI doesn't check memory leaks and CLI doesn't use threads
//	ACCESS_MUTEX_LOCKER;
	m_allocated_objects.insert(this);
#endif // CHECK_MEMORY_LEAKS
}

BaseObject::~BaseObject(void)
{
#ifdef CHECK_MEMORY_LEAKS
	// TODO: GUI doesn't check memory leaks and CLI doesn't use threads
//	ACCESS_MUTEX_LOCKER;
	m_allocated_objects.erase(this);
#endif // CHECK_MEMORY_LEAKS
}


/////////////////////////////////////////////////////////////////////////////
////
#ifdef CHECK_MEMORY_LEAKS
void BaseObject::printMemoryLeaks(uint number_of_static_objects)
{
	// TODO: GUI doesn't check memory leaks and CLI doesn't use threads
//	ACCESS_MUTEX_LOCKER;
	uint num_of_leaks = m_allocated_objects.size() - number_of_static_objects;
	stringstream ss;
	ss << "Number of memory leaks: " << num_of_leaks;
	INFO(ss.str());

	if(num_of_leaks == 0)
		return;

	// Display all allocated objects, also including static objects
	set<BaseObject*>::const_iterator it;
	for(it = m_allocated_objects.begin(); it != m_allocated_objects.end(); it++)
	{
		ss.str(string());
		ss << *it << ", " << typeid(**it).name();
		ERR(ss.str());
	}
}
#endif // CHECK_MEMORY_LEAKS


/////////////////////////////////////////////////////////////////////////////
////

void BaseObject::dumpIndent(ostream& os, uint indent)
{
	for(uint i = 0; i < indent; i++)
		os << "    ";
}
