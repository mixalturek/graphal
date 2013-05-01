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


#include "nodeposition.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

NodePosition::NodePosition(Node* next, const CodePosition* pos)
	: Node(),
	m_next(next),
	m_position(pos)
{
	assert(next != NULL);
	assert(pos != NULL);
}

NodePosition::~NodePosition()
{
	delete m_next;
	m_next = NULL;

	delete m_position;
	m_position = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodePosition::execute(void)
{
	CONTEXT.setPosition(m_position);
	return m_next->execute();
}

void NodePosition::dump(ostream& os, uint indent) const
{
//	dumpIndent(os, indent);
//	os << "<NodePosition>" << endl;

	m_next->dump(os, indent);

//	dumpIndent(os, indent);
//	os << "</NodePosition>" << endl;
}
