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
	void removeTrailingSpaces(void);

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
