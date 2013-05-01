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


#ifndef NODECONDITION_HPP
#define NODECONDITION_HPP

#include "general.h"
#include "node.h"


class NodeCondition : public Node
{
public:
	NodeCondition(Node* condition, Node* if_section, Node* else_section);
	virtual ~NodeCondition(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	NodeCondition(const NodeCondition& object);
	NodeCondition& operator=(const NodeCondition& object);

private:
	Node* m_condition;
	Node* m_if_section;
	Node* m_else_section;
};

#endif // NODECONDITION_HPP
