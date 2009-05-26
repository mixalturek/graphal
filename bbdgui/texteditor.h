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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QPlainTextEdit>

class TextEditorHighlighter;

class TextEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	TextEditor(QWidget* parent = 0);

	void newFile();
	bool loadFile(const QString& fileName, bool warnIfNotFound);
	bool save();
	bool saveAs();
	bool saveFile(const QString& fileName);

	QString userFriendlyCurrentFile() const;
	QString currentFile() const { return m_curFile; }
	bool isUntitled() const { return m_isUntitled; }

	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth(void);

protected:
	void closeEvent(QCloseEvent* event);
	void resizeEvent(QResizeEvent *event);

private slots:
	void setWindowModifiedFlag();
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine(void);
	void updateLineNumberArea(const QRect&, int);

private:
	bool maybeSave();
	void initCurrentFile(const QString& fileName);

private:
	QString m_curFile;
	bool m_isUntitled;

	QWidget* m_lineNumberArea;
	TextEditorHighlighter* m_highlighter;
};

#endif
