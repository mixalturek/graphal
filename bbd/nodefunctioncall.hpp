/*
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


#ifndef NODEFUNCTIONCALL_HPP
#define NODEFUNCTIONCALL_HPP

#include "general.hpp"
#include "node.hpp"
#include "codeposition.hpp"

class NodeBlock;

class NodeFunctionCall : public Node
{
public:
	NodeFunctionCall(identifier name, NodeBlock* parameters, CodePosition* pos);
	virtual ~NodeFunctionCall();

	virtual CountPtr<Value> execute(void);
	virtual void dump(ostream& os, uint indent) const;

private:
	identifier m_name;
	NodeBlock* m_parameters;
	CodePosition* m_position;// Position of the caller
};

ostream& operator<<(ostream& os, const NodeFunctionCall& node);

#endif // NODEFUNCTIONCALL_HPP
