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


#ifndef DIALOGFIND_H
#define DIALOGFIND_H

#include <QDialog>
#include <QTextDocument>
#include "ui_dialogfind.h"

class DialogFind : public QDialog
{
public:
	DialogFind(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	QString getText(void) const { return ui.editText->text(); }
	void setText(const QString& text) { ui.editText->setText(text); ui.editText->selectAll(); }

	QTextDocument::FindFlags getFlags(void) const;
	void setFlags(QTextDocument::FindFlags flags);

private:
	Ui::DialogFind ui;
};

#endif // DIALOGFIND_H
