/*
 *      node.hpp
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


#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include "general.hpp"
#include "baseobject.hpp"
#include "context.hpp"

class Value;
typedef auto_ptr<Value> PTR_Value;

class Node : public BaseObject
{
public:
	Node(void);
	virtual ~Node(void);

	virtual PTR_Value execute(Context& context) = 0;

	virtual void dump(ostream& os, uint indent) const = 0;
	static void dumpIndent(ostream& os, uint indent);

/* TODO: resolve
private:
	Node(const Node& object);
	Node& operator=(const Node& object);
*/
};

#endif /* NODE_HPP */