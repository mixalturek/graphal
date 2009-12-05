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


#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include "texteditor.h"
#include "dialogreplaceconfirmation.h"


/////////////////////////////////////////////////////////////////////////////
////

TextEditor::TextEditor(QWidget* parent)
	: TextEditorProgrammers(parent),
	m_curFile(""),
	m_isUntitled(true)
{
	setAttribute(Qt::WA_DeleteOnClose);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::newFile(void)
{
	m_isUntitled = true;
	m_curFile = tr("unnamed");
	setWindowTitle(m_curFile + "[*]");

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(setWindowModifiedFlag()));
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

	initCurrentFile(fileName);

	connect(document(), SIGNAL(contentsChanged()), this, SLOT(setWindowModifiedFlag()));

	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::save(const QString& directory)
{
	if(m_isUntitled)
		return saveAs(directory);
	else
		return saveFile(m_curFile);
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::saveAs(const QString& directory)
{
	QString fileName;

	if(m_isUntitled)
		fileName = QFileDialog::getSaveFileName(this, tr("Save As"), directory);
	else
		fileName = QFileDialog::getSaveFileName(this, tr("Save As"), m_curFile);

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

	removeTrailingSpaces();

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << toPlainText();
	QApplication::restoreOverrideCursor();

	initCurrentFile(fileName);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

QString TextEditor::userFriendlyCurrentFile(void) const
{
	return QFileInfo(m_curFile).fileName();
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

void TextEditor::setWindowModifiedFlag(void)
{
	setWindowModified(document()->isModified());
}


/////////////////////////////////////////////////////////////////////////////
////

bool TextEditor::maybeSave(void)
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

void TextEditor::initCurrentFile(const QString& fileName)
{
	m_curFile = QFileInfo(fileName).canonicalFilePath();
	m_isUntitled = false;
	document()->setModified(false);
	setWindowModified(false);
	setWindowTitle(userFriendlyCurrentFile() + "[*]");
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::findText(const QString& text, const QTextDocument::FindFlags& flags)
{
	if(!find(text, flags))
	{
		QString messageText(
			(flags & QTextDocument::FindBackward)
			? tr("Beginning of document reached.<br />Continue from the end?")
			: tr("End of document reached.<br />Continue from the beginning?"));

		QMessageBox::StandardButton btn;
		btn = QMessageBox::information(this, tr("Find"),
			messageText, QMessageBox::Yes, QMessageBox::No);

		if(btn == QMessageBox::Yes)
		{
			if(flags & QTextDocument::FindBackward)
				moveCursor(QTextCursor::End);
			else
				moveCursor(QTextCursor::Start);

			findText(text, flags);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
////

int TextEditor::replaceText(const QString& text, const QString& replacement,
	QTextDocument::FindFlags flags,	bool prompt)
{
	int num = 0;

	if(prompt)
	{
		bool replacementDone = false;
		num += replaceConfirmation(text, replacement, flags, &replacementDone);

		if(replacementDone)
			return num;

		QString messageText(
			(flags & QTextDocument::FindBackward)
			? tr("Beginning of document reached.<br />Continue from the end?")
			: tr("End of document reached.<br />Continue from the beginning?"));

		QMessageBox::StandardButton btn;
		btn = QMessageBox::information(this, tr("Replace"),
			messageText, QMessageBox::Yes, QMessageBox::No);

		if(btn == QMessageBox::Yes)
		{
			if(flags & QTextDocument::FindBackward)
				moveCursor(QTextCursor::End);
			else
				moveCursor(QTextCursor::Start);

			num += replaceConfirmation(text, replacement, flags, &replacementDone);
		}
	}
	else
		num += replaceAll(text, replacement, flags);

	return num;
}


/////////////////////////////////////////////////////////////////////////////
////

int TextEditor::replaceAll(const QString& text, const QString& replacement,
	QTextDocument::FindFlags flags)
{
	int num = 0;

	moveCursor(QTextCursor::Start);
	while(find(text, flags))
	{
		insertPlainText(replacement);
		num++;
	}

	return num;
}


/////////////////////////////////////////////////////////////////////////////
////

int TextEditor::replaceConfirmation(const QString& text, const QString& replacement,
	QTextDocument::FindFlags flags, bool* replacementDone)
{
	int num = 0;
	*replacementDone = false;

	while(find(text, flags))
	{
		DialogReplaceConfirmation dlg(this);
		int ret = dlg.exec();

		switch(ret)
		{
		case DialogReplaceConfirmation::REPLACE:
			insertPlainText(replacement);
			num++;
			break;

		case DialogReplaceConfirmation::REPLACE_ALL:
			num += replaceAll(text, replacement, flags);
			*replacementDone = true;
			return num;

		case DialogReplaceConfirmation::FIND_NEXT:
			continue; // New loop iteration
			break;

		default: // DialogReplaceConfirmation::CLOSE_DIALOG or something unexpected
			*replacementDone = true;
			return num;
		}
	}

	return num;
}
