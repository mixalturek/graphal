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


#include <cassert>
#include "context.hpp"
#include "valuenull.hpp"
#include "nodefunction.hpp"
#include "nodefunctioncall.hpp"
#include "valuearray.hpp"
#include "valuestring.hpp"
#include "nodevalue.hpp"
#include "nodeblock.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Context::Context()
	: BaseObject(),
	m_functions(),
	m_local_variables(),
	m_stringtable()
{
	pushLocal();
}


Context::~Context()
{
	clear();
}


void Context::clear(void)
{
	while(!m_local_variables.empty())
		popLocal();

	map<identifier, NodeFunction*>::iterator it;
	for(it = m_functions.begin(); it != m_functions.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	m_stringtable.clear();
	m_functions.clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::pushLocal(void)
{
	m_local_variables.push_back(map<identifier, CountPtr<Value> >());
}

void Context::popLocal(void)
{
	m_local_variables.pop_back();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> Context::getLocalVariable(identifier name)
{
	assert(!m_local_variables.empty());

	map<identifier, CountPtr<Value> >::iterator it = m_local_variables.back().find(name);

	if(it != m_local_variables.back().end())
		return it->second;
	else
	{
		// TODO: message using uninitialized variable
		return CountPtr<Value>(new ValueNull());
	}
}


CountPtr<Value> Context::setLocalVariable(identifier name, CountPtr<Value> val)
{
	assert(!m_local_variables.empty());

	map<identifier, CountPtr<Value> >::iterator it = m_local_variables.back().find(name);
	if(it != m_local_variables.back().end())
		m_local_variables.back().erase(it);

	m_local_variables.back().insert(pair<identifier, CountPtr<Value> >(name, val));
	return val;
}


/////////////////////////////////////////////////////////////////////////////
////

NodeFunction* Context::getFunction(identifier name)
{
	map<identifier, NodeFunction*>::iterator it = m_functions.find(name);

	if(it != m_functions.end())
		return it->second;
	else
		return NULL;
}

void Context::addFunction(identifier name, NodeFunction* function)
{
	assert(function != NULL);

	pair< map<identifier, NodeFunction*>::iterator, bool> ret
		= m_functions.insert(pair<identifier, NodeFunction*>(name, function));

	if(!ret.second)
	{
		// TODO: message function already defined
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::dump(ostream& os, uint indent) const
{
	Node::dumpIndent(os, indent);
	os << "<Context>" << endl;


	map<identifier, NodeFunction*>::const_iterator it;
	for(it = m_functions.begin(); it != m_functions.end(); it++)
		it->second->dump(os, indent+1);

	m_stringtable.dump(os, indent+1);

	Node::dumpIndent(os, indent);
	os << "</Context>" << endl;
}

ostream& operator<<(ostream& os, const Context& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

int Context::execute(int argc, char** argv)
{
	ValueArray* argv_array = new ValueArray();
	argv_array->resize(argc);

	for(int i = 0; i < argc; i++)
		argv_array->setItem(i, new ValueString(argv[i]));

	NodeFunctionCall main(getStringTable()->getID("main"), new NodeBlock(new NodeValue(argv_array)));
	string str = main.execute()->toString();
	cout << str << endl;

	return 0;
}
