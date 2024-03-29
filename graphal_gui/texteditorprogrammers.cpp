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


#include <QPainter>
#include "texteditorprogrammers.h"
#include "texteditorlines.h"
#include "texteditorhighlighter.h"
#include "settings.h"

#define LR_LINES_MARGIN 3


/////////////////////////////////////////////////////////////////////////////
////

TextEditorProgrammers::TextEditorProgrammers(QWidget* parent)
	: QPlainTextEdit(parent),
	m_lineNumberArea(new TextEditorLines(this)),
	m_highlighter(new TextEditorHighlighter(document()))
{
	setFont(SETTINGS.getEditorFont());

	updateSettings();

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

int TextEditorProgrammers::lineNumberAreaWidth()
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

void TextEditorProgrammers::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::updateLineNumberArea(const QRect& rect, int dy)
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

void TextEditorProgrammers::resizeEvent(QResizeEvent* e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::highlightCurrentLine(void)
{
	if(!isReadOnly())
	{
		QTextEdit::ExtraSelection selection;
		selection.format.setBackground(QColor(233, 238, 244));
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

void TextEditorProgrammers::lineNumberAreaPaintEvent(QPaintEvent* event)
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


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::keyPressEvent(QKeyEvent* event)
{
	switch(event->key())
	{
	case Qt::Key_Return:
	case Qt::Key_Enter:
		QPlainTextEdit::keyPressEvent(event);
		autoIndent();
		break;

	case Qt::Key_Home:
		// Home or Shift+Home, standard behavior for other modifiers
		if(!event->modifiers() || event->modifiers() == Qt::ShiftModifier)
			homeKey(event->modifiers() == Qt::ShiftModifier);
		else
			QPlainTextEdit::keyPressEvent(event);
		break;

	default:
		QPlainTextEdit::keyPressEvent(event);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::autoIndent(void)
{
	QTextBlock previousBlock = textCursor().block().previous();
	if(!previousBlock.isValid())
		return;

	QString previousBlockText = previousBlock.text();

	int num;
	int size = previousBlockText.size();
	for(num = 0; num < size; num++)
	{
		if(!previousBlockText.at(num).isSpace())
			break;
	}

	if(num > 0)
		textCursor().insertText(previousBlockText.left(num));

	if(num < size && previousBlockText.at(num) == '{')
	{
		if(SETTINGS.getUseSpaces())
			textCursor().insertText(QString(SETTINGS.getTabStopWidth(), ' '));
		else
			textCursor().insertText("\t");
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::homeKey(bool shift)
{
	QTextCursor::MoveMode mode(shift ? QTextCursor::KeepAnchor : QTextCursor::MoveAnchor);
	QTextCursor cursor(textCursor());
	QString text(cursor.block().text());
	int oldPos = cursor.columnNumber();
	int size = text.size();

	int pos;
	for(pos = 0; pos < size; pos++)
	{
		if(!text.at(pos).isSpace())
			break;
	}

	cursor.movePosition(QTextCursor::StartOfLine, mode);

	if(oldPos != pos)
		cursor.movePosition(QTextCursor::NextCharacter, mode, pos);

	setTextCursor(cursor);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::paintEvent(QPaintEvent* event)
{
	QPlainTextEdit::paintEvent(event);

	// TODO: 4 is the space between the left border and the text, how to get it?
	int x = fontMetrics().maxWidth() * SETTINGS.getVertLinePos() + 4;

	if(x > event->rect().x() && x < event->rect().x() + event->rect().width())
	{
		int y = event->rect().y();
		QPainter painter(viewport());
		painter.setPen(Qt::gray);
		painter.drawLine(x, y, x, y + event->rect().height());
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::updateSettings(void)
{
	setFont(SETTINGS.getEditorFont());
	setTabStopWidth(fontMetrics().width(QLatin1Char(' ')) * SETTINGS.getTabStopWidth());
	setLineWrapMode(SETTINGS.getWrapLines() ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorProgrammers::removeTrailingSpaces(void)
{
	if(!SETTINGS.getRemoveTrailingSpaces())
		return;

	QTextDocument* doc = document();

	for(int i = 0; i < doc->blockCount(); i++)
	{
		QTextBlock block = doc->findBlockByNumber(i);
		QString str = block.text();
		int pos = str.length()-1;

		while(pos >= 0)
		{
			if(!str.at(pos).isSpace())
				break;
			--pos;
		}

		if(pos < str.length()-1)
		{
			QTextCursor cursor(block);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor, str.length()-1-pos);
			cursor.removeSelectedText();
		}
	}
}
