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


#include "dialogfind.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogFind::DialogFind(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
}


/////////////////////////////////////////////////////////////////////////////
////

QTextDocument::FindFlags DialogFind::getFlags(void) const
{
	QTextDocument::FindFlags ret = 0;

	if(ui.checkCaseSensitive->isChecked())
		ret |= QTextDocument::FindCaseSensitively;

	if(ui.checkFindBackward->isChecked())
		ret |= QTextDocument::FindBackward;

	if(ui.checkWholeWords->isChecked())
		ret |= QTextDocument::FindWholeWords;

	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogFind::setFlags(QTextDocument::FindFlags flags)
{
	ui.checkCaseSensitive->setChecked(flags & QTextDocument::FindCaseSensitively);
	ui.checkFindBackward->setChecked(flags & QTextDocument::FindBackward);
	ui.checkWholeWords->setChecked(flags & QTextDocument::FindWholeWords);
}
