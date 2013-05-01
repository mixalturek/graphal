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


#include "nodeloop.h"
#include "value.h"
#include "valuenull.h"
#include "valuebool.h"
#include "nodeemptycommand.h"
#include "nodevalue.h"
#include "nodejumpbreak.h"
#include "nodejumpcontinue.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeLoop::NodeLoop(Node* init, Node* condition, Node* inc, Node* body)
	: Node(),
	m_init((init != NULL) ? init : new NodeEmptyCommand),
	m_condition((condition != NULL) ? condition : new NodeValue(VALUEBOOL_TRUE)),
	m_inc((inc != NULL) ? inc : new NodeEmptyCommand),
	m_body((body != NULL) ? body : new NodeEmptyCommand)
{

}

NodeLoop::~NodeLoop()
{
	delete m_init;
	m_init = NULL;

	delete m_condition;
	m_condition = NULL;

	delete m_inc;
	m_inc = NULL;

	delete m_body;
	m_body = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeLoop::execute(void)
{
	m_init->execute();

	try
	{
		while(m_condition->execute()->toBool())
		{
			try
			{
				m_body->execute();
			}
			catch(NodeJumpContinue* ex)
			{
				// Only the exception jump is needed
			}

			m_inc->execute();
		}
	}
	catch(NodeJumpBreak* ex)
	{
		// Only the exception jump is needed
	}

	return VALUENULL;
}

void NodeLoop::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Loop>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Init>" << endl;
	m_init->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Init>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Condition>" << endl;
	m_condition->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Condition>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Inc>" << endl;
	m_inc->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Inc>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Body>" << endl;
	m_body->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Body>" << endl;

	dumpIndent(os, indent);
	os << "</Loop>" << endl;
}

ostream& operator<<(ostream& os, const NodeLoop& node)
{
	node.dump(os, 0);
	return os;
}

