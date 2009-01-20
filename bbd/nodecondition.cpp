/*
 *      nodecondition.cpp
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


#include <cassert>
#include "nodecondition.hpp"
#include "value.hpp"
#include "valuenull.hpp"
#include "nodeemptycommand.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeCondition::NodeCondition(Node* condition, Node* if_section, Node* else_section)
	: Node(),
	m_condition(condition),
	m_if_section(if_section),
	m_else_section((else_section != NULL) ? else_section : new NodeEmptyCommand())
{
	assert(condition != NULL);
	assert(if_section != NULL);
}

NodeCondition::~NodeCondition()
{
	delete m_condition;
	m_condition = NULL;

	delete m_if_section;
	m_if_section = NULL;

	delete m_else_section;
	m_else_section = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeCondition::execute(void)
{
	// TODO: set position in the code to the context

	if(m_condition->execute()->toBool())
		return m_if_section->execute();
	else if(m_else_section != NULL)
		return m_else_section->execute();
	else
		return CountPtr<Value>(new ValueNull());
}

void NodeCondition::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<If>" << endl;

		dumpIndent(os, indent + 1);
		os << "<Condition>" << endl;
			m_condition->dump(os, indent + 2);
		dumpIndent(os, indent + 1);
		os << "</Condition>" << endl;

		dumpIndent(os, indent+1);
		os << "<IfSection>" << endl;
			m_if_section->dump(os, indent + 2);
		dumpIndent(os, indent+1);
		os << "</IfSection>" << endl;

		dumpIndent(os, indent+1);
		os << "<ElseSection>" << endl;
			m_else_section->dump(os, indent + 2);
		dumpIndent(os, indent+1);
		os << "</ElseSection>" << endl;

	dumpIndent(os, indent);
	os << "</If>" << endl;
}

ostream& operator<<(ostream& os, const NodeCondition& node)
{
	node.dump(os, 0);
	return os;
}

