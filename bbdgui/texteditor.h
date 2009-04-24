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

#include <QTextEdit>

class TextEditor : public QTextEdit
{
	Q_OBJECT

public:
	TextEditor();

	void newFile();
	bool loadFile(const QString& fileName);
	bool save();
	bool saveAs();
	bool saveFile(const QString& fileName);

	QString userFriendlyCurrentFile();
	QString currentFile() { return m_curFile; }

protected:
	void closeEvent(QCloseEvent* event);

private slots:
	void documentWasModified();

private:
	bool maybeSave();
	void setCurrentFile(const QString& fileName);
	QString strippedName(const QString& fullFileName);

private:
	QString m_curFile;
	bool m_isUntitled;
};

#endif
