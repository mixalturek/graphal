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


#include "dialogreplaceconfirmation.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogReplaceConfirmation::DialogReplaceConfirmation(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	connect(ui.buttonReplace, SIGNAL(clicked()), this, SLOT(replace()));
	connect(ui.buttonReplaceAll, SIGNAL(clicked()), this, SLOT(replaceAll()));
	connect(ui.buttonFindNext, SIGNAL(clicked()), this, SLOT(findNext()));
	connect(ui.buttonClose, SIGNAL(clicked()), this, SLOT(closeDialog()));
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogReplaceConfirmation::replace(void)
{
	done(REPLACE);
}

void DialogReplaceConfirmation::replaceAll(void)
{
	done(REPLACE_ALL);
}

void DialogReplaceConfirmation::findNext(void)
{
	done(FIND_NEXT);
}

void DialogReplaceConfirmation::closeDialog(void)
{
	done(CLOSE_DIALOG);
}
