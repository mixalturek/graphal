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


#include "visualizationitemdata.h"


/////////////////////////////////////////////////////////////////////////////
////

VisualizationItemData::VisualizationItemData(CountPtr<Value> value, identifier name, const QColor& color)
	: QObject(),
	m_value(value),
	m_name(name),
	m_color(color),
	m_enabled(true)
{

}

VisualizationItemData::~VisualizationItemData(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

VisualizationItemData::VisualizationItemData(void)
{

}

VisualizationItemData::VisualizationItemData(const VisualizationItemData& object)
	: QObject(),
	m_value(object.m_value),
	m_name(object.m_name),
	m_color(object.m_color),
	m_enabled(object.m_enabled)
{

}

VisualizationItemData& VisualizationItemData::operator= (const VisualizationItemData& object)
{
	m_value = object.m_value;
	m_name = object.m_name;
	m_color = object.m_color;
	m_enabled = object.m_enabled;

	return *this;
}
