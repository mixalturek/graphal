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


#ifndef EDGE_HPP
#define EDGE_HPP

#include "general.hpp"
#include "valuestruct.hpp"
#include "valuegraph.hpp"

class ValueVertex;

class ValueEdge : public Value
{
public:
	// Don't define copy constructor or operator=, shallow copy must be used!
	ValueEdge(ValueGraph* graph, ValueVertex* begin, ValueVertex* end);
	virtual ~ValueEdge();

	virtual bool     toBool(void) const { return true; }
	virtual string toString(void) const { return "ValueEdge"; }

	virtual ValueEdge*           toValueEdge(void) { return this; }
	virtual ValueStruct*       toValueStruct(void) { return m_properties; }

	virtual void dump(ostream& os, uint indent) const;

	ValueVertex* getBeginVertex(void) { return m_begin; }
	ValueVertex* getEndVertex(void)   { return m_end; }

	ValueGraph* getGraph(void) { return m_graph; }

	CountPtr<Value> setItem(identifier name, CountPtr<Value> value) { return m_properties->setItem(name, value); }
	CountPtr<Value> getItem(identifier name) { return m_properties->getItem(name); }
	bool isItemSet(identifier name) { return m_properties->isItemSet(name); }

	virtual CountPtr<Value> iterator(void) const { return m_properties->iterator(); }
	virtual CountPtr<Value> hasNext(void) const { return m_properties->hasNext(); }
	virtual CountPtr<Value> next(void) { return m_properties->next(); }
	virtual void resetIterator(void) { m_properties->resetIterator(); }

private:
	friend void ValueGraph::invertEdgesOrientation(void);
	void invertOrientation(void);

public:
	virtual PTR_Value add(const Value&   right) const; // +
	virtual PTR_Value sub(const Value&   right) const; // -
	virtual PTR_Value mult(const Value&  right) const; // *
	virtual PTR_Value div(const Value&   right) const; // /
	virtual PTR_Value mod(const Value&   right) const; // %
	virtual PTR_Value eq(const Value&    right) const; // ==
	virtual PTR_Value eq(const ValueEdge& left) const;
	virtual PTR_Value ne(const Value&    right) const; // !=
	virtual PTR_Value ne(const ValueEdge& left) const;
	virtual PTR_Value le(const Value&    right) const; // <=
	virtual PTR_Value ge(const Value&    right) const; // >=
	virtual PTR_Value lt(const Value&    right) const; // <
	virtual PTR_Value gt(const Value&    right) const; // >
	virtual PTR_Value member(const Value& right) const; // .
	virtual PTR_Value index(const Value&  right) const; // []
	virtual PTR_Value logNOT(void)              const; // !

private:
	ValueGraph*  m_graph;
	ValueVertex* m_begin;
	ValueVertex* m_end;
	ValueStruct* m_properties;
};

ostream& operator<<(ostream& os, const ValueEdge& node);

#endif
