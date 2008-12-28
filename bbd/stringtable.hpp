/*
 *      stringtable.hpp
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


#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <vector>
#include "general.hpp"
#include "baseobject.hpp"


class StringTable : public BaseObject
{
public:
	StringTable(uint expectedsize = 100);
	virtual ~StringTable();

	virtual void dump(ostream& os, uint indent) const;

	identifier getID(const string& str);
	string& getString(identifier id);

	uint getNumStrings(void) const { return m_data.size(); }

private:
	vector<string> m_data;
};

ostream& operator<<(ostream& os, const StringTable& node);

#endif // STRINGTABLE_HPP
