/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <cstdio>
#include "lexaniteratorstring.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

LexanIteratorString::LexanIteratorString(identifier filename, uint line, identifier macroname, const string& value)
	: LexanIterator(filename, line),
	m_macroname(macroname),
	m_value(value),
	m_pos(-1)
{

}

LexanIteratorString::~LexanIteratorString(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

char LexanIteratorString::get(void)
{
	// It has to be incremented every call, unget() could be called
	if(++m_pos < (int)m_value.length())
		return m_value[m_pos];
	else
		return EOF;
}

void LexanIteratorString::unget(void)
{
	if(m_pos > 0)
		m_pos--;
}


/////////////////////////////////////////////////////////////////////////////
////

void LexanIteratorString::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<LexanIteratorString string=\"" << ID2STR(m_macroname) << "\" />" << endl;
}

ostream& operator<<(ostream& os, const LexanIteratorString& node)
{
	node.dump(os, 0);
	return os;
}
