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


#ifndef NODEFUNCTIONCALL_HPP
#define NODEFUNCTIONCALL_HPP

#include "general.h"
#include "node.h"
#include "codeposition.h"

class NodeBlock;

class NodeFunctionCall : public Node
{
public:
	NodeFunctionCall(identifier name, NodeBlock* parameters, const CodePosition* pos);
	virtual ~NodeFunctionCall();

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	identifier m_name;
	NodeBlock* m_parameters;
	const CodePosition* m_position;// Position of the caller
};

ostream& operator<<(ostream& os, const NodeFunctionCall& node);

#endif // NODEFUNCTIONCALL_HPP
