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


#ifndef VISUALIZATIONITEMDATA_H
#define VISUALIZATIONITEMDATA_H

#include <QColor>
#include "general.h"
#include "value.h"

class VisualizationItemData : public QObject
{
	Q_OBJECT

public:
	VisualizationItemData(void);
	VisualizationItemData(CountPtr<Value> value, const QString& name, const QColor& color);
	VisualizationItemData(const VisualizationItemData& object);
	~VisualizationItemData(void);

	VisualizationItemData& operator= (const VisualizationItemData& object);

	// Hack for connect()
	const VisualizationItemData* getMe(void) const { return this; }

	CountPtr<Value> getValue(void) const { return m_value; }
	const QString& getName(void) const { return m_name; }
	const QColor& getColor(void) const { return m_color; }
	bool isEnabled(void) const { return m_enabled; }

public slots:
	void setEnabled(bool enabled) { m_enabled = enabled; }

private:
	CountPtr<Value> m_value;
	QString m_name;
	QColor m_color;
	bool m_enabled;
};

#endif // VISUALIZATIONITEMDATA_H
