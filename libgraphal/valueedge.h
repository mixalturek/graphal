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


#ifndef EDGE_HPP
#define EDGE_HPP

#include "general.h"
#include "valuestruct.h"
#include "valuegraph.h"

class ValueVertex;

class ValueEdge : public Value
{
public:
	// Don't define copy constructor or operator=, shallow copy must be used!
	ValueEdge(ValueGraph* graph, CountPtr<Value> begin, CountPtr<Value> end);
	virtual ~ValueEdge(void);
	void clear(void);

	virtual bool     toBool(void) const { return true; }
	virtual string toString(void) const { return "#Edge"; }

	virtual ValueEdge*           toValueEdge(void) { return this; }
	virtual ValueStruct*       toValueStruct(void) { return m_properties; }

	virtual void dump(ostream& os, uint indent) const;

	CountPtr<Value> getBeginVertex(void);
	CountPtr<Value> getEndVertex(void);
	ValueVertex* getBeginVertexPtr(void) { return m_begin; }
	ValueVertex* getEndVertexPtr(void) { return m_end; }

	void removeVertex(ValueVertex* vertex);

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
	friend void ValueGraph::invertEdgesDirection(void);
	void invertDirection(void);

public:
	virtual CountPtr<Value> add(const Value&   right) const; // +
	virtual CountPtr<Value> sub(const Value&   right) const; // -
	virtual CountPtr<Value> mult(const Value&  right) const; // *
	virtual CountPtr<Value> div(const Value&   right) const; // /
	virtual CountPtr<Value> mod(const Value&   right) const; // %
	virtual CountPtr<Value> eq(const Value&    right) const; // ==
	virtual CountPtr<Value> eq(const ValueEdge& left) const;
	virtual CountPtr<Value> ne(const Value&    right) const; // !=
	virtual CountPtr<Value> ne(const ValueEdge& left) const;
	virtual CountPtr<Value> le(const Value&    right) const; // <=
	virtual CountPtr<Value> ge(const Value&    right) const; // >=
	virtual CountPtr<Value> lt(const Value&    right) const; // <
	virtual CountPtr<Value> gt(const Value&    right) const; // >
	virtual CountPtr<Value> member(const Value& right) const; // .
	virtual CountPtr<Value> index(const Value&  right) const; // []
	virtual CountPtr<Value> logNOT(void)              const; // !

private:
	ValueGraph*  m_graph;
	ValueVertex* m_begin;// CountPtr<Value> cannot be used, cyclic references
	ValueVertex* m_end;
	ValueStruct* m_properties;
};

ostream& operator<<(ostream& os, const ValueEdge& node);

#endif
