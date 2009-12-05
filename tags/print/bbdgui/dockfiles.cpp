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


#include "dockfiles.h"


/////////////////////////////////////////////////////////////////////////////
////

DockFiles::DockFiles(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(tr("Files"), parent, flags),
	m_listView(new QListView(this)),
	m_dirModel(new QDirModel(m_listView))
{
	m_dirModel->setFilter(QDir::AllEntries);
	m_dirModel->setSorting(QDir::DirsFirst);
	m_listView->setModel(m_dirModel);

	setWidget(m_listView);

	connect(m_listView, SIGNAL(doubleClicked(const QModelIndex &)),
			this, SLOT(itemSelected(const QModelIndex &)));
}

DockFiles::~DockFiles(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DockFiles::itemSelected(const QModelIndex& index)
{
	if(m_dirModel->isDir(index))
	{
		m_listView->setRootIndex(index);
		emit directoryChanged(m_dirModel->filePath(index));
	}
	else
		emit fileSelected(m_dirModel->filePath(index));
}
