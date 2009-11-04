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
#include "valueset.hpp"

class ValueVertex;
class ValueEdge;

class ValueGraph : public Value
{
public:
	ValueGraph(bool directed = false);
	virtual ~ValueGraph(void);

	virtual ValueGraph*         toValueGraph(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	virtual bool toBool(void) const;
	virtual string toString(void) const { return "#Graph"; }

	bool loadFromFile(const string& filename);

	bool isDirected(void) const;
	bool setDirected(bool directed);
	void invertEdgesDirection(void);

	CountPtr<Value> generateVertex(void);
	CountPtr<Value> generateEdge(CountPtr<Value> begin, CountPtr<Value> end);

	void deleteVertex(CountPtr<Value> vertex);
	void deleteEdge(CountPtr<Value> edge);

	uint getNumVertices(void) const;
	uint getNumEdges(void) const;

	bool containsVertex(CountPtr<Value> vertex) const;
	bool containsEdge(CountPtr<Value> edge) const;

	CountPtr<Value> getVertices(void) const { return m_vertices.clone(); }
	CountPtr<Value> getEdges(void) const { return m_edges.clone(); }
	ValueSet* getVerticesPtr(void) { return &m_vertices; }
	ValueSet* getEdgesPtr(void) { return &m_edges; }

	// Two calls can return different matrices (permutation of rows/lines),
	// use getVertices() to get current vertices order
	CountPtr<Value> getAdjacencyMatrix(void) const;

	void setPropertyToAllVertices(identifier name, CountPtr<Value> value);
	void setPropertyToAllEdges(identifier name, CountPtr<Value> value);

	// See ValueEdge::getBeginVertex()
	CountPtr<Value> findVertex(ValueVertex* vertex) const;

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
	bool m_directed;
	ValueSet m_vertices;
	ValueSet m_edges;
};

ostream& operator<<(ostream& os, const ValueGraph& node);

#endif
