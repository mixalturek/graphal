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

/****************************************************************************
 *                                                                          *
 *           This file was generated by gen_operators.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/

#include "valueidentifier.h"
#include "generated/nodebinaryassref.h"
#include "value.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBinaryAssRef::NodeBinaryAssRef(Node* left, Node* right)
	: NodeBinary(left, right)
{

}

NodeBinaryAssRef::~NodeBinaryAssRef(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeBinaryAssRef::execute(void)
{
		CountPtr<Value> tmp(m_right->execute());
	ValueIdentifier* ident = tmp->toValueIdentifier();
	return m_left->execute()->assignRef((ident == NULL) ? tmp : ident->getVal());

}

void NodeBinaryAssRef::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<NodeBinaryAssRef>" << endl;

	m_left->dump(os, indent+1);
	m_right->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</NodeBinaryAssRef>" << endl;
}

ostream& operator<<(ostream& os, const NodeBinaryAssRef& node)
{
	node.dump(os, 0);
	return os;
}

