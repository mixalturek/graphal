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


#include "visualizationconnector.h"
#include "logger.h"
#include "valuenull.h"


/////////////////////////////////////////////////////////////////////////////
////

VisualizationConnector::VisualizationConnector(void)
	: BaseObject()
{

}

VisualizationConnector::~VisualizationConnector(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<VisualizationConnector />" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visRegister(CountPtr<Value> /* object */,
	const string& /* name */, int /* r */, int /* g */, int /* b */)
{
//	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visSetView(float /* x */, float /* y */, float /* z */,
	float /* rotx */, float /* roty */)
{
//	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visUseWeightWhenPaintingEdges(bool /* enable */)
{
//	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visScreenshot(const string& /* path */)
{
//	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> VisualizationConnector::visGetGraph(void)
{
//	WARN_P(_("Operation is not supported."));
	return VALUENULL;
}
