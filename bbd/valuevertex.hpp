/*
 *      vertex.hpp
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


#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>
#include "general.hpp"
#include "value.hpp"

class Graph;
class Edge;

enum ORIENTATION
{
	BEGIN = true,
	END = false
};


class ValueVertex : public Value
{
public:
	ValueVertex(ValueGraph* graph);
	virtual ~ValueVertex();

	virtual bool     toBool(void) const { return true; } // TODO:
	virtual bool     isNull(void) const { return false; }
	virtual string toString(void) const { return "ValueVertex"; } // TODO:

	void addEdge(ValueEdge* edge, ORIENTATION orientation);
	void deleteEdge(ValueEdge* edge, ORIENTATION orientation);

	set< pair<ValueEdge*, ORIENTATION> >& getEdges(void) { return m_edges; }

	uint getDegree(void) const { return m_edges.size(); }
	set<ValueEdge *> getNeighbors(void);

private:
	ValueGraph* m_graph;
	set< pair<ValueEdge*, ORIENTATION> > m_edges;
	// TODO: add ValueStruct member

public:
	virtual PTR_Value add(const Value&     right) const; // +
	virtual PTR_Value sub(const Value&     right) const; // -
	virtual PTR_Value mult(const Value&    right) const; // *
	virtual PTR_Value div(const Value&     right) const; // /
	virtual PTR_Value mod(const Value&     right) const; // %
	virtual PTR_Value eq(const Value&      right) const; // ==
	virtual PTR_Value eq(const ValueVertex& left) const;
	virtual PTR_Value ne(const Value&      right) const; // !=
	virtual PTR_Value ne(const ValueVertex& left) const;
	virtual PTR_Value le(const Value&      right) const; // <=
	virtual PTR_Value ge(const Value&      right) const; // >=
	virtual PTR_Value lt(const Value&      right) const; // <
	virtual PTR_Value gt(const Value&      right) const; // >
	virtual PTR_Value logNOT(void)                const; // !
};

#endif
