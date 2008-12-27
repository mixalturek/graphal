/*
 *      nodefunction.hpp
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


#ifndef NODEFUNCTION_HPP
#define NODEFUNCTION_HPP

#include <list>
#include "general.hpp"
#include "node.hpp"


class NodeFunction : public Node
{
public:
	NodeFunction(const list<identifier>& parameters, Node* block);
	virtual ~NodeFunction(void);

	virtual string toString(void) const { return "NodeFunction"; }

	virtual RetVal execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

	const list<identifier>& getParameterNames(void) const { return m_parameters; }

private:
	list<identifier> m_parameters;
	Node* m_block;
};

ostream& operator<<(ostream& os, const NodeFunction& node);

#endif // NODEFUNCTION_HPP
