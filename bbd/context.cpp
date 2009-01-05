/*
 *      context.cpp
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
#include "context.hpp"
#include "valuenull.hpp"
#include "nodefunction.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Context::Context()
	: BaseObject(),
	m_functions(),
	m_local_variables()
{
	pushLocal();
}


Context::~Context()
{
	while(!m_local_variables.empty())
		popLocal();

	map<identifier, NodeFunction*>::iterator it;
	for(it = m_functions.begin(); it != m_functions.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

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

void Context::dump(ostream& /* os */, uint /* indent */) const
{
	// TODO: add implementation
}

ostream& operator<<(ostream& os, const Context& node)
{
	node.dump(os, 0);
	return os;
}
