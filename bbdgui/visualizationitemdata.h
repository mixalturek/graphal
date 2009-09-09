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


#ifndef VISUALIZATIONITEMDATA_H
#define VISUALIZATIONITEMDATA_H

#include <QColor>
#include "general.hpp"
#include "value.hpp"

class VisualizationItemData : public QObject
{
	Q_OBJECT

public:
	VisualizationItemData(void);
	VisualizationItemData(CountPtr<Value> value, identifier name, const QColor& color);
	VisualizationItemData(const VisualizationItemData& object);
	~VisualizationItemData(void);

	VisualizationItemData& operator= (const VisualizationItemData& object);

	// Hack for connect()
	const VisualizationItemData* getMe(void) const { return this; }

	CountPtr<Value> getValue(void) const { return m_value; }
	identifier getName(void) const { return m_name; }
	const QColor& getColor(void) const { return m_color; }
	bool isEnabled(void) const { return m_enabled; }

public slots:
	void setEnabled(bool enabled) { m_enabled = enabled; }

private:
	CountPtr<Value> m_value;
	identifier m_name;
	QColor m_color;
	bool m_enabled;
};

#endif // VISUALIZATIONITEMDATA_H
