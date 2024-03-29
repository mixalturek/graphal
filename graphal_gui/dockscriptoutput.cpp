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


#include "dockscriptoutput.h"
#include "settings.h"


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

	m_textEdit = new QTextBrowser;

	m_textEdit->setUndoRedoEnabled(false);
	m_textEdit->setReadOnly(true);
	m_textEdit->setOpenLinks(false);// anchorClicked() -> MainWindow::openAndScroll()
	m_textEdit->setFont(SETTINGS.getEditorFont());

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
	append(str, QColor(255, 0, 0));
}

void DockScriptOutput::error(const QString& pos, const QString& str)
{
	append(pos, str, QColor(255, 0, 0));
}

/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::warn(const QString& str)
{
	append(str, QColor(255, 0, 0));
}

void DockScriptOutput::warn(const QString& pos, const QString& str)
{
	append(pos, str, QColor(255, 0, 0));
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::info(const QString& str)
{
	append(str, QColor(130, 130, 130));
}

void DockScriptOutput::info(const QString& pos, const QString& str)
{
	append(pos, str, QColor(130, 130, 130));
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::scriptStdout(const QString& str)
{
	m_textEdit->moveCursor(QTextCursor::End);
	m_textEdit->setTextColor(QColor(0, 0, 0));
	m_textEdit->insertPlainText(str);
	m_textEdit->ensureCursorVisible();
}


/////////////////////////////////////////////////////////////////////////////
////

void DockScriptOutput::append(const QString& str, const QColor& color)
{
	m_textEdit->moveCursor(QTextCursor::End);
	m_textEdit->setTextColor(color);
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}

void DockScriptOutput::append(const QString& pos, const QString& str, const QColor& color)
{
	m_textEdit->moveCursor(QTextCursor::End);
	m_textEdit->insertHtml("<a href=\"" + pos + "\">" + pos + "</a>: ");
	m_textEdit->setTextColor(color);
	m_textEdit->insertPlainText(str);
	m_textEdit->insertPlainText("\n");
	m_textEdit->ensureCursorVisible();
}
