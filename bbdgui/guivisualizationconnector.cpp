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


#include "guivisualizationconnector.h"
#include "guicontext.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiVisualizationConnector::GuiVisualizationConnector(void)
	: QObject(),
	VisualizationConnector()
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
		STR2ID(name), QColor(r, g, b)));
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
