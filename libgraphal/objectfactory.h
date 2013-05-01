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


#ifndef OBJECTFACTORY_HPP
#define OBJECTFACTORY_HPP

#include "general.h"
#include "baseobject.h"

class Logger;
class Context;
class Mutex;
class VisualizationConnector;

class ObjectFactory : public BaseObject
{
public:
	ObjectFactory(void);
	virtual ~ObjectFactory(void);

	virtual Logger* newLogger(void) const = 0;
	virtual Context* newContext(void) const = 0;
	virtual Mutex* newMutex(void) const = 0;
	virtual VisualizationConnector* newVisualizationConnector(void) const = 0;

private:
	ObjectFactory(const ObjectFactory& object);
	ObjectFactory& operator=(const ObjectFactory& object);
};

#endif // OBJECTFACTORY_HPP
