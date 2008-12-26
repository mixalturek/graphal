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
//#include "valuenull.hpp"
#include "valuefloat.hpp"


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

RetVal NodeVariable::setValue(Context& context, Value* val)
{
	return context.setLocalVariable(m_name, val);
}

RetVal NodeVariable::getValue(Context& context)
{
	return context.getLocalVariable(m_name);
}


/////////////////////////////////////////////////////////////////////////////
////

RetVal NodeVariable::execute(Context& context)
{
	return getValue(context);
}

void NodeVariable::dump(ostream& os, uint indent) const
{
	this->dumpIndent(os, indent);
	os << "<NodeVariable name=\"" << m_name << "\" />" << endl;
}

ostream& operator<<(ostream& os, const NodeVariable& node)
{
	node.dump(os, 0);
	return os;
}
