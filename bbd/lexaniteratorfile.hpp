/*
 *      lexaniteratorfile.hpp
 *
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

#ifndef LEXANITERATORFILE_HPP
#define LEXANITERATORFILE_HPP

#include <fstream>
#include "general.hpp"
#include "lexaniterator.hpp"

class LexanIteratorFile : public LexanIterator
{
public:
	LexanIteratorFile(const string& filename);
	virtual ~LexanIteratorFile(void);

	virtual string toString(void) const { return "LexanIteratorFile: " + m_filename; }

	virtual char get(void);
	virtual void unget(void);

	virtual const string getSource(void) const { return _("File ") + m_filename; }
	virtual int getPos(void) const { return m_line; }

private:
	string m_filename;
	ifstream m_file;
	uint m_line;
};

#endif
