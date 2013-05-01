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


#ifndef TEXTEDITORHIGHLIGHTER_H
#define TEXTEDITORHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class TextEditorHighlighter : public QSyntaxHighlighter
{
public:
	TextEditorHighlighter(QTextDocument* parent);

protected:
	void highlightBlock(const QString& text);

private:
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};

	QVector<HighlightingRule> m_highlightingRules;
	QRegExp m_commentStartExp;
	QRegExp m_commentEndExp;
	QTextCharFormat m_formatComment;
};

#endif // TEXTEDITORHIGHLIGHTER_H
