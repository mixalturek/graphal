/*
 *      nodeblock.hpp
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


#ifndef NODEBLOCK_HPP
#define NODEBLOCK_HPP

#include <list>
#include <cassert>
#include "general.h"
#include "node.h"
#include "nodefunctioncall.h"

class NodeBlock : public Node
{
public:
	NodeBlock(void);
	NodeBlock(Node* node);
	virtual ~NodeBlock(void);

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

	void pushCommandToFront(Node* node) { assert(node != NULL); m_commands.push_front(node); }
	void pushCommandToBack(Node* node) { assert(node != NULL); m_commands.push_back(node); }
	uint getNumberOfCommands(void) const { return m_commands.size(); }

private:
	NodeBlock(const NodeBlock& object);
	NodeBlock& operator=(const NodeBlock& object);

private:
	friend CountPtr<Value> NodeFunctionCall::execute(void);
	list<Node*> m_commands;
};

ostream& operator<<(ostream& os, const NodeBlock& node);

#endif // NODEBLOCK_HPP