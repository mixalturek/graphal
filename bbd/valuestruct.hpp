/*
 *      valuestruct.hpp
 *
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
#include <sstream>
#include "general.hpp"
#include "value.hpp"
#include "valuenull.hpp"

// TODO: strings and numbers should be used as indices
#define KEY_TYPE string

class ValueStruct: public Value
{
public:
	ValueStruct();
	virtual ~ValueStruct();

public:
	void   setItem(const string& name, Value* value);
	Value* getItem(const string& name);
	bool   isItemSet(const string& name);

public:
	virtual bool     toBool(void) const { return !m_val.empty(); }
	virtual string   toString(void) const;

	virtual PTR_Value execute(const Context& context);
	virtual void dump(ostream& os, uint indent) const;

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
	virtual PTR_Value logNOT(void)                 const; // !

private:
	map<KEY_TYPE, Value*> m_val;
	static ValueNull m_notfound; // Used in getProperty() to return NULL like variable
};

ostream& operator<<(ostream& os, const ValueStruct& node);

#endif /* VARIABLESTRUCT_HPP */
