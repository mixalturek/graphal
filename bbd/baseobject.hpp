/*
 *      baseobject.hpp
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


#ifndef BASEOBJECT_HPP
#define BASEOBJECT_HPP

#include "general.hpp"

#ifdef CHECK_MEMORY_LEAKS
#include <set>
#endif // CHECK_MEMORY_LEAKS

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

#ifdef CHECK_MEMORY_LEAKS
private:
	static set<BaseObject*> m_allocated_objects;

public:
	static uint getNumberOfLeaks(void) { return m_allocated_objects.size(); }
	static void printMemoryLeaks(uint number_of_static_objects);
#endif // CHECK_MEMORY_LEAKS
};

#endif /* BASEOBJECT_HPP */
