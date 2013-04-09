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


#include <cassert>
#include <algorithm>
#include "stringtable.h"
#include "objectcreator.h"


/////////////////////////////////////////////////////////////////////////////
////

StringTable::StringTable(uint expectedsize)
	: BaseObject(),
	m_data()
{
	m_data.reserve(expectedsize);
}

StringTable::~StringTable()
{

}


/////////////////////////////////////////////////////////////////////////////
////

identifier StringTable::getID(const string& str)
{
	ACCESS_MUTEX_LOCKER;
	vector<string>::const_iterator pos = find(m_data.begin(), m_data.end(), str);

	if(pos == m_data.end())
		m_data.push_back(str);

	return pos - m_data.begin();
}

string& StringTable::getString(identifier id)
{
	ACCESS_MUTEX_LOCKER;
	assert(id < m_data.size());
	return m_data[id];
}


/////////////////////////////////////////////////////////////////////////////
////

void StringTable::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<StringTable>" << endl;

	vector<string>::const_iterator it;
	for(it = m_data.begin(); it != m_data.end(); it++)
	{
		dumpIndent(os, indent+1);
		os << "<string id=\"" << (it - m_data.begin()) << "\">" << (*it) << "</string>" << endl;
	}

	dumpIndent(os, indent);
	os << "</StringTable>" << endl;
}

ostream& operator<<(ostream& os, const StringTable& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

uint StringTable::getNumStrings(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_data.size();
}


/////////////////////////////////////////////////////////////////////////////
////

void StringTable::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	m_data.clear();
}
