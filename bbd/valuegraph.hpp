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


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include "general.hpp"
#include "value.hpp"

class ValueVertex;
class ValueEdge;

class ValueGraph : public Value
{
public:
	ValueGraph(bool oriented = false);
	virtual ~ValueGraph();

	virtual ValueGraph*         toValueGraph(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	virtual bool     toBool(void) const { return !m_vertices.empty(); }
	virtual string toString(void) const { return "#Graph"; }

	bool loadFromFile(const string& filename);

	bool isOriented(void) const { return m_oriented; }
	bool setOriented(bool oriented) { bool ret = m_oriented; m_oriented = oriented; return ret; }
	void invertEdgesOrientation(void);

	ValueVertex* generateVertex(void);
	ValueEdge* generateEdge(ValueVertex* begin, ValueVertex* end);

	void deleteVertex(ValueVertex* vertex);
	void deleteEdge(ValueEdge* edge);

	uint getNumVertices(void) const { return m_vertices.size(); }
	uint getNumEdges(void)    const { return m_edges.size(); }

	bool contains(ValueVertex* vertex) const { return m_vertices.count(vertex); }
	bool contains(ValueEdge* edge) const { return m_edges.count(edge); }

	CountPtr<Value> getVertices(void) const;// Returns ValueVertexSet
	CountPtr<Value> getEdges(void) const;// Returns ValueEdgeSet


	virtual PTR_Value add(const Value&     right) const; // +
	virtual PTR_Value sub(const Value&     right) const; // -
	virtual PTR_Value mult(const Value&    right) const; // *
	virtual PTR_Value div(const Value&     right) const; // /
	virtual PTR_Value mod(const Value&     right) const; // %
	virtual PTR_Value eq(const Value&      right) const; // ==
	virtual PTR_Value eq(const ValueGraph& left)  const;
	virtual PTR_Value ne(const Value&      right) const; // !=
	virtual PTR_Value ne(const ValueGraph& left)  const;
	virtual PTR_Value le(const Value&      right) const; // <=
	virtual PTR_Value ge(const Value&      right) const; // >=
	virtual PTR_Value lt(const Value&      right) const; // <
	virtual PTR_Value gt(const Value&      right) const; // >
	virtual PTR_Value member(const Value&  right) const; // .
	virtual PTR_Value index(const Value&   right) const; // []
	virtual PTR_Value logNOT(void)                const; // !

private:
	bool m_oriented;
	set<ValueVertex*> m_vertices;
	set<ValueEdge*> m_edges;

	// Wait with the real deleting. Some variables in the script may contain
	// another reference to the deleted object -> segmentation fault
	// CountPtr<Value> can't be used here (circle in vertex and edge classes),
	// memory wouldn't be deleted
	set<ValueVertex*> m_vertices_deleted;
	set<ValueEdge*> m_edges_deleted;
};

ostream& operator<<(ostream& os, const ValueGraph& node);

#endif
