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


#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "texteditorprogrammers.h"

class TextEditor : public TextEditorProgrammers
{
	Q_OBJECT

public:
	TextEditor(QWidget* parent = 0);

	void newFile(void);
	bool loadFile(const QString& fileName, bool warnIfNotFound);
	bool save(const QString& directory = "");
	bool saveAs(const QString& directory);
	bool saveFile(const QString& fileName);

	QString userFriendlyCurrentFile(void) const;
	QString currentFile(void) const { return m_curFile; }
	bool isUntitled(void) const { return m_isUntitled; }

	void findText(const QString& text, const QTextDocument::FindFlags& flags);
	int replaceText(const QString& text, const QString& replacement,
		QTextDocument::FindFlags flags,	bool prompt);
	int replaceAll(const QString& text, const QString& replacement,
		QTextDocument::FindFlags flags);
	int replaceConfirmation(const QString& text, const QString& replacement,
		QTextDocument::FindFlags flags,	bool* replacementDone);

protected:
	void closeEvent(QCloseEvent* event);

private slots:
	void setWindowModifiedFlag(void);

private:
	bool maybeSave(void);
	void initCurrentFile(const QString& fileName);

private:
	QString m_curFile;
	bool m_isUntitled;
};

#endif
