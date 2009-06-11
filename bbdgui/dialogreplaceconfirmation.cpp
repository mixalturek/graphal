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
