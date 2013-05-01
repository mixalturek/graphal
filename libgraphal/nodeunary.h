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


#ifndef NODEUNARY_HPP
#define NODEUNARY_HPP

#include "general.h"
#include "node.h"

class NodeUnary : public Node
{
public:
	NodeUnary(Node* next);
	virtual ~NodeUnary(void);

	Node* getNext(void) { return m_next; }

private:
	NodeUnary(void);
	NodeUnary(const NodeUnary& object);
	NodeUnary& operator=(const NodeUnary& object);

protected:
	Node* m_next;
};

#endif /* NODEUNARY_HPP */
