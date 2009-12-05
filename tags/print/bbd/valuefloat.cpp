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


#include "value.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "valuestring.hpp"
#include "valuestruct.hpp"
#include "valuearray.hpp"
#include "logger.hpp"


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

void ValueFloat::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
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
CountPtr<Value> ValueFloat::add(const Value& right)       const { return right.add(*this); }
CountPtr<Value> ValueFloat::add(const ValueBool& left)    const { return CountPtr<Value>(new ValueFloat(left.getVal() + m_val)); }
CountPtr<Value> ValueFloat::add(const ValueInt& left)     const { return CountPtr<Value>(new ValueFloat(left.getVal() + m_val)); }
CountPtr<Value> ValueFloat::add(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() + m_val)); }

// -
CountPtr<Value> ValueFloat::sub(const Value& right)       const { return right.sub(*this); }
CountPtr<Value> ValueFloat::sub(const ValueBool& left)    const { return CountPtr<Value>(new ValueFloat(left.getVal() - m_val)); }
CountPtr<Value> ValueFloat::sub(const ValueInt& left)     const { return CountPtr<Value>(new ValueFloat(left.getVal() - m_val)); }
CountPtr<Value> ValueFloat::sub(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() - m_val)); }

// *
CountPtr<Value> ValueFloat::mult(const Value& right)      const { return right.mult(*this); }
CountPtr<Value> ValueFloat::mult(const ValueBool& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() * m_val)); }
CountPtr<Value> ValueFloat::mult(const ValueInt& left)    const { return CountPtr<Value>(new ValueFloat(left.getVal() * m_val)); }
CountPtr<Value> ValueFloat::mult(const ValueFloat& left)  const { return CountPtr<Value>(new ValueFloat(left.getVal() * m_val)); }

// /
CountPtr<Value> ValueFloat::div(const Value& right)       const { return right.div(*this); }

CountPtr<Value> ValueFloat::div(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueFloat(left.getVal() / m_val));
	}
}

CountPtr<Value> ValueFloat::div(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueFloat(left.getVal() / m_val));
	}
}

CountPtr<Value> ValueFloat::div(const ValueFloat& left)   const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueFloat(left.getVal() / m_val));
	}
}

// %
CountPtr<Value> ValueFloat::mod(const Value& right)       const { return right.mod(*this); }

CountPtr<Value> ValueFloat::mod(const ValueBool& /* left */)    const
{
	WARN_P(_("Invalid operands of types bool and float to modulo operator"));
	return VALUENULL;
}

CountPtr<Value> ValueFloat::mod(const ValueInt& /* left */)     const
{
	WARN_P(_("Invalid operands of types int and float to modulo operator"));
	return VALUENULL;
}

CountPtr<Value> ValueFloat::mod(const ValueFloat& /* left */)   const
{
	WARN_P(_("Invalid operands of types float and float to modulo operator"));
	return VALUENULL;
}

// ==
CountPtr<Value> ValueFloat::eq(const Value& right)        const { return right.eq(*this); }
CountPtr<Value> ValueFloat::eq(const ValueBool& left)     const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::eq(const ValueInt& left)      const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::eq(const ValueFloat& left)    const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !=
CountPtr<Value> ValueFloat::ne(const Value& right)        const { return right.ne(*this); }
CountPtr<Value> ValueFloat::ne(const ValueBool& left)     const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::ne(const ValueInt& left)      const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::ne(const ValueFloat& left)    const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <=
CountPtr<Value> ValueFloat::le(const Value& right)        const { return right.le(*this); }
CountPtr<Value> ValueFloat::le(const ValueBool& left)     const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::le(const ValueInt& left)      const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::le(const ValueFloat& left)    const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >=
CountPtr<Value> ValueFloat::ge(const Value& right)        const { return right.ge(*this); }
CountPtr<Value> ValueFloat::ge(const ValueBool& left)     const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::ge(const ValueInt& left)      const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::ge(const ValueFloat& left)    const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <
CountPtr<Value> ValueFloat::lt(const Value& right)        const { return right.lt(*this); }
CountPtr<Value> ValueFloat::lt(const ValueBool& left)     const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::lt(const ValueInt& left)      const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::lt(const ValueFloat& left)    const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >
CountPtr<Value> ValueFloat::gt(const Value& right)        const { return right.gt(*this); }
CountPtr<Value> ValueFloat::gt(const ValueBool& left)     const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::gt(const ValueInt& left)      const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueFloat::gt(const ValueFloat& left)    const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !
CountPtr<Value> ValueFloat::logNOT(void)  const { return (!m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// - (unary)
CountPtr<Value> ValueFloat::subUn(void)   const { return CountPtr<Value>(new ValueFloat(-m_val)); }

CountPtr<Value> ValueFloat::member(const Value& right)    const { return right.member(*this); } // .
CountPtr<Value> ValueFloat::index(const Value& right)     const { return right.index(*this); } // []

CountPtr<Value> ValueFloat::index(const ValueString& left) const
{
	if(m_val < left.getVal().length())
		return CountPtr<Value>(new ValueString(char2string(left.getVal()[(uint)m_val])));
	else
	{
		stringstream ss;
		ss << _("Index out of bounds (size: ") << left.getVal().length()
			<< _(", index: ") << m_val << ")";
		WARN_P(ss.str());

		return VALUENULL;
	}
}

CountPtr<Value> ValueFloat::index(const ValueArray& left) const { return left.getItem((uint)m_val); }
