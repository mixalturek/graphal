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

#ifndef TEXTEDITORPROGRAMMERS_H
#define TEXTEDITORPROGRAMMERS_H

#include <QPlainTextEdit>

class TextEditorHighlighter;

class TextEditorProgrammers : public QPlainTextEdit
{
	Q_OBJECT

public:
	TextEditorProgrammers(QWidget* parent = 0);

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth(void);

	void updateSettings(void);

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine(void);
	void updateLineNumberArea(const QRect&, int);

protected:
	void resizeEvent(QResizeEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	void autoIndent(void);
	void homeKey(bool shift);

private:
	QWidget* m_lineNumberArea;
	TextEditorHighlighter* m_highlighter;
};

#endif // TEXTEDITORPROGRAMMERS_H
