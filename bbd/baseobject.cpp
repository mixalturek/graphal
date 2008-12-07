/*
 *      baseobject.cpp
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


#include "baseobject.hpp"

#ifdef CHECK_MEMORY_LEAKS
#include <typeinfo>
#include "logger.hpp"
#endif // CHECK_MEMORY_LEAKS


/////////////////////////////////////////////////////////////////////////////
////

BaseObject::BaseObject()
	: m_id(m_max_id++)
{
#ifdef CHECK_MEMORY_LEAKS
	m_allocated_objects.insert(this);
#endif // CHECK_MEMORY_LEAKS
}

BaseObject::~BaseObject()
{
#ifdef CHECK_MEMORY_LEAKS
	m_allocated_objects.erase(this);
#endif // CHECK_MEMORY_LEAKS
}


/////////////////////////////////////////////////////////////////////////////
////
#ifdef CHECK_MEMORY_LEAKS
void BaseObject::printMemoryLeaks(uint number_of_static_objects)
{
	uint num_of_leaks = m_allocated_objects.size() - number_of_static_objects;
	INFO << "Number of memory leaks: " << num_of_leaks << endl;

	if(num_of_leaks == 0)
		return;

	// Display all allocated objects, also including static objects
	// (ie. ValueStruct::m_notfound)
	set<BaseObject*>::const_iterator it;
	for(it = m_allocated_objects.begin(); it != m_allocated_objects.end(); it++)
		ERROR << "\tid = " << (*it)->getID() << ", type = " << typeid(**it).name()
			<< ", tostring = " << (*it)->toString() << ", mem = " << *it << endl;
}
#endif // CHECK_MEMORY_LEAKS
