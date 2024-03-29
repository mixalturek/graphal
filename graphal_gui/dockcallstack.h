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


#ifndef DOCKCALLSTACK_H
#define DOCKCALLSTACK_H

#include <QDockWidget>


class QTreeView;
class QStandardItemModel;
class QModelIndex;


class DockCallStack : public QDockWidget
{
	Q_OBJECT

public:
	DockCallStack(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~DockCallStack(void);

public slots:
	void clear(void);
	void insert(const QString& function, const QString& filename, int line);
	void itemDoubleClicked(const QModelIndex& index);

signals:
	void openRequest(const QString& filename, int line);

private:
	QTreeView* m_table;
	QStandardItemModel* m_itemModel;
};

#endif // DOCKCALLSTACK_H
