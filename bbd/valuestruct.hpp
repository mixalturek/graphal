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


#ifndef VARIABLESTRUCT_HPP
#define VARIABLESTRUCT_HPP

#include <map>
#include "general.hpp"
#include "value.hpp"
#include "valuenull.hpp"

class ValueReference;

class ValueStruct: public Value
{
public:
	ValueStruct(void);
	virtual ~ValueStruct(void);
	void clear(void);

public:
	CountPtr<Value> setItem(identifier name, CountPtr<Value> val);
	CountPtr<Value> getItem(identifier name);
	bool isItemSet(identifier name);

public:
	virtual bool     toBool(void) const;
	virtual string   toString(void) const { return "#Struct"; }

	virtual ValueStruct*       toValueStruct(void) { return this; }

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

	virtual void dump(ostream& os, uint indent) const;
	uint getSize(void) const { ACCESS_MUTEX_LOCKER;	return m_val.size(); }

	void setPropertyToAllStructItems(identifier name, CountPtr<Value> value);

	virtual PTR_Value add(const Value&      right) const; // +
	virtual PTR_Value sub(const Value&      right) const; // -
	virtual PTR_Value mult(const Value&     right) const; // *
	virtual PTR_Value div(const Value&      right) const; // /
	virtual PTR_Value mod(const Value&      right) const; // %
	virtual PTR_Value eq(const Value&       right) const; // ==
	virtual PTR_Value eq(const ValueStruct&  left) const;
	virtual PTR_Value ne(const Value&       right) const; // !=
	virtual PTR_Value ne(const ValueStruct&  left) const;
	virtual PTR_Value le(const Value&       right) const; // <=
	virtual PTR_Value ge(const Value&       right) const; // >=
	virtual PTR_Value lt(const Value&       right) const; // <
	virtual PTR_Value gt(const Value&       right) const; // >
	virtual PTR_Value member(const Value&   right) const; // .
	virtual PTR_Value index(const Value&    right) const; // []
	virtual PTR_Value logNOT(void)                 const; // !

private:
	map<identifier, CountPtr<Value> > m_val;
	map<identifier, CountPtr<Value> >::iterator m_it;
};

ostream& operator<<(ostream& os, const ValueStruct& node);

#endif /* VARIABLESTRUCT_HPP */
