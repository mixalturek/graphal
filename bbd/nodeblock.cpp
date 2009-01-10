/*
 *      nodeblock.cpp
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


#include "nodeblock.hpp"
#include "valuenull.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeBlock::NodeBlock()
	: Node(),
	m_commands()
{

}

NodeBlock::NodeBlock(Node* node)
	: Node(),
	m_commands()
{
	pushCommandToFront(node);
}

NodeBlock::~NodeBlock()
{
	list<Node*>::iterator it;

	for(it = m_commands.begin(); it != m_commands.end(); it++)
	{
		delete (*it);
		*it = NULL;
	}

	m_commands.clear();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeBlock::execute(Context& context)
{
	// TODO: set position in the code to the context

	list<Node*>::iterator it;

	for(it = m_commands.begin(); it != m_commands.end(); it++)
		(*it)->execute(context);

	return CountPtr<Value>(new ValueNull());
}

void NodeBlock::dump(ostream& os, uint indent) const
{
	list<Node*>::const_iterator it;

	for(it = m_commands.begin(); it != m_commands.end(); it++)
		(*it)->dump(os, indent);
}

ostream& operator<<(ostream& os, const NodeBlock& node)
{
	node.dump(os, 0);
	return os;
}

