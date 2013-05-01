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
#include "nodeforeach.h"
#include "context.h"
#include "nodeemptycommand.h"
#include "nodejumpbreak.h"
#include "nodejumpcontinue.h"
#include "valuenull.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeForeach::NodeForeach(identifier var_name, Node* iterable, Node* body)
	: Node(),
	m_var_name(var_name),
	m_iterable(iterable),
	m_body((body != NULL) ? body : new NodeEmptyCommand)
{
	assert(iterable != NULL);
}

NodeForeach::~NodeForeach(void)
{
	delete m_iterable;
	m_iterable = NULL;

	delete m_body;
	m_body = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeForeach::execute(void)
{
	CountPtr<Value> it(m_iterable->execute()->iterator());

	try
	{
		while(it->hasNext()->toBool())
		{
			try
			{
				CONTEXT.deleteLocalVariable(m_var_name);
				CONTEXT.setLocalVariableAllowRef(m_var_name, it->next());
				m_body->execute();
			}
			catch(NodeJumpContinue* ex)
			{
				// Only the exception jump is needed
			}
		}
	}
	catch(NodeJumpBreak* ex)
	{
		// Only the exception jump is needed
	}

	return VALUENULL;
}

void NodeForeach::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Foreach variable=\"" << ID2STR(m_var_name) << "\">" << endl;

	dumpIndent(os, indent + 1);
	os << "<Iterable>" << endl;
	m_iterable->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Iterable>" << endl;

	dumpIndent(os, indent + 1);
	os << "<Body>" << endl;
	m_body->dump(os, indent + 2);
	dumpIndent(os, indent + 1);
	os << "</Body>" << endl;

	dumpIndent(os, indent);
	os << "</Foreach>" << endl;
}
