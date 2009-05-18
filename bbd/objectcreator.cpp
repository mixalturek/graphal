/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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


#include <cassert>
#include "objectcreator.hpp"
#include "objectfactory.hpp"
#include "logger.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ObjectCreator::ObjectCreator(void)
	: m_factory(NULL),
	m_context(NULL)
{

}

ObjectCreator::~ObjectCreator(void)
{
	destroy();
}


/////////////////////////////////////////////////////////////////////////////
////

void ObjectCreator::init(ObjectFactory* factory)
{
	assert(factory != NULL);
	m_factory = factory;

	m_logger = m_factory->newLogger();
	m_context = m_factory->newContext();
}

void ObjectCreator::destroy(void)
{
	if(m_factory != NULL)
	{
		delete m_factory;
		m_factory = NULL;
	}

	if(m_logger != NULL)
	{
		delete m_logger;
		m_logger = NULL;
	}

	if(m_context != NULL)
	{
		delete m_context;
		m_context = NULL;
	}
}

