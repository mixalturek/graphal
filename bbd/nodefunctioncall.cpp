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


#include <list>
#include "nodefunctioncall.hpp"
#include "nodefunction.hpp"
#include "nodeblock.hpp"
#include "valuenull.hpp"
#include "logger.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunctionCall::NodeFunctionCall(identifier name, NodeBlock* parameters, const CodePosition& pos)
	: Node(),
	m_name(name),
	m_parameters((parameters != NULL) ? parameters : new NodeBlock()),
	m_position(pos)
{

}

NodeFunctionCall::~NodeFunctionCall()
{
	delete m_parameters;
	m_parameters = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeFunctionCall::execute(void)
{
	NodeFunction* function = CONTEXT.getFunction(m_name);

	if(function == NULL)
	{
		// TODO: position
		ERROR << _("Function ") << ID2STR(m_name) << _("() has not been defined") << endl;
		return VALUENULL;
	}

	const list<identifier>& names = function->getParameterNames();

	if(names.size() == m_parameters->getNumberOfCommands())
	{
		list< CountPtr<Value> > values;

		// Evaluate parameters in the old function context
		list<Node*>::iterator itc;
		for(itc = m_parameters->m_commands.begin(); itc != m_parameters->m_commands.end(); itc++)
		{
			CountPtr<Value> tmp((*itc)->execute());

			if(tmp->isLValue())
			{
				// Passing by value
				values.push_back(tmp->getReferredValue());
			}
			else
				values.push_back(tmp);
		}

		CONTEXT.pushLocal();
			list<identifier>::const_iterator itn;
			list< CountPtr<Value> >::iterator itv;

			// Set parameters in the new function context
			for(itn = names.begin(), itv = values.begin(); itn != names.end(); itn++, itv++)
				CONTEXT.setLocalVariable(*itn, *itv);

			CountPtr<Value> ret = function->execute();
		CONTEXT.popLocal();

		CONTEXT.setPosition(m_position);// Set caller's position
		return ret;
	}
	else
	{
		// TODO: position, declared in
		ERROR << _("Wrong number of parameters was passed to function ") << ID2STR(m_name) << "(" << names << ")" << endl;
		return VALUENULL;
	}

	// Should never be called
	assert(false);
	return VALUENULL;
}

void NodeFunctionCall::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<FunctionCall name=\"" << ID2STR(m_name)
		<< "\" id=\"" << m_name << "\">" << endl;

	m_parameters->dump(os, indent + 1);

	dumpIndent(os, indent);
	os << "</FunctionCall>" << endl;
}

ostream& operator<<(ostream& os, const NodeFunctionCall& node)
{
	node.dump(os, 0);
	return os;
}
