/*
 *      valueadapter.cpp
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


#include "valueadapter.hpp"


#include "value.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueAdapter::ValueAdapter()
	: Value()
{

}


ValueAdapter::~ValueAdapter()
{

}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueAdapter::add(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::add(const ValueBool& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::add(const ValueInt& left)     const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::add(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::add(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::add(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// -
PTR_Value ValueAdapter::sub(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::sub(const ValueBool& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::sub(const ValueInt& left)     const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::sub(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::sub(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::sub(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// *
PTR_Value ValueAdapter::mult(const ValueNull& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mult(const ValueBool& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mult(const ValueInt& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mult(const ValueFloat& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mult(const ValueString& left) const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mult(const ValueStruct& left) const { return PTR_Value(new ValueNull()); }

// /
PTR_Value ValueAdapter::div(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::div(const ValueBool& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::div(const ValueInt& left)     const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::div(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::div(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::div(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// %
PTR_Value ValueAdapter::mod(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mod(const ValueBool& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mod(const ValueInt& left)     const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mod(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mod(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueAdapter::mod(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// ==
PTR_Value ValueAdapter::eq(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::eq(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::eq(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::eq(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::eq(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::eq(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// !=
PTR_Value ValueAdapter::ne(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ne(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ne(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ne(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ne(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ne(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// <=
PTR_Value ValueAdapter::le(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::le(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::le(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::le(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::le(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::le(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// >=
PTR_Value ValueAdapter::ge(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ge(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ge(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ge(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ge(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::ge(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// <
PTR_Value ValueAdapter::lt(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::lt(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::lt(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::lt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::lt(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::lt(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// >
PTR_Value ValueAdapter::gt(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::gt(const ValueBool& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::gt(const ValueInt& left)      const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::gt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::gt(const ValueString& left)   const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueAdapter::gt(const ValueStruct& left)   const { return PTR_Value(new ValueBool(false)); }

// !
PTR_Value ValueAdapter::logNOT(void)  const { return PTR_Value(new ValueBool(true)); }

// - (unary)
PTR_Value ValueAdapter::subUn(void)   const { return PTR_Value(new ValueNull()); }

// ++ (prefix)
PTR_Value ValueAdapter::incPre(void)  { return PTR_Value(new ValueNull()); }

// -- (prefix)
PTR_Value ValueAdapter::decPre(void)  { return PTR_Value(new ValueNull()); }

// ++ (postfix)
PTR_Value ValueAdapter::incPost(void) { return PTR_Value(new ValueNull()); }

// -- (postfix)
PTR_Value ValueAdapter::decPost(void) { return PTR_Value(new ValueNull()); }
