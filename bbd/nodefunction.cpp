/*
 *      nodefunction.cpp
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


#include "nodefunction.hpp"
#include "nodeemptycommand.hpp"
#include "valuenull.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunction::NodeFunction(list<identifier>* parameters, Node* block, identifier name)
	: Node(),
	m_parameters((parameters != NULL) ? parameters : new list<identifier>()),
	m_block((block != NULL) ? block : new NodeEmptyCommand()),
	m_name(name)
{

}

NodeFunction::~NodeFunction(void)
{
	delete m_parameters;
	m_parameters = NULL;

	delete m_block;
	m_block = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeFunction::execute(void)
{
	// TODO: built in functions

	try
	{
		m_block->execute();
	}
	catch(CountPtr<Value>& ex)
	{
		return ex;
	}

	return CountPtr<Value>(new ValueNull());;
}

void NodeFunction::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<Function name=\"" << ID2STR(m_name)
		<< "\" id=\"" << m_name << "\">" << endl;

	list<identifier>::const_iterator it;

	for(it = m_parameters->begin(); it != m_parameters->end(); it++)
	{
		dumpIndent(os, indent + 1);
		os << "<Parameter name=\"" << ID2STR(*it) << "\" id=\"" << *it << "\" />" << endl;
	}

	m_block->dump(os, indent + 1);

	dumpIndent(os, indent);
	os << "</Function>" << endl;
}

ostream& operator<<(ostream& os, const NodeFunction& node)
{
	node.dump(os, 0);
	return os;
}

ostream& operator<<(ostream& os, const list<identifier>& node)
{
	uint num = node.size();
	list<identifier>::const_iterator it = node.begin();

	for(uint i = 0; i < num-1; i++, it++)
		os << ID2STR(*it) << ", ";

	if(num > 0)
		os << ID2STR(*it);

	return os;
}
