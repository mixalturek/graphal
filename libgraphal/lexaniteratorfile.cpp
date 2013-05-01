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

#include <stdexcept>
#include "lexaniteratorfile.h"
#include "context.h"


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
