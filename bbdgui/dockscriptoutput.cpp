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


#include "dockscriptoutput.h"


/////////////////////////////////////////////////////////////////////////////
////

DockScriptOutput::DockScriptOutput(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(tr("Script output"), parent, flags),
	m_textEdit(new QTextBrowser(this))
{
	m_textEdit->setUndoRedoEnabled(false);
	m_textEdit->setReadOnly(true);
	setWidget(m_textEdit);
}

DockScriptOutput::~DockScriptOutput(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::scriptStdout(const QString& str)
{
	m_textEdit->append(str);
}

void DockScriptOutput::scriptStderr(const QString& str)
{
	m_textEdit->append("<span style=\"color: red;\">" + str + "</span>");
}
