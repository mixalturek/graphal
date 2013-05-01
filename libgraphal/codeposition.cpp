/*
 * Copyright 2009 Michal Turek
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


#include <sstream>
#include "codeposition.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

CodePosition::CodePosition(identifier file, uint line)
	: BaseObject(),
	m_file(file),
	m_line(line)
{

}

CodePosition::~CodePosition()
{

}


/////////////////////////////////////////////////////////////////////////////
////

string CodePosition::toString(void) const
{
	stringstream ss;
	ss << ID2STR(m_file) << ":" << m_line;
	return ss.str();
}

void CodePosition::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<CodePosition file=\"" << ID2STR(m_file) << "\" line=\"" << m_line << "\" />" << endl;
}

