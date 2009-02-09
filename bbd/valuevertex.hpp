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


#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>
#include "general.hpp"
#include "value.hpp"
#include "valueedgeset.hpp"
#include "valuegraph.hpp"
#include "valuestruct.hpp"

class ValueEdge;

class ValueVertex : public Value
{
public:
	// Don't define copy constructor or operator=, shallow copy must be used!
	ValueVertex(ValueGraph* graph);
	virtual ~ValueVertex();

	virtual bool     toBool(void) const { return true; }
	virtual string toString(void) const { return "ValueVertex"; }

	virtual ValueStruct*       toValueStruct(void) { return m_properties; }
	virtual ValueVertex*       toValueVertex(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	set<ValueEdge*>* getEdges(void) { return m_edges; }

	uint getDegree(void) const { return m_edges->size(); }
	ValueVertexSet* getNeighbors(void);// Caller have to delete the memory

	ValueGraph* getGraph(void) { return m_graph; }

	CountPtr<Value> setItem(identifier name, CountPtr<Value> value) { return m_properties->setItem(name, value); }
	CountPtr<Value> getItem(identifier name) { return m_properties->getItem(name); }
	bool isItemSet(identifier name) { return m_properties->isItemSet(name); }

private:
	friend ValueEdge* ValueGraph::addEdge(ValueVertex* begin, ValueVertex* end);
	void addEdge(ValueEdge* edge);

	friend void ValueGraph::deleteEdge(ValueEdge* edge);
	void deleteEdge(ValueEdge* edge);

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
	virtual PTR_Value member(const Value&  right) const; // .
	virtual PTR_Value index(const Value&   right) const; // []
	virtual PTR_Value logNOT(void)                const; // !

private:
	ValueGraph* m_graph;
	set<ValueEdge*>* m_edges;
	ValueStruct* m_properties;
};

ostream& operator<<(ostream& os, const ValueVertex& node);

#endif
