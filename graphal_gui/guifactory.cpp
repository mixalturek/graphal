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


#include "guifactory.h"
#include "guilogger.h"
#include "guicontext.h"
#include "guimutex.h"
#include "guivisualizationconnector.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiFactory::GuiFactory(void)
	: ObjectFactory()
{

}

GuiFactory::~GuiFactory(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void GuiFactory::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<GuiFactory />" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

Logger* GuiFactory::newLogger(void) const
{
	return new GuiLogger;
}

Context* GuiFactory::newContext(void) const
{
	return new GuiContext;
}

Mutex* GuiFactory::newMutex(void) const
{
	return new GuiMutex;
}

VisualizationConnector* GuiFactory::newVisualizationConnector(void) const
{
	return new GuiVisualizationConnector;
}
