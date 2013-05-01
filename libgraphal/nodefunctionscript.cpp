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


#include "nodefunctionscript.h"
#include "nodeemptycommand.h"
#include "nodejumpcontinue.h"
#include "nodejumpbreak.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunctionScript::NodeFunctionScript(identifier name, list<identifier>* parameters,
		Node* block, const CodePosition* pos)
	: NodeFunction(name, parameters),
	m_block((block != NULL) ? block : new NodeEmptyCommand),
	m_position(pos)
{
	assert(m_position != NULL);
}

NodeFunctionScript::~NodeFunctionScript()
{
	delete m_block;
	m_block = NULL;

	delete m_position;
	m_position = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeFunctionScript::execute(void)
{
	CONTEXT.setPositionEnterToFunction(m_position);

	try
	{
		m_block->execute();
	}
	catch(CountPtr<Value>& ex)
	{
		// The value would be inaccessible after CONTEXT.popLocal() call in NodeFunctionCall::execute()
		// NodeIdentifier contains only ID, not reference, so the CountPtr<> delete it
		if(ex->isLValue())
			return ex->getReferredValue();
		else
			return ex;

		return ex;
	}
	catch(NodeJumpContinue* ex)
	{
		WARN_P(_("Continue occurred outside of a loop"));
	}
	catch(NodeJumpBreak* ex)
	{
		WARN_P(_("Break occurred outside of a loop"));
	}

	return VALUENULL;
}

void NodeFunctionScript::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Function name=\"" << ID2STR(getName())
		<< "\" id=\"" << getName() << "\">" << endl;

	const list<identifier>& parameters = getParameterNames();
	list<identifier>::const_iterator it;

	for(it = parameters.begin(); it != parameters.end(); it++)
	{
		dumpIndent(os, indent + 1);
		os << "<Parameter name=\"" << ID2STR(*it) << "\" id=\"" << *it << "\" />" << endl;
	}

	m_block->dump(os, indent + 1);

	dumpIndent(os, indent);
	os << "</Function>" << endl;
}

ostream& operator<<(ostream& os, const NodeFunctionScript& node)
{
	node.dump(os, 0);
	return os;
}
