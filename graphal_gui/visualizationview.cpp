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


#include <cassert>
#include "visualizationview.h"
#include "visualization.h"


/////////////////////////////////////////////////////////////////////////////
////

Visualization* VisualizationView::m_visualization(NULL);


/////////////////////////////////////////////////////////////////////////////
////

VisualizationView::VisualizationView(void)
	: QObject(),
	m_name(""),
	m_posx(0.0f),
	m_posy(0.0f),
	m_posz(0.0f),
	m_rotx(0.0f),
	m_roty(0.0f)
{

}

VisualizationView::~VisualizationView(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

VisualizationView::VisualizationView(const VisualizationView& object)
	: QObject(),
	m_name(object.m_name),
	m_posx(object.m_posx),
	m_posy(object.m_posy),
	m_posz(object.m_posz),
	m_rotx(object.m_rotx),
	m_roty(object.m_roty)
{

}

VisualizationView& VisualizationView::operator= (const VisualizationView& object)
{
	m_name = object.m_name;
	m_posx = object.m_posx;
	m_posy = object.m_posy;
	m_posz = object.m_posz;
	m_rotx = object.m_rotx;
	m_roty = object.m_roty;

	return *this;
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationView::clear(void)
{
	m_name = "";
	m_posx = 0.0f;
	m_posy = 0.0f;
	m_posz = 0.0f;
	m_rotx = 0.0f;
	m_roty = 0.0f;
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationView::selected(void)
{
	assert(m_visualization != NULL);
	m_visualization->setCurrentView(*this);
}


/////////////////////////////////////////////////////////////////////////////
////

void VisualizationView::setAll(float x, float y, float z, float rotx, float roty)
{
	m_name = "";
	m_posx = x;
	m_posy = y;
	m_posz = z;
	m_rotx = rotx;
	m_roty = roty;
}
