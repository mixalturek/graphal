/*
 *      nodebinaryass.cpp
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

/****************************************************************************
 *                                                                          *
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#include <cassert>
#include "nodevariable.hpp"
#include "nodebinaryass.hpp"
#include "context.hpp"
#include "value.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeBinaryAss::NodeBinaryAss(Node* left, Node* right)
	: NodeBinary(left, right)
{

}

NodeBinaryAss::~NodeBinaryAss(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


PTR_Value NodeBinaryAss::execute(Context& context)
{
	NodeVariable* var = dynamic_cast<NodeVariable*>(m_left);
	assert(var != NULL);// TODO: is it safe?
	return var->setValue(context, &(*m_right->execute(context)));

}


/////////////////////////////////////////////////////////////////////////////
////

void NodeBinaryAss::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<NodeBinaryAss>" << endl;

	m_left->dump(os, indent+1);
	m_right->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</NodeBinaryAss>" << endl;
}

ostream& operator<<(ostream& os, const NodeBinaryAss& node)
{
	node.dump(os, 0);
	return os;
}

