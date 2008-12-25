/*
 *      nodebinaryeq.cpp
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

#include "nodebinaryeq.hpp"
#include "context.hpp"
#include "value.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeBinaryEq::NodeBinaryEq(Node* left, Node* right)
	: NodeBinary(left, right)
{

}

NodeBinaryEq::~NodeBinaryEq(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


PTR_Value NodeBinaryEq::execute(Context& context)
{
	return m_left->execute(context)->eq(*(m_right->execute(context)));
}


/////////////////////////////////////////////////////////////////////////////
////

void NodeBinaryEq::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<NodeBinaryEq>" << endl;

	m_left->dump(os, indent+1);
	m_right->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</NodeBinaryEq>" << endl;
}

ostream& operator<<(ostream& os, const NodeBinaryEq& node)
{
	node.dump(os, 0);
	return os;
}

