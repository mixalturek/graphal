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


#include "visualizationconnector.hpp"
#include "logger.hpp"


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
	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visSetView(float /* x */, float /* y */, float /* z */,
	float /* rotx */, float /* roty */)
{
	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visUseWeightWhenPaintingEdges(bool /* enable */)
{
	WARN_P(_("Operation is not supported."));
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationConnector::visScreenshot(const string& /* path */)
{
	WARN_P(_("Operation is not supported."));
}
