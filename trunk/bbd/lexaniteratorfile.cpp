/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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

#include <stdexcept>
#include "lexaniteratorfile.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

LexanIteratorFile::LexanIteratorFile(const string& filename)
	: LexanIterator(STR2ID(filename), 1),
	m_file(filename.c_str(), ios::in)
{
	if(!m_file.is_open())
		THROW(runtime_error(_("Unable to open file: ") + filename));
}

LexanIteratorFile::~LexanIteratorFile(void)
{
	m_file.close();
}


/////////////////////////////////////////////////////////////////////////////
////

char LexanIteratorFile::get(void)
{
	return m_file.get();
}

void LexanIteratorFile::unget(void)
{
	m_file.unget();
}


/////////////////////////////////////////////////////////////////////////////
////

void LexanIteratorFile::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<LexanIteratorFile file=\"" << ID2STR(getFile()) << "\" />" << endl;
}

ostream& operator<<(ostream& os, const LexanIteratorFile& node)
{
	node.dump(os, 0);
	return os;
}
