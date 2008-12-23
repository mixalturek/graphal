/*
 *      value.hpp
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


#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <memory>
#include "general.hpp"
#include "node.hpp"

class Value;
class ValueNull;
class ValueBool;
class ValueInt;
class ValueFloat;
class ValueString;
class ValueStruct;
class ValueReference;
class ValueGraph;
class ValueVertex;
class ValueEdge;
class ValueVertexSet;
class ValueEdgeSet;


typedef auto_ptr<Value> PTR_Value;


class Value : public Node
{
public:
	Value();
	virtual ~Value();

public:
	virtual bool toBool(void)     const = 0;
	virtual bool isNull(void)     const { return false; }

	// +
	virtual PTR_Value add(const Value&         right) const = 0;
	virtual PTR_Value add(const ValueNull&      left) const;
	virtual PTR_Value add(const ValueBool&      left) const;
	virtual PTR_Value add(const ValueInt&       left) const;
	virtual PTR_Value add(const ValueFloat&     left) const;
	virtual PTR_Value add(const ValueString&    left) const;
	virtual PTR_Value add(const ValueStruct&    left) const;
	virtual PTR_Value add(const ValueReference& left) const;
	virtual PTR_Value add(const ValueGraph&     left) const;
	virtual PTR_Value add(const ValueVertex&    left) const;
	virtual PTR_Value add(const ValueEdge&      left) const;
	virtual PTR_Value add(const ValueVertexSet& left) const;
	virtual PTR_Value add(const ValueEdgeSet&   left) const;

	// -
	virtual PTR_Value sub(const Value&         right) const = 0;
	virtual PTR_Value sub(const ValueNull&      left) const;
	virtual PTR_Value sub(const ValueBool&      left) const;
	virtual PTR_Value sub(const ValueInt&       left) const;
	virtual PTR_Value sub(const ValueFloat&     left) const;
	virtual PTR_Value sub(const ValueString&    left) const;
	virtual PTR_Value sub(const ValueStruct&    left) const;
	virtual PTR_Value sub(const ValueReference& left) const;
	virtual PTR_Value sub(const ValueGraph&     left) const;
	virtual PTR_Value sub(const ValueVertex&    left) const;
	virtual PTR_Value sub(const ValueEdge&      left) const;
	virtual PTR_Value sub(const ValueVertexSet& left) const;
	virtual PTR_Value sub(const ValueEdgeSet&   left) const;

	// *
	virtual PTR_Value mult(const Value&         right) const = 0;
	virtual PTR_Value mult(const ValueNull&      left) const;
	virtual PTR_Value mult(const ValueBool&      left) const;
	virtual PTR_Value mult(const ValueInt&       left) const;
	virtual PTR_Value mult(const ValueFloat&     left) const;
	virtual PTR_Value mult(const ValueString&    left) const;
	virtual PTR_Value mult(const ValueStruct&    left) const;
	virtual PTR_Value mult(const ValueReference& left) const;
	virtual PTR_Value mult(const ValueGraph&     left) const;
	virtual PTR_Value mult(const ValueVertex&    left) const;
	virtual PTR_Value mult(const ValueEdge&      left) const;
	virtual PTR_Value mult(const ValueVertexSet& left) const;
	virtual PTR_Value mult(const ValueEdgeSet&   left) const;

	// /
	virtual PTR_Value div(const Value&         right) const = 0;
	virtual PTR_Value div(const ValueNull&      left) const;
	virtual PTR_Value div(const ValueBool&      left) const;
	virtual PTR_Value div(const ValueInt&       left) const;
	virtual PTR_Value div(const ValueFloat&     left) const;
	virtual PTR_Value div(const ValueString&    left) const;
	virtual PTR_Value div(const ValueStruct&    left) const;
	virtual PTR_Value div(const ValueReference& left) const;
	virtual PTR_Value div(const ValueGraph&     left) const;
	virtual PTR_Value div(const ValueVertex&    left) const;
	virtual PTR_Value div(const ValueEdge&      left) const;
	virtual PTR_Value div(const ValueVertexSet& left) const;
	virtual PTR_Value div(const ValueEdgeSet&   left) const;

	// %
	virtual PTR_Value mod(const Value&         right) const = 0;
	virtual PTR_Value mod(const ValueNull&      left) const;
	virtual PTR_Value mod(const ValueBool&      left) const;
	virtual PTR_Value mod(const ValueInt&       left) const;
	virtual PTR_Value mod(const ValueFloat&     left) const;
	virtual PTR_Value mod(const ValueString&    left) const;
	virtual PTR_Value mod(const ValueStruct&    left) const;
	virtual PTR_Value mod(const ValueReference& left) const;
	virtual PTR_Value mod(const ValueGraph&     left) const;
	virtual PTR_Value mod(const ValueVertex&    left) const;
	virtual PTR_Value mod(const ValueEdge&      left) const;
	virtual PTR_Value mod(const ValueVertexSet& left) const;
	virtual PTR_Value mod(const ValueEdgeSet&   left) const;

	// ==
	virtual PTR_Value eq(const Value&         right) const = 0;
	virtual PTR_Value eq(const ValueNull&      left) const;
	virtual PTR_Value eq(const ValueBool&      left) const;
	virtual PTR_Value eq(const ValueInt&       left) const;
	virtual PTR_Value eq(const ValueFloat&     left) const;
	virtual PTR_Value eq(const ValueString&    left) const;
	virtual PTR_Value eq(const ValueStruct&    left) const;
	virtual PTR_Value eq(const ValueReference& left) const;
	virtual PTR_Value eq(const ValueGraph&     left) const;
	virtual PTR_Value eq(const ValueVertex&    left) const;
	virtual PTR_Value eq(const ValueEdge&      left) const;
	virtual PTR_Value eq(const ValueVertexSet& left) const;
	virtual PTR_Value eq(const ValueEdgeSet&   left) const;

	// !=
	virtual PTR_Value ne(const Value&         right) const = 0;
	virtual PTR_Value ne(const ValueNull&      left) const;
	virtual PTR_Value ne(const ValueBool&      left) const;
	virtual PTR_Value ne(const ValueInt&       left) const;
	virtual PTR_Value ne(const ValueFloat&     left) const;
	virtual PTR_Value ne(const ValueString&    left) const;
	virtual PTR_Value ne(const ValueStruct&    left) const;
	virtual PTR_Value ne(const ValueReference& left) const;
	virtual PTR_Value ne(const ValueGraph&     left) const;
	virtual PTR_Value ne(const ValueVertex&    left) const;
	virtual PTR_Value ne(const ValueEdge&      left) const;
	virtual PTR_Value ne(const ValueVertexSet& left) const;
	virtual PTR_Value ne(const ValueEdgeSet&   left) const;

	// <=
	virtual PTR_Value le(const Value&         right) const = 0;
	virtual PTR_Value le(const ValueNull&      left) const;
	virtual PTR_Value le(const ValueBool&      left) const;
	virtual PTR_Value le(const ValueInt&       left) const;
	virtual PTR_Value le(const ValueFloat&     left) const;
	virtual PTR_Value le(const ValueString&    left) const;
	virtual PTR_Value le(const ValueStruct&    left) const;
	virtual PTR_Value le(const ValueReference& left) const;
	virtual PTR_Value le(const ValueGraph&     left) const;
	virtual PTR_Value le(const ValueVertex&    left) const;
	virtual PTR_Value le(const ValueEdge&      left) const;
	virtual PTR_Value le(const ValueVertexSet& left) const;
	virtual PTR_Value le(const ValueEdgeSet&   left) const;

	// >=
	virtual PTR_Value ge(const Value&         right) const = 0;
	virtual PTR_Value ge(const ValueNull&      left) const;
	virtual PTR_Value ge(const ValueBool&      left) const;
	virtual PTR_Value ge(const ValueInt&       left) const;
	virtual PTR_Value ge(const ValueFloat&     left) const;
	virtual PTR_Value ge(const ValueString&    left) const;
	virtual PTR_Value ge(const ValueStruct&    left) const;
	virtual PTR_Value ge(const ValueReference& left) const;
	virtual PTR_Value ge(const ValueGraph&     left) const;
	virtual PTR_Value ge(const ValueVertex&    left) const;
	virtual PTR_Value ge(const ValueEdge&      left) const;
	virtual PTR_Value ge(const ValueVertexSet& left) const;
	virtual PTR_Value ge(const ValueEdgeSet&   left) const;

	// <
	virtual PTR_Value lt(const Value&         right) const = 0;
	virtual PTR_Value lt(const ValueNull&      left) const;
	virtual PTR_Value lt(const ValueBool&      left) const;
	virtual PTR_Value lt(const ValueInt&       left) const;
	virtual PTR_Value lt(const ValueFloat&     left) const;
	virtual PTR_Value lt(const ValueString&    left) const;
	virtual PTR_Value lt(const ValueStruct&    left) const;
	virtual PTR_Value lt(const ValueReference& left) const;
	virtual PTR_Value lt(const ValueGraph&     left) const;
	virtual PTR_Value lt(const ValueVertex&    left) const;
	virtual PTR_Value lt(const ValueEdge&      left) const;
	virtual PTR_Value lt(const ValueVertexSet& left) const;
	virtual PTR_Value lt(const ValueEdgeSet&   left) const;

	// >
	virtual PTR_Value gt(const Value&         right) const = 0;
	virtual PTR_Value gt(const ValueNull&      left) const;
	virtual PTR_Value gt(const ValueBool&      left) const;
	virtual PTR_Value gt(const ValueInt&       left) const;
	virtual PTR_Value gt(const ValueFloat&     left) const;
	virtual PTR_Value gt(const ValueString&    left) const;
	virtual PTR_Value gt(const ValueStruct&    left) const;
	virtual PTR_Value gt(const ValueReference& left) const;
	virtual PTR_Value gt(const ValueGraph&     left) const;
	virtual PTR_Value gt(const ValueVertex&    left) const;
	virtual PTR_Value gt(const ValueEdge&      left) const;
	virtual PTR_Value gt(const ValueVertexSet& left) const;
	virtual PTR_Value gt(const ValueEdgeSet&   left) const;

	// !
	virtual PTR_Value logNOT(void) const = 0;

	// - (unary)
	virtual PTR_Value subUn(void) const;

	// &&, ||
	PTR_Value logAND(const Value& right) const;
	PTR_Value logOR (const Value& right) const;
};

#endif /* VARIABLE_HPP */
