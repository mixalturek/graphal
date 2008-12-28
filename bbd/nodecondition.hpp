/*
 *      nodecondition.hpp
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


#ifndef NODECONDITION_HPP
#define NODECONDITION_HPP

#include "general.hpp"
#include "node.hpp"


class NodeCondition : public Node
{
public:
	NodeCondition(Node* condition, Node* if_section, Node* else_section);
	virtual ~NodeCondition(void);

	virtual CountPtr<Value> execute(Context& context);
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
