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


#ifndef DIALOGREPLACECONFIRMATION_H
#define DIALOGREPLACECONFIRMATION_H

#include <QDialog>
#include "ui_dialogreplaceconfirmation.h"

class DialogReplaceConfirmation : public QDialog
{
	Q_OBJECT

public:
	DialogReplaceConfirmation(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	enum ReturnCodes
	{
		REPLACE = 0,
		REPLACE_ALL,
		FIND_NEXT,
		CLOSE_DIALOG
	};

private slots:
	void replace(void);
	void replaceAll(void);
	void findNext(void);
	void closeDialog(void);

private:
	Ui::DialogReplaceConfirmation ui;
};

#endif // DIALOGREPLACECONFIRMATION_H
