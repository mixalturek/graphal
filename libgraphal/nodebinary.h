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


#ifndef NODEBINARY_HPP
#define NODEBINARY_HPP

#include "general.h"
#include "node.h"

class NodeBinary : public Node
{
public:
	NodeBinary(Node* left, Node* right);
	virtual ~NodeBinary(void);

	Node* getLeft(void) { return m_left; }
	Node* getRight(void) { return m_right; }

private:
	NodeBinary(void);
	NodeBinary(const NodeBinary& object);
	NodeBinary& operator=(const NodeBinary& object);

protected:
	Node* m_left;
	Node* m_right;
};

#endif /* NODEUNARY_HPP */
