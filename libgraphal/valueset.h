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
#include "general.h"
#include "value.h"
#include "countptr.h"

typedef deque< CountPtr<Value> > set_container;

class ValueSet : public Value
{
public:
	ValueSet(void);
	virtual ~ValueSet(void);

	virtual bool toBool(void) const { ACCESS_MUTEX_LOCKER; return !m_val.empty(); }
	virtual string toString(void) const { return "#Set"; }
	virtual void dump(ostream& os, uint indent) const;
	virtual ValueSet* toValueSet(void) { return this; }

	void clear(void);
	bool empty(void) const { ACCESS_MUTEX_LOCKER; return m_val.empty(); }
	CountPtr<Value> clone(void) const;

	void insert(CountPtr<Value> value);
	void remove(CountPtr<Value> value);
	void remove(const ValueSet& set);
	bool contains(CountPtr<Value> value) const;
	uint getSize(void) const { ACCESS_MUTEX_LOCKER;	return m_val.size(); }

	CountPtr<Value> getUnion(const ValueSet& vs) const;
	CountPtr<Value> getIntersection(const ValueSet& vs) const;
	CountPtr<Value> getDifference(const ValueSet& vs) const;

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

	void setPropertyToAllStructItems(identifier name, CountPtr<Value> value);

	// See ValueEdge::getBeginVertex()
	CountPtr<Value> findItem(const Value* value) const;

	set_container::iterator begin(void) { ACCESS_MUTEX_LOCKER; return m_val.begin(); }
	set_container::iterator end(void) { ACCESS_MUTEX_LOCKER; return m_val.end(); }
	set_container::const_iterator begin(void) const { ACCESS_MUTEX_LOCKER; return m_val.begin(); }
	set_container::const_iterator end(void) const { ACCESS_MUTEX_LOCKER; return m_val.end(); }

public:
	virtual CountPtr<Value> add(const Value&    right) const; // +
	virtual CountPtr<Value> sub(const Value&    right) const; // -
	virtual CountPtr<Value> mult(const Value&   right) const; // *
	virtual CountPtr<Value> div(const Value&    right) const; // /
	virtual CountPtr<Value> mod(const Value&    right) const; // %
	virtual CountPtr<Value> eq(const Value&     right) const; // ==
	virtual CountPtr<Value> eq(const ValueSet&  left) const;
	virtual CountPtr<Value> ne(const Value&     right) const; // !=
	virtual CountPtr<Value> ne(const ValueSet&  left) const;
	virtual CountPtr<Value> le(const Value&     right) const; // <=
	virtual CountPtr<Value> ge(const Value&     right) const; // >=
	virtual CountPtr<Value> lt(const Value&     right) const; // <
	virtual CountPtr<Value> gt(const Value&     right) const; // >
	virtual CountPtr<Value> member(const Value& right) const; // .
	virtual CountPtr<Value> index(const Value&  right) const; // []
	virtual CountPtr<Value> logNOT(void)               const; // !

private:
	set_container m_val;
	set_container::iterator m_it;
};

#endif // VALUESET_HPP
