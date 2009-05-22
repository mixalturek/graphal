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


#include <QTreeView>
#include <QStandardItemModel>
#include "dockcallstack.h"


/////////////////////////////////////////////////////////////////////////////
////

enum CallStackColumns
{
	COL_FUNCTION = 0,
	COL_FILENAME = 1,
	COL_LINE = 2
};


/////////////////////////////////////////////////////////////////////////////
////

DockCallStack::DockCallStack(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(tr("Call stack"), parent, flags),
	m_table(new QTreeView(this)),
	m_itemModel(new QStandardItemModel(0, 3, m_table))
{
	QStringList headers;
	headers << tr("Function") << tr("File") << tr("Line");
	m_itemModel->setHorizontalHeaderLabels(headers);

	m_table->setModel(m_itemModel);
	m_table->setRootIsDecorated(false);
	m_table->setAlternatingRowColors(true);
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	setWidget(m_table);

	connect(m_table, SIGNAL(doubleClicked(const QModelIndex&)),
			this, SLOT(itemDoubleClicked(const QModelIndex&)));
}

DockCallStack::~DockCallStack(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DockCallStack::insert(const QString& function, const QString& filename, int line)
{
	QStandardItem* fileitem = new QStandardItem(filename.section('/', -1));
	fileitem->setToolTip(filename);

	QList<QStandardItem *> items;
	items << new QStandardItem(function)
		<< fileitem
		<< new QStandardItem(QString::number(line));

	m_itemModel->insertRow(0, items);
	m_table->resizeColumnToContents(COL_FUNCTION);
	m_table->resizeColumnToContents(COL_FILENAME);
	m_table->resizeColumnToContents(COL_LINE);
	m_table->scrollToTop();
}


/////////////////////////////////////////////////////////////////////////////
////

void DockCallStack::clear(void)
{
	m_itemModel->removeRows(0, m_itemModel->rowCount());
}


/////////////////////////////////////////////////////////////////////////////
////

void DockCallStack::itemDoubleClicked(const QModelIndex& index)
{
	bool ok;

	QString filename = m_itemModel->item(index.row(), COL_FILENAME)->toolTip();
	int line = m_itemModel->item(index.row(), COL_LINE)->text().toInt(&ok);

	if(ok)
		emit openRequest(filename, line);

}
