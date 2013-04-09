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


#ifndef VARIABLEINT_HPP
#define VARIABLEINT_HPP

#include <sstream>
#include "general.h"
#include "value.h"

class ValueInt: public Value
{
public:
	ValueInt(int val);
	virtual ~ValueInt();

public:
	int              getVal(void) const { return m_val; }
	virtual bool     toBool(void) const { return m_val; }
	virtual string toString(void) const { ostringstream os; os << m_val; return os.str(); }
	virtual bool  isNumeric(void) const { return true; }
	virtual float     toInt(void) const { return m_val; }
	virtual float   toFloat(void) const { return m_val; }

	virtual ValueInt*             toValueInt(void) { return this; }

	virtual void dump(ostream& os, uint indent) const;

	// +
	virtual CountPtr<Value> add(const Value&      right) const;
	virtual CountPtr<Value> add(const ValueBool&   left) const;
	virtual CountPtr<Value> add(const ValueInt&    left) const;
	virtual CountPtr<Value> add(const ValueFloat&  left) const;

	// -
	virtual CountPtr<Value> sub(const Value&      right) const;
	virtual CountPtr<Value> sub(const ValueBool&   left) const;
	virtual CountPtr<Value> sub(const ValueInt&    left) const;
	virtual CountPtr<Value> sub(const ValueFloat&  left) const;

	// *
	virtual CountPtr<Value> mult(const Value&      right) const;
	virtual CountPtr<Value> mult(const ValueBool&   left) const;
	virtual CountPtr<Value> mult(const ValueInt&    left) const;
	virtual CountPtr<Value> mult(const ValueFloat&  left) const;

	// /
	virtual CountPtr<Value> div(const Value&      right) const;
	virtual CountPtr<Value> div(const ValueBool&   left) const;
	virtual CountPtr<Value> div(const ValueInt&    left) const;
	virtual CountPtr<Value> div(const ValueFloat&  left) const;

	// %
	virtual CountPtr<Value> mod(const Value&      right) const;
	virtual CountPtr<Value> mod(const ValueBool&   left) const;
	virtual CountPtr<Value> mod(const ValueInt&    left) const;
	virtual CountPtr<Value> mod(const ValueFloat&  left) const;

	// ==
	virtual CountPtr<Value> eq(const Value&      right) const;
	virtual CountPtr<Value> eq(const ValueBool&   left) const;
	virtual CountPtr<Value> eq(const ValueInt&    left) const;
	virtual CountPtr<Value> eq(const ValueFloat&  left) const;

	// !=
	virtual CountPtr<Value> ne(const Value&      right) const;
	virtual CountPtr<Value> ne(const ValueBool&   left) const;
	virtual CountPtr<Value> ne(const ValueInt&    left) const;
	virtual CountPtr<Value> ne(const ValueFloat&  left) const;

	// <=
	virtual CountPtr<Value> le(const Value&      right) const;
	virtual CountPtr<Value> le(const ValueBool&   left) const;
	virtual CountPtr<Value> le(const ValueInt&    left) const;
	virtual CountPtr<Value> le(const ValueFloat&  left) const;

	// >=
	virtual CountPtr<Value> ge(const Value&      right) const;
	virtual CountPtr<Value> ge(const ValueBool&   left) const;
	virtual CountPtr<Value> ge(const ValueInt&    left) const;
	virtual CountPtr<Value> ge(const ValueFloat&  left) const;

	// <
	virtual CountPtr<Value> lt(const Value&      right) const;
	virtual CountPtr<Value> lt(const ValueBool&   left) const;
	virtual CountPtr<Value> lt(const ValueInt&    left) const;
	virtual CountPtr<Value> lt(const ValueFloat&  left) const;

	// >
	virtual CountPtr<Value> gt(const Value&      right) const;
	virtual CountPtr<Value> gt(const ValueBool&   left) const;
	virtual CountPtr<Value> gt(const ValueInt&    left) const;
	virtual CountPtr<Value> gt(const ValueFloat&  left) const;

	// !
	virtual CountPtr<Value> logNOT(void) const;

	// - (unary)
	virtual CountPtr<Value> subUn(void) const;

	// .
	virtual CountPtr<Value> member(const Value& right) const;

	// []
	virtual CountPtr<Value> index(const Value&  right) const;
	virtual CountPtr<Value> index(const ValueString& left) const;
	virtual CountPtr<Value> index(const ValueArray& left) const;

private:
	const int m_val;
};

ostream& operator<<(ostream& os, const ValueInt& node);

#endif /* VARIABLEINT_HPP */
