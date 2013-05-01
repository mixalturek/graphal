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
