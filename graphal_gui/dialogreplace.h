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


#ifndef DIALOGREPLACE_H
#define DIALOGREPLACE_H

#include <QDialog>
#include <QTextDocument>
#include "ui_dialogreplace.h"

class DialogReplace : public QDialog
{
public:
	DialogReplace(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	QString getTextFind(void) const { return ui.editFind->text(); }
	void setTextFind(const QString& text) { ui.editFind->setText(text); ui.editFind->selectAll(); }

	QString getTextReplace(void) const { return ui.editReplace->text(); }
	void setTextReplace(const QString& text) { ui.editReplace->setText(text); }

	QTextDocument::FindFlags getFlags(void) const;
	void setFlags(QTextDocument::FindFlags flags);

	bool getPrompt(void) const { return ui.checkPrompt->isChecked(); }
	void setPrompt(bool prompt) const { return ui.checkPrompt->setChecked(prompt); }

private:
	Ui::DialogReplace ui;
};

#endif // DIALOGREPLACE_H
