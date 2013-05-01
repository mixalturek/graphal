/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <algorithm>
#include "nodeblock.h"
#include "valuenull.h"


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
	for_each(m_commands.begin(), m_commands.end(), DeleteObject());
	m_commands.clear();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> NodeBlock::execute(void)
{
	list<Node*>::iterator it;

	for(it = m_commands.begin(); it != m_commands.end(); it++)
		(*it)->execute();

	return VALUENULL;
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

