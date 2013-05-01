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


#include <QTreeView>
#include <QStandardItemModel>
#include "dockvariables.h"


/////////////////////////////////////////////////////////////////////////////
////

enum CallStackColumns
{
	COL_NAME = 0,
	COL_VALUE = 1,
};


/////////////////////////////////////////////////////////////////////////////
////

DockVariables::DockVariables(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(tr("Variables"), parent, flags),
	m_table(new QTreeView(this)),
	m_itemModel(new QStandardItemModel(0, 2, m_table))
{
	QStringList headers;
	headers << tr("Name") << tr("Value");
	m_itemModel->setHorizontalHeaderLabels(headers);

	m_table->setModel(m_itemModel);
	m_table->setRootIsDecorated(false);
	m_table->setAlternatingRowColors(true);
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_table->resizeColumnToContents(COL_NAME);
	m_table->resizeColumnToContents(COL_VALUE);
	setWidget(m_table);
}

DockVariables::~DockVariables(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DockVariables::insert(const QString& name, const QString& value)
{

	QList<QStandardItem *> items;
	items << new QStandardItem(name) << new QStandardItem(value);

	m_itemModel->appendRow(items);
	m_table->resizeColumnToContents(COL_NAME);
	m_table->resizeColumnToContents(COL_VALUE);
}


/////////////////////////////////////////////////////////////////////////////
////

void DockVariables::clear(void)
{
	m_itemModel->removeRows(0, m_itemModel->rowCount());
}
