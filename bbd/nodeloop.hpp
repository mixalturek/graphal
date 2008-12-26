/*
 *      nodeloop.hpp
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


#ifndef NODELOOP_HPP
#define NODELOOP_HPP

#include "general.hpp"
#include "node.hpp"


class NodeLoop : public Node
{
public:
	NodeLoop(Node* init, Node* condition, Node* inc, Node* body);
	virtual ~NodeLoop();

	virtual string toString(void) const { return "NodeLoop"; }

	virtual RetVal execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

private:
	NodeLoop(const NodeLoop& object);
	NodeLoop& operator=(const NodeLoop& object);

private:
	Node* m_init;
	Node* m_condition;
	Node* m_inc;
	Node* m_body;
};

ostream& operator<<(ostream& os, const NodeLoop& node);

#endif // NODELOOP_HPP
