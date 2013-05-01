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

#ifndef LEXANITERATORSTRING_HPP
#define LEXANITERATORSTRING_HPP

#include "general.h"
#include "lexaniterator.h"

class LexanIteratorString : public LexanIterator
{
public:
	LexanIteratorString(identifier filename, uint line, identifier macroname, const string& value);
	virtual ~LexanIteratorString(void);

	virtual void dump(ostream& os, uint indent) const;

	virtual char get(void);
	virtual void unget(void);

	identifier getMacroName(void) const { return m_macroname; }

private:
	identifier m_macroname;
	string m_value;
	int m_pos;
};

ostream& operator<<(ostream& os, const LexanIteratorString& node);

#endif
