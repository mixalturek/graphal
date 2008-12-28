/*
 *      nodefunctioncall.cpp
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


#include <list>
#include "nodefunctioncall.hpp"
#include "nodefunction.hpp"
#include "nodeblock.hpp"
#include "valuenull.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunctionCall::NodeFunctionCall(identifier name, NodeBlock* parameters)
	: Node(),
	m_name(name),
	m_parameters((parameters != NULL) ? parameters : new NodeBlock())
{

}

NodeFunctionCall::~NodeFunctionCall()
{
	delete m_parameters;
	m_parameters = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeFunctionCall::execute(Context& context)
{
	NodeFunction* function = context.getFunction(m_name);

	if(function == NULL)
	{
		// TODO: function was not found
		return CountPtr<Value>(new ValueNull());
	}

	const list<identifier>& names = function->getParameterNames();

	if(names.size() == m_parameters->getNumberOfCommands())
	{
		list< CountPtr<Value> > values;

		// Evaluate parameters in the old function context
		list<Node*>::iterator itc;
		for(itc = m_parameters->m_commands.begin(); itc != m_parameters->m_commands.end(); itc++)
			values.push_back((*itc)->execute(context));

		context.pushLocal();
			list<identifier>::const_iterator itn;
			list< CountPtr<Value> >::iterator itv;

			// Set parameters in the new function context
			for(itn = names.begin(), itv = values.begin(); itn != names.end(); itn++, itv++)
				context.setLocalVariable(*itn, *itv);

			CountPtr<Value> ret = function->execute(context);
		context.popLocal();

		return ret;
	}
	else
	{
		// TODO: _("Wrong number of parameters has been passed to the function ") + m_name + _("()"),
		return CountPtr<Value>(new ValueNull());
	}

	// Should never be called
	assert(false);
	return CountPtr<Value>(new ValueNull());
}

void NodeFunctionCall::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<FunctionCall name=\"" << m_name << "\">" << endl;

	if(m_parameters != NULL)
		m_parameters->dump(os, indent + 1);

	dumpIndent(os, indent);
	os << "</FunctionCall>" << endl;
}

ostream& operator<<(ostream& os, const NodeFunctionCall& node)
{
	node.dump(os, 0);
	return os;
}
