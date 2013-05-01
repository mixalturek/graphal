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


#include <cassert>
#include "nodecondition.h"
#include "value.h"
#include "valuenull.h"
#include "nodeemptycommand.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeCondition::NodeCondition(Node* condition, Node* if_section, Node* else_section)
	: Node(),
	m_condition(condition),
	m_if_section(if_section),
	m_else_section((else_section != NULL) ? else_section : new NodeEmptyCommand)
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
	if(m_condition->execute()->toBool())
		return m_if_section->execute();
	else
		return m_else_section->execute();
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

