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

