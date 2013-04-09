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


#include "value.h"
#include "valuenull.h"
#include "valuebool.h"
#include "valueint.h"
#include "valuefloat.h"
#include "valuestring.h"
#include "valuestruct.h"
#include "valuearray.h"
#include "logger.h"


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
CountPtr<Value> ValueInt::add(const Value& right)       const { return right.add(*this); }
CountPtr<Value> ValueInt::add(const ValueBool& left)    const { return CountPtr<Value>(new ValueInt(left.getVal() + m_val)); }
CountPtr<Value> ValueInt::add(const ValueInt& left)     const { return CountPtr<Value>(new ValueInt(left.getVal() + m_val)); }
CountPtr<Value> ValueInt::add(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() + m_val)); }

// -
CountPtr<Value> ValueInt::sub(const Value& right)       const { return right.sub(*this); }
CountPtr<Value> ValueInt::sub(const ValueBool& left)    const { return CountPtr<Value>(new ValueInt(left.getVal() - m_val)); }
CountPtr<Value> ValueInt::sub(const ValueInt& left)     const { return CountPtr<Value>(new ValueInt(left.getVal() - m_val)); }
CountPtr<Value> ValueInt::sub(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() - m_val)); }

// *
CountPtr<Value> ValueInt::mult(const Value& right)      const { return right.mult(*this); }
CountPtr<Value> ValueInt::mult(const ValueBool& left)   const { return CountPtr<Value>(new ValueInt(left.getVal() * m_val)); }
CountPtr<Value> ValueInt::mult(const ValueInt& left)    const { return CountPtr<Value>(new ValueInt(left.getVal() * m_val)); }
CountPtr<Value> ValueInt::mult(const ValueFloat& left)  const { return CountPtr<Value>(new ValueFloat(left.getVal() * m_val)); }

// /
CountPtr<Value> ValueInt::div(const Value& right)       const { return right.div(*this); }

CountPtr<Value> ValueInt::div(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueInt(left.getVal() / m_val));
	}
}

CountPtr<Value> ValueInt::div(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueInt(left.getVal() / m_val));
	}
}

CountPtr<Value> ValueInt::div(const ValueFloat& left)   const
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
CountPtr<Value> ValueInt::mod(const Value& right)       const { return right.mod(*this); }

CountPtr<Value> ValueInt::mod(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN_P(_("Division (modulo) by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueInt(left.getVal() % m_val));
	}
}

CountPtr<Value> ValueInt::mod(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN_P(_("Division (modulo) by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueInt(left.getVal() % m_val));
	}
}

CountPtr<Value> ValueInt::mod(const ValueFloat& /* left */)   const
{
	WARN_P(_("Invalid operands of types float and int to modulo operator"));
	return VALUENULL;
}

// ==
CountPtr<Value> ValueInt::eq(const Value& right)        const { return right.eq(*this); }
CountPtr<Value> ValueInt::eq(const ValueBool& left)     const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::eq(const ValueInt& left)      const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::eq(const ValueFloat& left)    const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !=
CountPtr<Value> ValueInt::ne(const Value& right)        const { return right.ne(*this); }
CountPtr<Value> ValueInt::ne(const ValueBool& left)     const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::ne(const ValueInt& left)      const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::ne(const ValueFloat& left)    const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <=
CountPtr<Value> ValueInt::le(const Value& right)        const { return right.le(*this); }
CountPtr<Value> ValueInt::le(const ValueBool& left)     const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::le(const ValueInt& left)      const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::le(const ValueFloat& left)    const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >=
CountPtr<Value> ValueInt::ge(const Value& right)        const { return right.ge(*this); }
CountPtr<Value> ValueInt::ge(const ValueBool& left)     const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::ge(const ValueInt& left)      const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::ge(const ValueFloat& left)    const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// <
CountPtr<Value> ValueInt::lt(const Value& right)        const { return right.lt(*this); }
CountPtr<Value> ValueInt::lt(const ValueBool& left)     const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::lt(const ValueInt& left)      const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::lt(const ValueFloat& left)    const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// >
CountPtr<Value> ValueInt::gt(const Value& right)        const { return right.gt(*this); }
CountPtr<Value> ValueInt::gt(const ValueBool& left)     const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::gt(const ValueInt& left)      const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueInt::gt(const ValueFloat& left)    const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// !
CountPtr<Value> ValueInt::logNOT(void)  const { return (!m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }

// - (unary)
CountPtr<Value> ValueInt::subUn(void)   const { return CountPtr<Value>(new ValueInt(-m_val)); }

CountPtr<Value> ValueInt::member(const Value& right)    const { return right.member(*this); } // .
CountPtr<Value> ValueInt::index(const Value& right)     const { return right.index(*this); } // []

CountPtr<Value> ValueInt::index(const ValueString& left) const
{
	if((unsigned int)m_val < left.getVal().length())
		return CountPtr<Value>(new ValueString(char2string(left.getVal()[m_val])));
	else
	{
		stringstream ss;
		ss << _("Index out of bounds (size: ") << left.getVal().length()
			<< _(", index: ") << m_val << _(")");
		WARN_P(ss.str());

		return VALUENULL;
	}
}


/*
TODO: ??? gcc bug ???
Tests::testValueArray()

right.index(*this) in ValueArray::index(const Value& right) calls
ValueInt::index(const Value& right)
ValueFloat::index(const Value& right)
etc.

instead of
ValueInt::index(const ValueArray& left)
ValueFloat::index(const ValueArray& left)
etc.

There is no problem with indexing of ValueString, why? It is the same!

Temporary fixed in Value::index() by dynamic_cast
*/
CountPtr<Value> ValueInt::index(const ValueArray& left) const
{
	assert("TODO: gcc bug? analyze, if called" != NULL);
	return left.getItem(m_val);
}
