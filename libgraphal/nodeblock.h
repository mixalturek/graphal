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
