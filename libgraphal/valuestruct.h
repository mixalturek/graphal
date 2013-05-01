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


#ifndef VARIABLESTRUCT_HPP
#define VARIABLESTRUCT_HPP

#include <map>
#include "general.h"
#include "value.h"
#include "valuenull.h"

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

	virtual CountPtr<Value> add(const Value&      right) const; // +
	virtual CountPtr<Value> sub(const Value&      right) const; // -
	virtual CountPtr<Value> mult(const Value&     right) const; // *
	virtual CountPtr<Value> div(const Value&      right) const; // /
	virtual CountPtr<Value> mod(const Value&      right) const; // %
	virtual CountPtr<Value> eq(const Value&       right) const; // ==
	virtual CountPtr<Value> eq(const ValueStruct&  left) const;
	virtual CountPtr<Value> ne(const Value&       right) const; // !=
	virtual CountPtr<Value> ne(const ValueStruct&  left) const;
	virtual CountPtr<Value> le(const Value&       right) const; // <=
	virtual CountPtr<Value> ge(const Value&       right) const; // >=
	virtual CountPtr<Value> lt(const Value&       right) const; // <
	virtual CountPtr<Value> gt(const Value&       right) const; // >
	virtual CountPtr<Value> member(const Value&   right) const; // .
	virtual CountPtr<Value> index(const Value&    right) const; // []
	virtual CountPtr<Value> logNOT(void)                 const; // !

private:
	map<identifier, CountPtr<Value> > m_val;
	map<identifier, CountPtr<Value> >::iterator m_it;
};

ostream& operator<<(ostream& os, const ValueStruct& node);

#endif /* VARIABLESTRUCT_HPP */
