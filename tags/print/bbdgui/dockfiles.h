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


#ifndef DOCKFILES_H
#define DOCKFILES_H

#include <QDockWidget>
#include <QListView>
#include <QDirModel>

class DockFiles : public QDockWidget
{
	Q_OBJECT

public:
	DockFiles(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	~DockFiles(void);

	void setRootIndex(const QString& path) { m_listView->setRootIndex(m_dirModel->index(path)); }
	QString rootIndex(void) { return m_dirModel->filePath(m_listView->rootIndex()); }

signals:
	void fileSelected(const QString& path);
	void directoryChanged(const QString& path);

private slots:
	void itemSelected(const QModelIndex& index);

private:
	QListView* m_listView;
	QDirModel* m_dirModel;
};

#endif // DOCKFILES_H
