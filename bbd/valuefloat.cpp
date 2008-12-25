/*
 *      valuefloat.cpp
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

ValueFloat::ValueFloat(float val)
	: Value(),
	m_val(val)
{

}


ValueFloat::~ValueFloat()
{

}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueFloat::execute(Context& context)
{
	return PTR_Value(new ValueFloat(m_val));
}

void ValueFloat::dump(ostream& os, uint indent) const
{
	this->dumpIndent(os, indent);
	os << "<ValueFloat value=\"" << toString() << "\" />" << endl;
}

ostream& operator<<(ostream& os, const ValueFloat& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueFloat::add(const Value& right)       const { return right.add(*this); }
PTR_Value ValueFloat::add(const ValueBool& left)    const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }
PTR_Value ValueFloat::add(const ValueInt& left)     const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }
PTR_Value ValueFloat::add(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }

// -
PTR_Value ValueFloat::sub(const Value& right)       const { return right.sub(*this); }
PTR_Value ValueFloat::sub(const ValueBool& left)    const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }
PTR_Value ValueFloat::sub(const ValueInt& left)     const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }
PTR_Value ValueFloat::sub(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }

// *
PTR_Value ValueFloat::mult(const Value& right)      const { return right.mult(*this); }
PTR_Value ValueFloat::mult(const ValueBool& left)   const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }
PTR_Value ValueFloat::mult(const ValueInt& left)    const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }
PTR_Value ValueFloat::mult(const ValueFloat& left)  const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }

// /
PTR_Value ValueFloat::div(const Value& right)       const { return right.div(*this); }
PTR_Value ValueFloat::div(const ValueBool& left)    const { return PTR_Value(new ValueFloat(left.getVal() / m_val)); }
PTR_Value ValueFloat::div(const ValueInt& left)     const { return PTR_Value(new ValueFloat(left.getVal() / m_val)); }
PTR_Value ValueFloat::div(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() / m_val)); }

// %
PTR_Value ValueFloat::mod(const Value& right)       const { return right.mod(*this); }
// TODO: error: invalid operands of types 'bool' and 'const float' to binary 'operator%'
PTR_Value ValueFloat::mod(const ValueBool& left)    const { return PTR_Value(new ValueNull()); }
// TODO: error: invalid operands of types 'int' and 'const float' to binary 'operator%'
PTR_Value ValueFloat::mod(const ValueInt& left)     const { return PTR_Value(new ValueNull()); }
// TODO: error: invalid operands of types 'double' and 'int' to binary 'operator%'
PTR_Value ValueFloat::mod(const ValueFloat& left)   const { return PTR_Value(new ValueNull()); }

// ==
PTR_Value ValueFloat::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueFloat::eq(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueFloat::eq(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueFloat::eq(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }

// !=
PTR_Value ValueFloat::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueFloat::ne(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueFloat::ne(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueFloat::ne(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }

// <=
PTR_Value ValueFloat::le(const Value& right)        const { return right.le(*this); }
PTR_Value ValueFloat::le(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueFloat::le(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueFloat::le(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }

// >=
PTR_Value ValueFloat::ge(const Value& right)        const { return right.ge(*this); }
PTR_Value ValueFloat::ge(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueFloat::ge(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueFloat::ge(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }

// <
PTR_Value ValueFloat::lt(const Value& right)        const { return right.lt(*this); }
PTR_Value ValueFloat::lt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueFloat::lt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueFloat::lt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }

// >
PTR_Value ValueFloat::gt(const Value& right)        const { return right.gt(*this); }
PTR_Value ValueFloat::gt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueFloat::gt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueFloat::gt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }

// !
PTR_Value ValueFloat::logNOT(void)  const { return PTR_Value(new ValueBool(!m_val)); }

// - (unary)
PTR_Value ValueFloat::subUn(void)   const { return PTR_Value(new ValueFloat(-m_val)); }
