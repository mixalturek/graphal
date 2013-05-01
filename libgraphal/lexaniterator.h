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

#ifndef LEXANITERATOR_HPP
#define LEXANITERATOR_HPP

#include "general.h"
#include "baseobject.h"

class LexanIterator : public BaseObject
{
public:
	LexanIterator(identifier filename, uint line);
	virtual ~LexanIterator(void);

	virtual char get(void) = 0;
	virtual void unget(void) = 0;

	identifier getFile(void) const { return m_filename; }
	uint getLine(void) const { return m_line; }

	void incLine(void) { m_line++; }

private:
	identifier m_filename;
	uint m_line;
};

#endif
