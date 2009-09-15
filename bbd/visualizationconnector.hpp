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


#ifndef VISUALIZATIONCONNECTOR_HPP
#define VISUALIZATIONCONNECTOR_HPP

#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"


class VisualizationConnector : public BaseObject
{
public:
	VisualizationConnector(void);
	virtual ~VisualizationConnector(void);

	virtual void dump(ostream& os, uint indent) const;

public:
	virtual void visRegister(CountPtr<Value> object, const string& name, int r, int g, int b);
	virtual void repaintVisualization(void) { }
};

#endif // VISUALIZATIONCONNECTOR_HPP
