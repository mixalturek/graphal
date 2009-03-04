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


#ifndef VALUEVERTEXSET_HPP
#define VALUEVERTEXSET_HPP

#include <set>
#include "general.hpp"
#include "value.hpp"

class ValueGraph;
class ValueVertex;

class ValueVertexSet : public Value
{
public:
	ValueVertexSet(ValueGraph* graph);
	virtual ~ValueVertexSet();

	virtual bool     toBool(void) const { return !m_vertices.empty(); }
	virtual string toString(void) const { return "ValueVertexSet"; }

	virtual ValueVertexSet* toValueVertexSet(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	void addVertex(ValueVertex* vertex);
	void deleteVertex(ValueVertex* vertex);
	uint getNumVertices(void) const { return m_vertices.size(); }
	bool contains(ValueVertex* vertex) const { return m_vertices.count(vertex); }

	ValueGraph* getGraph(void) { return m_graph; }

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

private:
	ValueGraph* m_graph;
	set<ValueVertex*> m_vertices;
	set<ValueVertex*>::iterator m_it;

public:
	virtual PTR_Value add(const Value&        right) const; // +
	virtual PTR_Value sub(const Value&        right) const; // -
	virtual PTR_Value mult(const Value&       right) const; // *
	virtual PTR_Value div(const Value&        right) const; // /
	virtual PTR_Value mod(const Value&        right) const; // %
	virtual PTR_Value eq(const Value&         right) const; // ==
	virtual PTR_Value eq(const ValueVertexSet& left) const;
	virtual PTR_Value ne(const Value&         right) const; // !=
	virtual PTR_Value ne(const ValueVertexSet& left) const;
	virtual PTR_Value le(const Value&         right) const; // <=
	virtual PTR_Value ge(const Value&         right) const; // >=
	virtual PTR_Value lt(const Value&         right) const; // <
	virtual PTR_Value gt(const Value&         right) const; // >
	virtual PTR_Value member(const Value&     right) const; // .
	virtual PTR_Value index(const Value&      right) const; // []
	virtual PTR_Value logNOT(void)                   const; // !
};

ostream& operator<<(ostream& os, const ValueVertexSet& node);

#endif /* VALUEVERTEXSET_HPP */
