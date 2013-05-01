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


#ifndef STRINGTABLE_HPP
#define STRINGTABLE_HPP

#include <vector>
#include "general.h"
#include "baseobject.h"


class StringTable : public BaseObject
{
public:
	StringTable(uint expectedsize = 100);
	virtual ~StringTable();

	virtual void dump(ostream& os, uint indent) const;

	identifier getID(const string& str);
	string& getString(identifier id);

	uint getNumStrings(void) const;

	void clear(void);

private:
	vector<string> m_data;
};

ostream& operator<<(ostream& os, const StringTable& node);

#endif // STRINGTABLE_HPP
