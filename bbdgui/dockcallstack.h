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


#ifndef DOCKCALLSTACK_H
#define DOCKCALLSTACK_H

#include <QDockWidget>


class QTreeView;
class QStandardItemModel;

class DockCallStack : public QDockWidget
{
	Q_OBJECT

public:
	DockCallStack(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~DockCallStack(void);

public slots:
	void clear(void);
	void insert(const QString& function, const QString& filename, int line);

private:
	QTreeView* m_table;
	QStandardItemModel* m_itemModel;
};

#endif // DOCKCALLSTACK_H
