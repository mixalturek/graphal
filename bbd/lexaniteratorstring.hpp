/*
 *      lexaniteratorstring.hpp
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

#ifndef LEXANITERATORSTRING_HPP
#define LEXANITERATORSTRING_HPP

#include "general.hpp"
#include "lexaniterator.hpp"

class LexanIteratorString : public LexanIterator
{
public:
	LexanIteratorString(const string& name, const string& value);
	virtual ~LexanIteratorString(void);

	virtual string toString(void) const { return "LexanIteratorString: " + m_name; }

	virtual char get(void);
	virtual void unget(void);

	virtual const string& getSource(void) const { return m_name; }
	virtual uint getPos(void) const { return m_pos; }

private:
	string m_name;
	string m_value;
	uint m_pos;
};

#endif
