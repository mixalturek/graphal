/*
 *      init_static_objects.cpp
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


/****************************************************************************
 * ALL STATIC OBJECTS IN THE APPLICATION                                    *
 * HAVE TO BE INITIALIZED IN THIS FILE                                      *
 * WITH A PROPER ORDER!!!                                                   *
 ****************************************************************************/


#include "general.hpp"
#include "baseobject.hpp"
#include "valuestruct.hpp"
#include "logger.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
//// BaseObject

#ifdef CHECK_MEMORY_LEAKS
set<BaseObject*> BaseObject::m_allocated_objects = set<BaseObject*>();
#endif // CHECK_MEMORY_LEAKS


/////////////////////////////////////////////////////////////////////////////
//// Logger

Logger Logger::instance;


/////////////////////////////////////////////////////////////////////////////
//// Context

Context Context::instance;


/////////////////////////////////////////////////////////////////////////////
//// ValueStruct

ValueNull ValueStruct::m_notfound;


/////////////////////////////////////////////////////////////////////////////
////
