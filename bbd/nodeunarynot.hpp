/*
 *      nodeunarynot.hpp
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

/****************************************************************************
 *                                                                          *
 *               This class was generated by gen_operators.pl               *
 *                           Don't update directly                          *
 *                                                                          *
 ****************************************************************************/

#ifndef NODEUNARYNOT_HPP
#define NODEUNARYNOT_HPP

#include "general.hpp"
#include "nodeunary.hpp"

class NodeUnaryNot : public NodeUnary
{
public:
	NodeUnaryNot(Node* next);
	virtual ~NodeUnaryNot(void);

	virtual string toString(void) const { return "NodeUnaryNot"; }

	virtual PTR_Value execute(Context& context);
	virtual void dump(ostream& os, uint indent) const;

private:
	NodeUnaryNot(void);
	NodeUnaryNot(const NodeUnaryNot& object);
	NodeUnaryNot& operator=(const NodeUnaryNot& object);
};

ostream& operator<<(ostream& os, const NodeUnaryNot& node);

#endif /* NODEUNARYNOT_HPP */
