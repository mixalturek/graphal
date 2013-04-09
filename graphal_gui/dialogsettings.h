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


#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>

class QListWidgetItem;
class QListWidget;
class QStackedWidget;

class DialogSettings : public QDialog
{
	Q_OBJECT

public:
	DialogSettings(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~DialogSettings(void);

public slots:
	void changePage(QListWidgetItem* current, QListWidgetItem* previous);

private:
	void createPages(void);

private:
	QListWidget* m_contents;
	QStackedWidget* m_pages;
};

#endif // DIALOGSETTINGS_H
