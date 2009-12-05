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


#ifndef CLIFACTORY_HPP
#define CLIFACTORY_HPP

#include "general.hpp"
#include "objectfactory.hpp"


class CliFactory : public ObjectFactory
{
public:
	CliFactory(void);
	virtual ~CliFactory(void);

	void dump(ostream& os, uint indent) const;

	virtual Logger* newLogger(void) const;
	virtual Context* newContext(void) const;
	virtual Mutex* newMutex(void) const;
	virtual VisualizationConnector* newVisualizationConnector(void) const;
};

#endif // CLIFACTORY_HPP
