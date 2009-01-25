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

ValueInt::ValueInt(int val)
	: Value(),
	m_val(val)
{

}


ValueInt::~ValueInt()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueInt::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueInt value=\"" << toString() << "\" />" << endl;
}

ostream& operator<<(ostream& os, const ValueInt& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueInt::add(const Value& right)       const { return right.add(*this); }
PTR_Value ValueInt::add(const ValueBool& left)    const { return PTR_Value(new ValueInt(left.getVal() + m_val)); }
PTR_Value ValueInt::add(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() + m_val)); }
PTR_Value ValueInt::add(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }

// -
PTR_Value ValueInt::sub(const Value& right)       const { return right.sub(*this); }
PTR_Value ValueInt::sub(const ValueBool& left)    const { return PTR_Value(new ValueInt(left.getVal() - m_val)); }
PTR_Value ValueInt::sub(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() - m_val)); }
PTR_Value ValueInt::sub(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }

// *
PTR_Value ValueInt::mult(const Value& right)      const { return right.mult(*this); }
PTR_Value ValueInt::mult(const ValueBool& left)   const { return PTR_Value(new ValueInt(left.getVal() * m_val)); }
PTR_Value ValueInt::mult(const ValueInt& left)    const { return PTR_Value(new ValueInt(left.getVal() * m_val)); }
PTR_Value ValueInt::mult(const ValueFloat& left)  const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }

// /
PTR_Value ValueInt::div(const Value& right)       const { return right.div(*this); }

PTR_Value ValueInt::div(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return VALUENULL;
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() / m_val));
	}
}

PTR_Value ValueInt::div(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return VALUENULL;
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() / m_val));
	}
}

PTR_Value ValueInt::div(const ValueFloat& left)   const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return VALUENULL;
	}
	else
	{
		return PTR_Value(new ValueFloat(left.getVal() / m_val));
	}
}

// %
PTR_Value ValueInt::mod(const Value& right)       const { return right.mod(*this); }

PTR_Value ValueInt::mod(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN << _("Division (modulo) by zero") << endl;
		return VALUENULL;
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() % m_val));
	}
}

PTR_Value ValueInt::mod(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN << _("Division (modulo) by zero") << endl;
		return VALUENULL;
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() % m_val));
	}
}

PTR_Value ValueInt::mod(const ValueFloat& /* left */)   const
{
	WARN << _("Invalid operands of types float and int to modulo operator") << endl;
	return VALUENULL;
}

// ==
PTR_Value ValueInt::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueInt::eq(const ValueBool& left)     const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::eq(const ValueInt& left)      const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::eq(const ValueFloat& left)    const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !=
PTR_Value ValueInt::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueInt::ne(const ValueBool& left)     const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::ne(const ValueInt& left)      const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::ne(const ValueFloat& left)    const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <=
PTR_Value ValueInt::le(const Value& right)        const { return right.le(*this); }
PTR_Value ValueInt::le(const ValueBool& left)     const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::le(const ValueInt& left)      const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::le(const ValueFloat& left)    const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >=
PTR_Value ValueInt::ge(const Value& right)        const { return right.ge(*this); }
PTR_Value ValueInt::ge(const ValueBool& left)     const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::ge(const ValueInt& left)      const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::ge(const ValueFloat& left)    const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <
PTR_Value ValueInt::lt(const Value& right)        const { return right.lt(*this); }
PTR_Value ValueInt::lt(const ValueBool& left)     const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::lt(const ValueInt& left)      const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::lt(const ValueFloat& left)    const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >
PTR_Value ValueInt::gt(const Value& right)        const { return right.gt(*this); }
PTR_Value ValueInt::gt(const ValueBool& left)     const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::gt(const ValueInt& left)      const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueInt::gt(const ValueFloat& left)    const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !
PTR_Value ValueInt::logNOT(void)  const { return (!m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// - (unary)
PTR_Value ValueInt::subUn(void)   const { return PTR_Value(new ValueInt(-m_val)); }

PTR_Value ValueInt::member(const Value& right)    const { return right.member(*this); } // .
PTR_Value ValueInt::index(const Value& right)     const { return right.index(*this); } // []

PTR_Value ValueInt::index(const ValueString& left) const
{
	if((unsigned int)m_val < left.getVal().length())
		return PTR_Value(new ValueString(char2string(left.getVal()[m_val])));
	else
	{
		WARN << _("Index out of bounds (size: ") << left.getVal().length()
			<< _(", index: ") << m_val << ")" << endl;
		return VALUENULL;
	}
}

PTR_Value ValueInt::index(const ValueArray& left) const { return left.getItem(m_val); }
