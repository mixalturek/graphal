/*
 *      valuestring.hpp
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


#ifndef VARIABLESTRING_HPP
#define VARIABLESTRING_HPP

#include "general.hpp"
#include "value.hpp"

class ValueString: public Value
{
public:
	ValueString(const string& val);
	virtual ~ValueString();

public:
	string           getVal(void) const { return m_val; }
	virtual bool     toBool(void) const { return !m_val.empty(); }
	virtual bool     isNull(void) const { return false; }
	virtual string toString(void) const { return m_val; }

	// +
	virtual PTR_Value add(const Value&      right) const;
	virtual PTR_Value add(const ValueNull&   left) const;
	virtual PTR_Value add(const ValueBool&   left) const;
	virtual PTR_Value add(const ValueInt&    left) const;
	virtual PTR_Value add(const ValueFloat&  left) const;
	virtual PTR_Value add(const ValueString& left) const;
	virtual PTR_Value add(const ValueStruct& left) const;

	// -
	virtual PTR_Value sub(const Value&      right) const;
	virtual PTR_Value sub(const ValueNull&   left) const;
	virtual PTR_Value sub(const ValueBool&   left) const;
	virtual PTR_Value sub(const ValueInt&    left) const;
	virtual PTR_Value sub(const ValueFloat&  left) const;
	virtual PTR_Value sub(const ValueString& left) const;
	virtual PTR_Value sub(const ValueStruct& left) const;

	// *
	virtual PTR_Value mult(const Value&      right) const;
	virtual PTR_Value mult(const ValueNull&   left) const;
	virtual PTR_Value mult(const ValueBool&   left) const;
	virtual PTR_Value mult(const ValueInt&    left) const;
	virtual PTR_Value mult(const ValueFloat&  left) const;
	virtual PTR_Value mult(const ValueString& left) const;
	virtual PTR_Value mult(const ValueStruct& left) const;

	// /
	virtual PTR_Value div(const Value&      right) const;
	virtual PTR_Value div(const ValueNull&   left) const;
	virtual PTR_Value div(const ValueBool&   left) const;
	virtual PTR_Value div(const ValueInt&    left) const;
	virtual PTR_Value div(const ValueFloat&  left) const;
	virtual PTR_Value div(const ValueString& left) const;
	virtual PTR_Value div(const ValueStruct& left) const;

	// %
	virtual PTR_Value mod(const Value&      right) const;
	virtual PTR_Value mod(const ValueNull&   left) const;
	virtual PTR_Value mod(const ValueBool&   left) const;
	virtual PTR_Value mod(const ValueInt&    left) const;
	virtual PTR_Value mod(const ValueFloat&  left) const;
	virtual PTR_Value mod(const ValueString& left) const;
	virtual PTR_Value mod(const ValueStruct& left) const;

	// ==
	virtual PTR_Value eq(const Value&      right) const;
	virtual PTR_Value eq(const ValueNull&   left) const;
	virtual PTR_Value eq(const ValueBool&   left) const;
	virtual PTR_Value eq(const ValueInt&    left) const;
	virtual PTR_Value eq(const ValueFloat&  left) const;
	virtual PTR_Value eq(const ValueString& left) const;
	virtual PTR_Value eq(const ValueStruct& left) const;

	// !=
	virtual PTR_Value ne(const Value&      right) const;
	virtual PTR_Value ne(const ValueNull&   left) const;
	virtual PTR_Value ne(const ValueBool&   left) const;
	virtual PTR_Value ne(const ValueInt&    left) const;
	virtual PTR_Value ne(const ValueFloat&  left) const;
	virtual PTR_Value ne(const ValueString& left) const;
	virtual PTR_Value ne(const ValueStruct& left) const;

	// <=
	virtual PTR_Value le(const Value&      right) const;
	virtual PTR_Value le(const ValueNull&   left) const;
	virtual PTR_Value le(const ValueBool&   left) const;
	virtual PTR_Value le(const ValueInt&    left) const;
	virtual PTR_Value le(const ValueFloat&  left) const;
	virtual PTR_Value le(const ValueString& left) const;
	virtual PTR_Value le(const ValueStruct& left) const;

	// >=
	virtual PTR_Value ge(const Value&      right) const;
	virtual PTR_Value ge(const ValueNull&   left) const;
	virtual PTR_Value ge(const ValueBool&   left) const;
	virtual PTR_Value ge(const ValueInt&    left) const;
	virtual PTR_Value ge(const ValueFloat&  left) const;
	virtual PTR_Value ge(const ValueString& left) const;
	virtual PTR_Value ge(const ValueStruct& left) const;

	// <
	virtual PTR_Value lt(const Value&      right) const;
	virtual PTR_Value lt(const ValueNull&   left) const;
	virtual PTR_Value lt(const ValueBool&   left) const;
	virtual PTR_Value lt(const ValueInt&    left) const;
	virtual PTR_Value lt(const ValueFloat&  left) const;
	virtual PTR_Value lt(const ValueString& left) const;
	virtual PTR_Value lt(const ValueStruct& left) const;

	// >
	virtual PTR_Value gt(const Value&      right) const;
	virtual PTR_Value gt(const ValueNull&   left) const;
	virtual PTR_Value gt(const ValueBool&   left) const;
	virtual PTR_Value gt(const ValueInt&    left) const;
	virtual PTR_Value gt(const ValueFloat&  left) const;
	virtual PTR_Value gt(const ValueString& left) const;
	virtual PTR_Value gt(const ValueStruct& left) const;

	// !
	virtual PTR_Value logNOT(void) const;

	// - (unary)
	virtual PTR_Value subUn(void) const;

	// ++ (prefix)
	virtual PTR_Value incPre(void);

	// -- (prefix)
	virtual PTR_Value decPre(void);

	// ++ (postfix)
	virtual PTR_Value incPost(void);

	// -- (postfix)
	virtual PTR_Value decPost(void);

private:
	string m_val;
};

#endif /* VARIABLESTRING_HPP */
