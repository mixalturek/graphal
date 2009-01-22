/*
 *      nodevariable.cpp
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
#include "nodevariable.hpp"
#include "valuefloat.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeVariable::NodeVariable(identifier name)
	: Node(),
	m_name(name)
{

}

NodeVariable::~NodeVariable()
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeVariable::setValue(CountPtr<Value> val)
{
	return CONTEXT.setLocalVariable(m_name, val);
}

CountPtr<Value> NodeVariable::getValue(void)
{
	return CONTEXT.getLocalVariable(m_name);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeVariable::execute(void)
{
	return getValue();
}

void NodeVariable::dump(ostream& os, uint indent) const
{
	this->dumpIndent(os, indent);
	os << "<NodeVariable name=\"" << ID2STR(m_name)
		<< "\" id=\"" << m_name << "\" />" << endl;
}

ostream& operator<<(ostream& os, const NodeVariable& node)
{
	node.dump(os, 0);
	return os;
}
