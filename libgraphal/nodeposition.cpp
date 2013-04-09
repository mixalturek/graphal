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
