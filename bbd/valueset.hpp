/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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


#ifndef VALUESET_HPP
#define VALUESET_HPP

#include <deque>
#include "general.hpp"
#include "value.hpp"
#include "countptr.hpp"

typedef deque< CountPtr<Value> > set_container;

class ValueSet : public Value
{
public:
	ValueSet(void);
	virtual ~ValueSet(void);

	virtual bool toBool(void) const { ACCESS_MUTEX_LOCKER; return !m_data.empty(); }
	virtual string toString(void) const { return "#Set"; }
	virtual void dump(ostream& os, uint indent) const;
	virtual ValueSet* toValueSet(void) { return this; }

	void insert(CountPtr<Value> value);
	void remove(CountPtr<Value> value);
	bool contains(CountPtr<Value> value) const;
	uint getNumItems(void) const { ACCESS_MUTEX_LOCKER;	return m_data.size(); }

	CountPtr<Value> getUnion(const ValueSet& vs) const;
	CountPtr<Value> getIntersection(const ValueSet& vs) const;
	CountPtr<Value> getDifference(const ValueSet& vs) const;

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

//	void setPropertyToAllVertices(identifier name, CountPtr<Value> value);

public:
	virtual PTR_Value add(const Value&    right) const; // +
	virtual PTR_Value sub(const Value&    right) const; // -
	virtual PTR_Value mult(const Value&   right) const; // *
	virtual PTR_Value div(const Value&    right) const; // /
	virtual PTR_Value mod(const Value&    right) const; // %
	virtual PTR_Value eq(const Value&     right) const; // ==
	virtual PTR_Value eq(const ValueSet&  left) const;
	virtual PTR_Value ne(const Value&     right) const; // !=
	virtual PTR_Value ne(const ValueSet&  left) const;
	virtual PTR_Value le(const Value&     right) const; // <=
	virtual PTR_Value ge(const Value&     right) const; // >=
	virtual PTR_Value lt(const Value&     right) const; // <
	virtual PTR_Value gt(const Value&     right) const; // >
	virtual PTR_Value member(const Value& right) const; // .
	virtual PTR_Value index(const Value&  right) const; // []
	virtual PTR_Value logNOT(void)               const; // !

private:
	set_container m_data;
	set_container::iterator m_it;
};

#endif // VALUESET_HPP
