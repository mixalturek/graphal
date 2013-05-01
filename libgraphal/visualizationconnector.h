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


#ifndef VISUALIZATIONCONNECTOR_HPP
#define VISUALIZATIONCONNECTOR_HPP

#include "general.h"
#include "baseobject.h"
#include "countptr.h"
#include "value.h"


class VisualizationConnector : public BaseObject
{
public:
	VisualizationConnector(void);
	virtual ~VisualizationConnector(void);

	virtual void dump(ostream& os, uint indent) const;

public:
	virtual void visRegister(CountPtr<Value> object, const string& name, int r, int g, int b);
	virtual void repaintVisualization(void) { }
	virtual void visSetView(float x, float y, float z, float rotx, float roty);
	virtual void visUseWeightWhenPaintingEdges(bool enable);
	virtual void visScreenshot(const string& path);
	virtual CountPtr<Value> visGetGraph(void);
};

#endif // VISUALIZATIONCONNECTOR_HPP
