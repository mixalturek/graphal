/*
 *      nodeloop.cpp
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
#include "nodeloop.hpp"
#include "value.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeLoop::NodeLoop(Node* init, Node* condition, Node* inc, Node* body)
	: Node(),
	m_init(init),
	m_condition((condition != NULL) ? condition : new ValueBool(true)),
	m_inc(inc),
	m_body(body)
{
	assert(body != NULL);
}

NodeLoop::~NodeLoop()
{
	if(m_init != NULL)
	{
		delete m_init;
		m_init = NULL;
	}

	delete m_condition;
	m_condition = NULL;

	if(m_inc != NULL)
	{
		delete m_inc;
		m_inc = NULL;
	}

	delete m_body;
	m_body = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

RetVal NodeLoop::execute(Context& context)
{
	// TODO: set position in the code to the context
	// TODO: catch jump exceptions

	if(m_init != NULL)
		m_init->execute(context);

//	try
//	{
		while(m_condition->execute(context)->toBool())
		{
//			try
//			{
				m_body->execute(context);
/*			}
			catch(CContinueException& ex)
			{
				// Need only the exception jump
			}
*/
			if(m_inc != NULL)
				m_inc->execute(context);
		}
/*	}
	catch(CBreakException& ex)
	{
		// Only the jump needed
	}
*/
	return RetVal(new ValueNull());
}

void NodeLoop::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Loop>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Init>" << endl;
	if(m_init != NULL)
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
	if(m_inc != NULL)
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

