/*
 * Copyright 2009 Michal Turek
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


#ifndef OBJECTCREATOR_HPP
#define OBJECTCREATOR_HPP

#include "general.h"
#include "mutexlocker.h"

#define CREATOR ObjectCreator::getInstance()
#define FACTORY ObjectCreator::getInstance().getFactory()
#define LOGGER ObjectCreator::getInstance().getLogger()
#define CONTEXT ObjectCreator::getInstance().getContext()
#define VISUALIZATION_CONNECTOR ObjectCreator::getInstance().getVisualizationConnector()
#define ACCESS_MUTEX ObjectCreator::getInstance().getAccessMutex()

#ifdef DISABLE_THREAD_SYNCHRONIZATION
#define ACCESS_MUTEX_LOCKER
#else
#define ACCESS_MUTEX_LOCKER MutexLocker mutexLocker(ObjectCreator::getInstance().getAccessMutex())
#endif


class ObjectFactory;
class Mutex;
class Logger;
class Context;
class CodePosition;
class VisualizationConnector;


class ObjectCreator
{
public:
	static inline ObjectCreator& getInstance(void)
	{
		return *m_instance;
	}

	static void initInstance(void);
	static void destroyInstance(void);

	void init(ObjectFactory* factory);

	ObjectFactory& getFactory(void) { return *m_factory; }
	Mutex* getAccessMutex(void) { return m_accessMutex; }
	Logger* getLogger(void) { return m_logger; }
	Context& getContext(void) { return *m_context; }
	VisualizationConnector* getVisualizationConnector(void) { return m_visualization_connector; }

private:
	ObjectCreator(void);
	virtual ~ObjectCreator(void);
	ObjectCreator(const ObjectCreator& object);
	ObjectCreator& operator=(const ObjectCreator& object);

private:
	static ObjectCreator* m_instance;

	ObjectFactory* m_factory;
	Mutex* m_accessMutex;
	Logger* m_logger;
	Context* m_context;
	VisualizationConnector* m_visualization_connector;
};

#endif // OBJECTCREATOR_HPP
