/*
 *      nodevariable.hpp
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


#ifndef VALUEVARIABLE_HPP
#define VALUEVARIABLE_HPP

#include <sstream>
#include "general.hpp"
#include "node.hpp"


class NodeVariable : public Node
{
public:
	NodeVariable(identifier name);
	virtual ~NodeVariable(void);

	virtual string toString(void) const { ostringstream os; os << "NodeVariable(" << m_name << ")"; return os.str(); }

	virtual RetVal execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

	identifier getName(void) const { return m_name; }
	RetVal setValue(Context& context, Value* val);

private:
	identifier m_name;
};

ostream& operator<<(ostream& os, const NodeVariable& node);

#endif // VALUEVARIABLE_HPP
