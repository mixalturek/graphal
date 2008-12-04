/*
 *      valuenull.cpp
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


#include "value.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueNull::ValueNull()
	: Value()
{

}


ValueNull::~ValueNull()
{

}


/////////////////////////////////////////////////////////////////////////////
////

// TODO: "Warning: Operation argument is NULL variable"

// +
PTR_Value ValueNull::add(const Value& right)       const { return right.add(*this); }

// -
PTR_Value ValueNull::sub(const Value& right)       const { return right.sub(*this); }

// *
PTR_Value ValueNull::mult(const Value& right)      const { return right.mult(*this); }

// /
PTR_Value ValueNull::div(const Value& right)       const { return right.div(*this); }

// %
PTR_Value ValueNull::mod(const Value& right)       const { return right.mod(*this); }

// ==
PTR_Value ValueNull::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueNull::eq(const ValueNull& left)     const { return PTR_Value(new ValueBool(true)); }

// !=
PTR_Value ValueNull::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueNull::ne(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }

// <=
PTR_Value ValueNull::le(const Value& right)        const { return right.le(*this); }

// >=
PTR_Value ValueNull::ge(const Value& right)        const { return right.ge(*this); }

// <
PTR_Value ValueNull::lt(const Value& right)        const { return right.lt(*this); }

// >
PTR_Value ValueNull::gt(const Value& right)        const { return right.gt(*this); }

// !
PTR_Value ValueNull::logNOT(void)                  const { return PTR_Value(new ValueBool(true)); }
