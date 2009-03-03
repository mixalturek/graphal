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

#ifndef VALUEARRAY_HPP
#define VALUEARRAY_HPP

#include <vector>
#include "general.hpp"
#include "value.hpp"

class ValueReference;

class ValueArray : public Value
{
public:
	ValueArray();
	ValueArray(uint size);
	virtual ~ValueArray();

public:
	vector< CountPtr<Value> >   getVal(void) const { return m_val; }
	virtual bool     toBool(void) const { return !m_val.empty(); }
	virtual string toString(void) const;

	virtual ValueArray*         toValueArray(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	uint getSize(void) const { return m_val.size(); }
	void resize(uint newsize);
	CountPtr<Value> getItem(uint pos) const;
	CountPtr<Value> setItem(uint pos, CountPtr<Value> val);

	virtual CountPtr<Value> iterator(void) const;
	virtual CountPtr<Value> hasNext(void) const;
	virtual CountPtr<Value> next(void);
	virtual void resetIterator(void);

	virtual PTR_Value add(const Value&     right) const; // +
	virtual PTR_Value sub(const Value&     right) const; // -
	virtual PTR_Value mult(const Value&    right) const; // *
	virtual PTR_Value div(const Value&     right) const; // /
	virtual PTR_Value mod(const Value&     right) const; // %
	virtual PTR_Value eq(const Value&      right) const; // ==
	virtual PTR_Value eq(const ValueArray&  left) const;
	virtual PTR_Value ne(const Value&      right) const; // !=
	virtual PTR_Value ne(const ValueArray&  left) const;
	virtual PTR_Value le(const Value&      right) const; // <=
	virtual PTR_Value ge(const Value&      right) const; // >=
	virtual PTR_Value lt(const Value&      right) const; // <
	virtual PTR_Value gt(const Value&      right) const; // >
	virtual PTR_Value member(const Value&  right) const; // .
	virtual PTR_Value index(const Value&   right) const; // []
	virtual PTR_Value logNOT(void)                const; // !

private:
	vector< CountPtr<Value> > m_val;
	vector< CountPtr<Value> >::iterator m_it;
};

ostream& operator<<(ostream& os, const ValueArray& node);

#endif // VALUEARRAY_HPP
