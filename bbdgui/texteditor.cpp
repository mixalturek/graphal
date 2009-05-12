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
#include "texteditorlines.h"


#define LR_LINES_MARGIN 3


/////////////////////////////////////////////////////////////////////////////
////

TextEditor::TextEditor(QWidget* parent)
	: QPlainTextEdit(parent),
	m_curFile(""),
	m_isUntitled(true),
	m_lineNumberArea(new TextEditorLines(this))
{
	setAttribute(Qt::WA_DeleteOnClose);

	// TODO: add to the settings
	QFont font("Monospace", 9);
	font.setStyleHint(QFont::TypeWriter);
	setFont(font);

	connect(this, SIGNAL(blockCountChanged(int)),
			this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(const QRect&, int)),
			this, SLOT(updateLineNumberArea(const QRect&, int)));
	connect(this, SIGNAL(cursorPositionChanged()),
			this, SLOT(highlightCurrentLine()));

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::newFile()
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

	initCurrentFile(fileName);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

QString TextEditor::userFriendlyCurrentFile() const
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

void TextEditor::setWindowModifiedFlag()
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

int TextEditor::lineNumberAreaWidth()
{
	int max = qMax(1, blockCount());
	int digits = 1;

	while(max >= 10)
	{
		max /= 10;
		++digits;
	}

	return LR_LINES_MARGIN*2 + fontMetrics().width(QLatin1Char('9')) * digits;
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::updateLineNumberArea(const QRect& rect, int dy)
{
	if(dy)
		m_lineNumberArea->scroll(0, dy);
	else
		m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

	if(rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::resizeEvent(QResizeEvent* e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::highlightCurrentLine()
{
	if(!isReadOnly())
	{
		QTextEdit::ExtraSelection selection;
		selection.format.setBackground(QColor(233, 238, 244));// TODO: Add to the settings
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();

		QList<QTextEdit::ExtraSelection> extraSelections;
		extraSelections.append(selection);
		setExtraSelections(extraSelections);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
	QPainter painter(m_lineNumberArea);
	painter.fillRect(event->rect(), QColor(230, 230, 230));

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();

	while(block.isValid() && top <= event->rect().bottom())
	{
		if(block.isVisible() && bottom >= event->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(QColor(85, 85, 85));
			painter.drawText(-LR_LINES_MARGIN, top, m_lineNumberArea->width(),
				fontMetrics().height(), Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}
