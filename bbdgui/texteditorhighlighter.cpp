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


#include "texteditorhighlighter.h"


/////////////////////////////////////////////////////////////////////////////
////

TextEditorHighlighter::TextEditorHighlighter(QTextDocument* parent)
	: QSyntaxHighlighter(parent),
	m_commentStartExp("/\\*"),
	m_commentEndExp("\\*/"),
	m_formatComment()
{
	HighlightingRule rule;
	QTextCharFormat formatKeyword;
	QTextCharFormat formatKeywordPreprocessor;
	QTextCharFormat formatString;
	QTextCharFormat formatBreakpoint;
	QTextCharFormat formatNumberInt;
	QTextCharFormat formatNumberFloat;
	QTextCharFormat formatFunction;

	formatKeyword.setFontWeight(QFont::Bold);
	formatKeywordPreprocessor.setFontWeight(QFont::Bold);
	formatKeywordPreprocessor.setForeground(QColor(0, 0, 255));
	formatString.setForeground(QColor(0, 128, 0));
	formatBreakpoint.setForeground(QColor(255, 0, 0));
	formatBreakpoint.setFontWeight(QFont::Bold);
	formatNumberInt.setForeground(QColor(0, 0, 255));
	formatNumberFloat.setForeground(QColor(128, 0, 128));
	formatFunction.setForeground(Qt::black);
	m_formatComment.setForeground(QColor(128, 128, 128));


	// THE ORDER OF m_highlightingRules.append() IS SIGNIFICANT!

	// Int
	rule.pattern = QRegExp("\\b\\d+(?:e[+-]?\\d+)?\\b", Qt::CaseInsensitive);
	rule.format = formatNumberInt;
	m_highlightingRules.append(rule);

	rule.pattern = QRegExp("\\b0x[0-9a-f]+(?:e[+-]?[0-9a-f]+)?\\b", Qt::CaseInsensitive);
	rule.format = formatNumberInt;
	m_highlightingRules.append(rule);

	// Float
	rule.pattern = QRegExp("\\d*\\.\\d+(?:e[+-]?\\d+)?\\b", Qt::CaseInsensitive);
	rule.format = formatNumberFloat;
	m_highlightingRules.append(rule);

	// Functions
	rule.pattern = QRegExp("\\b[a-z0-9_]+(?=\\()", Qt::CaseInsensitive);
	rule.format = formatFunction;
	m_highlightingRules.append(rule);

	// Keywords
	rule.pattern = QRegExp("\\b(function|return|if|else|while|for|foreach|break|continue|null|true|false|global)\\b");
	rule.format = formatKeyword;
	m_highlightingRules.append(rule);

	// Preprocessor keywords
	rule.pattern = QRegExp("\\b(__FILE__|__LINE__|__FUNCTION__|include|define)\\b");
	rule.format = formatKeywordPreprocessor;
	m_highlightingRules.append(rule);

	// Breakpoint
	rule.pattern = QRegExp("\\bbreakpoint\\b");
	rule.format = formatBreakpoint;
	m_highlightingRules.append(rule);

	// Strings
	rule.pattern = QRegExp("\"(?:[^\"]|\\\\\")*\"");
	rule.format = formatString;
	m_highlightingRules.append(rule);

	// C++ style comments
	rule.pattern = QRegExp("//[^\n]*");
	rule.format = m_formatComment;
	m_highlightingRules.append(rule);
}


/////////////////////////////////////////////////////////////////////////////
////

void TextEditorHighlighter::highlightBlock(const QString& text)
{
	foreach(HighlightingRule rule, m_highlightingRules)
	{
		QRegExp expression(rule.pattern);
		int index = text.indexOf(expression);

		while(index >= 0)
		{
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = text.indexOf(expression, index + length);
		}
	}

	setCurrentBlockState(0);

	int startIndex = 0;
	if(previousBlockState() != 1)
	startIndex = text.indexOf(m_commentStartExp);

	while(startIndex >= 0)
	{
		int endIndex = text.indexOf(m_commentEndExp, startIndex);
		int comLength = 0;

		if(endIndex == -1)
		{
			setCurrentBlockState(1);
			comLength = text.length() - startIndex;
		}
		else
			comLength = endIndex - startIndex + m_commentEndExp.matchedLength();

		setFormat(startIndex, comLength, m_formatComment);
		startIndex = text.indexOf(m_commentStartExp, startIndex + comLength);
	}
}
