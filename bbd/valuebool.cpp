/*
 *      valuebool.cpp
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

ValueBool::ValueBool(bool val)
	: Value(),
	m_val(val)
{

}


ValueBool::~ValueBool()
{

}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueBool::add(const Value& right)       const { return right.add(*this); }
PTR_Value ValueBool::add(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::add(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() + m_val)); }
PTR_Value ValueBool::add(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() + m_val)); }
PTR_Value ValueBool::add(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }
PTR_Value ValueBool::add(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::add(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// -
PTR_Value ValueBool::sub(const Value& right)       const { return right.sub(*this); }
PTR_Value ValueBool::sub(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::sub(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() - m_val)); }
PTR_Value ValueBool::sub(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() - m_val)); }
PTR_Value ValueBool::sub(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }
PTR_Value ValueBool::sub(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::sub(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// *
PTR_Value ValueBool::mult(const Value& right)      const { return right.mult(*this); }
PTR_Value ValueBool::mult(const ValueNull& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::mult(const ValueBool& left)   const { return PTR_Value(new ValueBool(left.getVal() * m_val)); }
PTR_Value ValueBool::mult(const ValueInt& left)    const { return PTR_Value(new ValueInt(left.getVal() * m_val)); }
PTR_Value ValueBool::mult(const ValueFloat& left)  const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }
PTR_Value ValueBool::mult(const ValueString& left) const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::mult(const ValueStruct& left) const { return PTR_Value(new ValueNull()); }

// /
PTR_Value ValueBool::div(const Value& right)       const { return right.div(*this); }
PTR_Value ValueBool::div(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::div(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() / m_val)); }
PTR_Value ValueBool::div(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() / m_val)); }
PTR_Value ValueBool::div(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() / m_val)); }
PTR_Value ValueBool::div(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::div(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// %
PTR_Value ValueBool::mod(const Value& right)       const { return right.mod(*this); }
PTR_Value ValueBool::mod(const ValueNull& left)    const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::mod(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() % m_val)); }
PTR_Value ValueBool::mod(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() % m_val)); }
PTR_Value ValueBool::mod(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); } // TODO: error: invalid operands of types 'double' and 'int' to binary 'operator%'
PTR_Value ValueBool::mod(const ValueString& left)  const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::mod(const ValueStruct& left)  const { return PTR_Value(new ValueNull()); }

// ==
PTR_Value ValueBool::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueBool::eq(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::eq(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueBool::eq(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueBool::eq(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueBool::eq(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::eq(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// !=
PTR_Value ValueBool::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueBool::ne(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::ne(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueBool::ne(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueBool::ne(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueBool::ne(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::ne(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// <=
PTR_Value ValueBool::le(const Value& right)        const { return right.le(*this); }
PTR_Value ValueBool::le(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::le(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueBool::le(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueBool::le(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueBool::le(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::le(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// >=
PTR_Value ValueBool::ge(const Value& right)        const { return right.ge(*this); }
PTR_Value ValueBool::ge(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::ge(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueBool::ge(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueBool::ge(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueBool::ge(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::ge(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// <
PTR_Value ValueBool::lt(const Value& right)        const { return right.lt(*this); }
PTR_Value ValueBool::lt(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::lt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueBool::lt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueBool::lt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueBool::lt(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::lt(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// >
PTR_Value ValueBool::gt(const Value& right)        const { return right.gt(*this); }
PTR_Value ValueBool::gt(const ValueNull& left)     const { return PTR_Value(new ValueBool(false)); }
PTR_Value ValueBool::gt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueBool::gt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueBool::gt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueBool::gt(const ValueString& left)   const { return PTR_Value(new ValueNull()); }
PTR_Value ValueBool::gt(const ValueStruct& left)   const { return PTR_Value(new ValueNull()); }

// !
PTR_Value ValueBool::logNOT(void)  const { return PTR_Value(new ValueBool(!m_val)); }

// - (unary)
PTR_Value ValueBool::subUn(void)   const { return PTR_Value(new ValueBool(-m_val)); }

// ++ (prefix)
PTR_Value ValueBool::incPre(void)  { return PTR_Value(new ValueBool(++m_val)); } // TODO: gcc: no error (???)

// -- (prefix)
PTR_Value ValueBool::decPre(void)  { return PTR_Value(new ValueNull()); } // TODO: error: invalid use of '--' on bool variable 'bval'

// ++ (postfix)
PTR_Value ValueBool::incPost(void) { return PTR_Value(new ValueBool(m_val++)); } // TODO: gcc: no error (???)

// -- (postfix)
PTR_Value ValueBool::decPost(void) { return PTR_Value(new ValueNull()); } // TODO: error: invalid use of '--' on bool variable 'bval'
