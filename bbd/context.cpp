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


/////////////////////////////////////////////////////////////////////////////
////

Context::Context()
	: BaseObject(),
	m_local_variables()
{
	pushLocal();
}


Context::~Context()
{
	while(!m_local_variables.empty())
		popLocal();
}

/////////////////////////////////////////////////////////////////////////////
////

void Context::pushLocal(void)
{
	m_local_variables.push_back(map<identifier, Value*>());
}

void Context::popLocal(void)
{
	map<identifier, Value*>& frame = m_local_variables.back();

	map<identifier, Value*>::iterator it;
	for(it = frame.begin(); it != frame.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	m_local_variables.pop_back();
}


/////////////////////////////////////////////////////////////////////////////
////

RetVal Context::getLocalVariable(identifier name)
{
	assert(!m_local_variables.empty());

	map<identifier, Value*>::iterator it = m_local_variables.back().find(name);

	if(it != m_local_variables.back().end())
		return RetVal((*it).second, false);
	else
		return RetVal(new ValueNull());
}


RetVal Context::setLocalVariable(identifier name, Value* val)
{
	assert(!m_local_variables.empty());
	assert(val != NULL);

	map<identifier, Value*>::iterator it = m_local_variables.back().find(name);
	if(it != m_local_variables.back().end())
	{
		delete it->second;
		it->second = NULL;
		m_local_variables.back().erase(it);
	}

	return RetVal(m_local_variables.back()[name] = val, false);
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::dump(ostream& os, uint indent) const
{

}

ostream& operator<<(ostream& os, const Context& node)
{
	node.dump(os, 0);
	return os;
}
