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

#ifndef LEXANITERATORFILE_HPP
#define LEXANITERATORFILE_HPP

#include <fstream>
#include "general.h"
#include "lexaniterator.h"

class LexanIteratorFile : public LexanIterator
{
public:
	LexanIteratorFile(const string& filename);
	virtual ~LexanIteratorFile(void);

	virtual void dump(ostream& os, uint indent) const;

	virtual char get(void);
	virtual void unget(void);

private:
	ifstream m_file;
};

ostream& operator<<(ostream& os, const LexanIteratorFile& node);

#endif
