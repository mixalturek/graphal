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


#ifndef TEXTEDITORLINES_H
#define TEXTEDITORLINES_H

#include <QWidget>

class TextEditorProgrammers;

class TextEditorLines : public QWidget
{
public:
	TextEditorLines(TextEditorProgrammers* editor);
	~TextEditorLines(void);

	QSize sizeHint(void) const;

protected:
	void paintEvent(QPaintEvent* event);

private:
	TextEditorProgrammers* m_editor;
};

#endif // TEXTEDITORLINES_H
