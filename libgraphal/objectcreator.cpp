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
#include "objectcreator.h"
#include "objectfactory.h"
#include "logger.h"
#include "context.h"
#include "visualizationconnector.h"
#include "mutex.h"


/////////////////////////////////////////////////////////////////////////////
////

ObjectCreator::ObjectCreator(void)
	: m_factory(NULL),
	m_accessMutex(NULL),
	m_logger(NULL),
	m_context(NULL),
	m_visualization_connector(NULL)
{

}

ObjectCreator::~ObjectCreator(void)
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

	if(m_visualization_connector != NULL)
	{
		delete m_visualization_connector;
		m_visualization_connector = NULL;
	}

	if(m_accessMutex != NULL)
	{
		delete m_accessMutex;
		m_accessMutex = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ObjectCreator::initInstance(void)
{
	m_instance = new ObjectCreator;
}

void ObjectCreator::destroyInstance(void)
{
	delete m_instance;
	m_instance = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ObjectCreator::init(ObjectFactory* factory)
{
	assert(factory != NULL);
	m_factory = factory;
	m_accessMutex = m_factory->newMutex();

	m_logger = m_factory->newLogger();
	m_context = m_factory->newContext();
	m_visualization_connector = m_factory->newVisualizationConnector();
}

