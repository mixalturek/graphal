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


#ifndef VARIABLESTRING_HPP
#define VARIABLESTRING_HPP

#include "general.h"
#include "value.h"

class ValueString: public Value
{
public:
	ValueString(const string& val);
	virtual ~ValueString();

public:
	const string& getVal(void) const { return m_val; }
	virtual bool toBool(void) const { return !m_val.empty(); }
	virtual string toString(void) const { return m_val; }

	virtual ValueString*       toValueString(void) { return this; }

	uint getSize(void) const { return m_val.size(); }

	virtual void dump(ostream& os, uint indent) const;

	virtual CountPtr<Value> add(const Value&     right) const; // +
	// virtual CountPtr<Value> add(const ValueString& left) const;
	virtual CountPtr<Value> sub(const Value&     right) const; // -
	virtual CountPtr<Value> mult(const Value&    right) const; // *
	virtual CountPtr<Value> div(const Value&     right) const; // /
	virtual CountPtr<Value> mod(const Value&     right) const; // %
	virtual CountPtr<Value> eq(const Value&      right) const; // ==
	virtual CountPtr<Value> eq(const ValueString& left) const;
	virtual CountPtr<Value> ne(const Value&      right) const; // !=
	virtual CountPtr<Value> ne(const ValueString& left) const;
	virtual CountPtr<Value> le(const Value&      right) const; // <=
	virtual CountPtr<Value> le(const ValueString& left) const;
	virtual CountPtr<Value> ge(const Value&      right) const; // >=
	virtual CountPtr<Value> ge(const ValueString& left) const;
	virtual CountPtr<Value> lt(const Value&      right) const; // <
	virtual CountPtr<Value> lt(const ValueString& left) const;
	virtual CountPtr<Value> gt(const Value&      right) const; // >
	virtual CountPtr<Value> gt(const ValueString& left) const;
	virtual CountPtr<Value> member(const Value&  right) const; // .
	virtual CountPtr<Value> index(const Value&   right) const; // []
	virtual CountPtr<Value> logNOT(void)                const; // !

private:
	const string m_val;
};

ostream& operator<<(ostream& os, const ValueString& node);

#endif /* VARIABLESTRING_HPP */
