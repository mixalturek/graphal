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


#ifndef CODEPOSITION_HPP
#define CODEPOSITION_HPP

#include "general.h"
#include "baseobject.h"


class CodePosition : public BaseObject
{
public:
	CodePosition(identifier file, uint line);
	virtual ~CodePosition();

	virtual void dump(ostream& os, uint indent) const;
	string toString(void) const;

	identifier getFile(void) const { return m_file; }
	uint getLine(void) const { return m_line; }

private:
	identifier m_file;
	uint m_line;
};

#endif // CODEPOSITION_HPP
