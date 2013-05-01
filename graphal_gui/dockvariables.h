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


#ifndef DOCKVARIABLES_H
#define DOCKVARIABLES_H

#include <QDockWidget>

class QTreeView;
class QStandardItemModel;

class DockVariables : public QDockWidget
{
public:
	DockVariables(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~DockVariables(void);

	void clear(void);
	void insert(const QString& name, const QString& value);

private:
	QTreeView* m_table;
	QStandardItemModel* m_itemModel;
};

#endif // DOCKVARIABLES_H
