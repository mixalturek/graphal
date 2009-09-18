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


#ifndef GUIVISUALIZATIONCONNECTOR_H
#define GUIVISUALIZATIONCONNECTOR_H

#include <QObject>
#include "general.hpp"
#include "visualizationconnector.hpp"
#include "visualizationitemdata.h"

class GuiVisualizationConnector : public QObject, public VisualizationConnector
{
		Q_OBJECT

public:
	GuiVisualizationConnector(void);
	~GuiVisualizationConnector(void);

	virtual void dump(ostream& os, uint indent) const;

signals:
	void visRegisterSig(VisualizationItemData);
	void repaintRequest(void);
	void setView(float, float, float, float, float);
	void useWeightWhenPaintingEdges(bool);
	void screenshot(QString);

public:
	virtual void visRegister(CountPtr<Value> object, const string& name, int r, int g, int b);
	virtual void repaintVisualization(void) { emit repaintRequest(); }
	virtual void visSetView(float x, float y, float z, float rotx, float roty);
	virtual void visUseWeightWhenPaintingEdges(bool enable);
	virtual void visScreenshot(const string& path);
};

#endif // GUIVISUALIZATIONCONNECTOR_H
