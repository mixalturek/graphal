/*
 * Copyright 2009 Michal Turek
 *
 * This file is part of Graphal GUI.
 * http://graphal.sourceforge.net/
 *
 * Graphal GUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal GUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal GUI.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef GUIVISUALIZATIONCONNECTOR_H
#define GUIVISUALIZATIONCONNECTOR_H

#include <QObject>
#include "general.h"
#include "visualizationconnector.h"
#include "visualizationitemdata.h"

class GuiVisualizationConnector : public QObject, public VisualizationConnector
{
		Q_OBJECT

public:
	GuiVisualizationConnector(void);
	~GuiVisualizationConnector(void);

	virtual void dump(ostream& os, uint indent) const;
	void setGraphPath(const QString& path) { ACCESS_MUTEX_LOCKER; m_graphPath = path; }

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
	virtual CountPtr<Value> visGetGraph(void);

private:
	QString m_graphPath;
};

#endif // GUIVISUALIZATIONCONNECTOR_H
