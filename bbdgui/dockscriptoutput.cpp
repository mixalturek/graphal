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
	m_textEdit(NULL)
{
	reinit();
}

DockScriptOutput::~DockScriptOutput(void)
{
	if(m_textEdit != NULL)
	{
		delete m_textEdit;
		m_textEdit = NULL;
	}
}

void DockScriptOutput::reinit(void)
{
	if(m_textEdit != NULL)
	{
		delete m_textEdit;
		m_textEdit = NULL;
	}

	m_textEdit = new QTextBrowser();// TODO: this as parent, check memory leaks

	m_textEdit->setUndoRedoEnabled(false);
	m_textEdit->setReadOnly(true);
	m_textEdit->setOpenLinks(false);// anchorClicked() -> MainWindow::open()

	// TODO: add to the settings
	QFont font("Monospace", 9);
	font.setStyleHint(QFont::TypeWriter);
	m_textEdit->setFont(font);

	setWidget(m_textEdit);

	connect(m_textEdit, SIGNAL(anchorClicked(QUrl)),
			this, SLOT(anchorClicked(QUrl)));
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::anchorClicked(const QUrl& link)
{
	// Links are expected in "filename:line" format
	// MS Windows C:/filename:line !!!

	bool ok;
	int line = link.toString().section(':', -1).toInt(&ok);

	if(ok)
		emit anchorClicked(link.toString().section(':', 0, -2), line);
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::error(const QString& str)
{
	m_textEdit->setTextColor(QColor(255, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}

void DockScriptOutput::error(const QString& pos, const QString& str)
{
	m_textEdit->insertHtml("<a href=\"" + pos + "\">" + pos + "</a>: ");
	m_textEdit->setTextColor(QColor(255, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}

/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::warn(const QString& str)
{
	m_textEdit->setTextColor(QColor(255, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}

void DockScriptOutput::warn(const QString& pos, const QString& str)
{
	m_textEdit->insertHtml("<a href=\"" + pos + "\">" + pos + "</a>: ");
	m_textEdit->setTextColor(QColor(255, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::info(const QString& str)
{
	m_textEdit->setTextColor(QColor(130, 130, 130));
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::scriptStdout(const QString& str)
{
	m_textEdit->setTextColor(QColor(0, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->ensureCursorVisible();
}
