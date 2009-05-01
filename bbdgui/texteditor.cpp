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


#include <QtGui>
#include "texteditor.h"


/////////////////////////////////////////////////////////////////////////////
////

TextEditor::TextEditor()
	: QTextEdit(),
	m_curFile(""),
	m_isUntitled(true)
{
	setAttribute(Qt::WA_DeleteOnClose);

	// TODO: add to the settings
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);
	setFont(font);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::newFile()
{
	m_isUntitled = true;
	m_curFile = tr("unnamed");
	setWindowTitle(m_curFile + "[*]");

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::loadFile(const QString& fileName, bool warnIfNotFound)
{
	QFile file(fileName);

	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		if(warnIfNotFound)
		{
			QMessageBox::warning(this, tr("bbdgui"),
				tr("Cannot read file %1:\n%2.")
					.arg(fileName)
					.arg(file.errorString()));
		}

		return false;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::save()
{
	if(m_isUntitled)
		return saveAs();
	else
		return saveFile(m_curFile);
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), m_curFile);

	if(fileName.isEmpty())
		return false;

	return saveFile(fileName);
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::saveFile(const QString &fileName)
{
	QFile file(fileName);

	if(!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("bbdgui"),
			tr("Cannot write file %1:\n%2.")
				.arg(fileName)
				.arg(file.errorString()));

		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << toPlainText();
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

QString TextEditor::userFriendlyCurrentFile() const
{
	return strippedName(m_curFile);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::closeEvent(QCloseEvent* event)
{
	if(maybeSave())
		event->accept();
	else
		event->ignore();
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::documentWasModified()
{
	setWindowModified(document()->isModified());
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::maybeSave()
{
	if(document()->isModified())
	{
		QMessageBox::StandardButton ret;

		ret = QMessageBox::warning(this, tr("MDI"),
			tr("'%1' has been modified.\nDo you want to save your changes?")
				.arg(userFriendlyCurrentFile()),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

		if(ret == QMessageBox::Save)
			return save();
		else if(ret == QMessageBox::Cancel)
			return false;
	}

	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::setCurrentFile(const QString& fileName)
{
	m_curFile = QFileInfo(fileName).canonicalFilePath();
	m_isUntitled = false;
	document()->setModified(false);
	setWindowModified(false);
	setWindowTitle(userFriendlyCurrentFile() + "[*]");
}


/////////////////////////////////////////////////////////////////////////////
////

QString TextEditor::strippedName(const QString &fullFileName) const
{
	return QFileInfo(fullFileName).fileName();
}
