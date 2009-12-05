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


#ifndef OBJECTFACTORY_HPP
#define OBJECTFACTORY_HPP

#include "general.hpp"
#include "baseobject.hpp"

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
