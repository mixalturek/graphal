/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>
#include "general.h"
#include "value.h"
#include "valuegraph.h"
#include "valuestruct.h"

class ValueEdge;

class ValueVertex : public Value
{
public:
	// Don't define copy constructor or operator=, shallow copy must be used!
	ValueVertex(ValueGraph* graph);
	virtual ~ValueVertex(void);
	void clear(void);

	virtual bool     toBool(void) const { return true; }
	virtual string toString(void) const { return "#Vertex"; }

	virtual ValueStruct*       toValueStruct(void) { return m_properties; }
	virtual ValueVertex*       toValueVertex(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	ValueSet* getEdges(void) { return m_edges; }
	CountPtr<Value> getEdgesCopy(void);

	uint getDegree(void) const;
	CountPtr<Value> getNeighbors(void);

	ValueGraph* getGraph(void) { return m_graph; }
	void setGraphToNULL(void) { m_graph = NULL; }

	CountPtr<Value> setItem(identifier name, CountPtr<Value> value) { return m_properties->setItem(name, value); }
	CountPtr<Value> getItem(identifier name) { return m_properties->getItem(name); }
	bool isItemSet(identifier name) { return m_properties->isItemSet(name); }

	virtual CountPtr<Value> iterator(void) const { return m_properties->iterator(); }
	virtual CountPtr<Value> hasNext(void) const { return m_properties->hasNext(); }
	virtual CountPtr<Value> next(void) { return m_properties->next(); }
	virtual void resetIterator(void) { m_properties->resetIterator(); }

private:
	friend CountPtr<Value> ValueGraph::generateEdge(CountPtr<Value> begin, CountPtr<Value> end);
	friend bool ValueGraph::loadFromFile(const string& filename);
	void addEdge(CountPtr<Value> edge);

	friend void ValueGraph::deleteEdge(CountPtr<Value> edge);
	void deleteEdge(CountPtr<Value> edge);

public:
	virtual CountPtr<Value> add(const Value&     right) const; // +
	virtual CountPtr<Value> sub(const Value&     right) const; // -
	virtual CountPtr<Value> mult(const Value&    right) const; // *
	virtual CountPtr<Value> div(const Value&     right) const; // /
	virtual CountPtr<Value> mod(const Value&     right) const; // %
	virtual CountPtr<Value> eq(const Value&      right) const; // ==
	virtual CountPtr<Value> eq(const ValueVertex& left) const;
	virtual CountPtr<Value> ne(const Value&      right) const; // !=
	virtual CountPtr<Value> ne(const ValueVertex& left) const;
	virtual CountPtr<Value> le(const Value&      right) const; // <=
	virtual CountPtr<Value> ge(const Value&      right) const; // >=
	virtual CountPtr<Value> lt(const Value&      right) const; // <
	virtual CountPtr<Value> gt(const Value&      right) const; // >
	virtual CountPtr<Value> member(const Value&  right) const; // .
	virtual CountPtr<Value> index(const Value&   right) const; // []
	virtual CountPtr<Value> logNOT(void)                const; // !

private:
	ValueGraph* m_graph;
	ValueSet* m_edges;
	ValueStruct* m_properties;
};

ostream& operator<<(ostream& os, const ValueVertex& node);

#endif
