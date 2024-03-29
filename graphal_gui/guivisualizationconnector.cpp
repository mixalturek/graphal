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


#include "guivisualizationconnector.h"
#include "guicontext.h"
#include "valuenull.h"
#include "valuegraph.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiVisualizationConnector::GuiVisualizationConnector(void)
	: QObject(),
	VisualizationConnector(),
	m_graphPath("")
{

}

GuiVisualizationConnector::~GuiVisualizationConnector(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void GuiVisualizationConnector::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<GuiVisualizationConnector />" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiVisualizationConnector::visRegister(CountPtr<Value> object,
	const string& name, int r, int g, int b)
{
	emit visRegisterSig(VisualizationItemData(object,
		QString::fromStdString(name), QColor(r, g, b)));
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiVisualizationConnector::visSetView(float x, float y, float z, float rotx, float roty)
{
	emit setView(x, y, z, rotx, roty);
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiVisualizationConnector::visUseWeightWhenPaintingEdges(bool enable)
{
	emit useWeightWhenPaintingEdges(enable);
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiVisualizationConnector::visScreenshot(const string& path)
{
	emit repaintRequest();
	emit screenshot(QString::fromStdString(path));

	GuiContext* context = dynamic_cast<GuiContext*>(&CONTEXT);
	assert(context != NULL);
	context->screenshotBegin();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> GuiVisualizationConnector::visGetGraph(void)
{
	ACCESS_MUTEX_LOCKER;

	if(!m_graphPath.isEmpty())
	{
		ValueGraph* graph = new ValueGraph();
		if(graph->loadFromFile(m_graphPath.toStdString()))
			return CountPtr<Value>(graph);
		else
		{
			delete graph;
			graph = NULL;
		}
	}

	return VALUENULL;
}
