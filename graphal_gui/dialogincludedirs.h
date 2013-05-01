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


#ifndef DIALOGINCLUDEDIRS_H
#define DIALOGINCLUDEDIRS_H

#include <QDialog>
#include "ui_dialogincludedirs.h"

class DialogIncludeDirs : public QDialog
{
	Q_OBJECT

public:
	DialogIncludeDirs(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	QStringList getDirectories(void) const;
	void setDirectories(const QStringList& directories);

private slots:
	void buttonAddItem(void);
	void buttonDeleteItem(void);
	void buttonMoveUp(void);
	void buttonMoveDown(void);

private:
	Ui::DialogIncludeDirs ui;
};

#endif // DIALOGINCLUDEDIRS_H
