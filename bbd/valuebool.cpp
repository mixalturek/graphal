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
#include "node.hpp"
#include "logger.hpp"


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

void ValueBool::dump(ostream& os, uint indent) const
{
	Node::dumpIndent(os, indent);
	os << "<ValueBool value=\"" << toString() << "\" />" << endl;
}

ostream& operator<<(ostream& os, const ValueBool& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueBool::add(const Value& right)       const { return right.add(*this); }
PTR_Value ValueBool::add(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() + m_val)); }
PTR_Value ValueBool::add(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() + m_val)); }
PTR_Value ValueBool::add(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() + m_val)); }

// -
PTR_Value ValueBool::sub(const Value& right)       const { return right.sub(*this); }
PTR_Value ValueBool::sub(const ValueBool& left)    const { return PTR_Value(new ValueBool(left.getVal() - m_val)); }
PTR_Value ValueBool::sub(const ValueInt& left)     const { return PTR_Value(new ValueInt(left.getVal() - m_val)); }
PTR_Value ValueBool::sub(const ValueFloat& left)   const { return PTR_Value(new ValueFloat(left.getVal() - m_val)); }

// *
PTR_Value ValueBool::mult(const Value& right)      const { return right.mult(*this); }
PTR_Value ValueBool::mult(const ValueBool& left)   const { return PTR_Value(new ValueBool(left.getVal() * m_val)); }
PTR_Value ValueBool::mult(const ValueInt& left)    const { return PTR_Value(new ValueInt(left.getVal() * m_val)); }
PTR_Value ValueBool::mult(const ValueFloat& left)  const { return PTR_Value(new ValueFloat(left.getVal() * m_val)); }

// /
PTR_Value ValueBool::div(const Value& right)       const { return right.div(*this); }

PTR_Value ValueBool::div(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return PTR_Value(new ValueNull());
	}
	else
	{
		return PTR_Value(new ValueBool(left.getVal() / m_val));
	}
}

PTR_Value ValueBool::div(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return PTR_Value(new ValueNull());
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() / m_val));
	}
}

PTR_Value ValueBool::div(const ValueFloat& left)   const
{
	if(m_val == 0)
	{
		WARN << _("Division by zero") << endl;
		return PTR_Value(new ValueNull());
	}
	else
	{
		return PTR_Value(new ValueFloat(left.getVal() / m_val));
	}
}

// %
PTR_Value ValueBool::mod(const Value& right)       const { return right.mod(*this); }

PTR_Value ValueBool::mod(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN << _("Division (modulo) by zero") << endl;
		return PTR_Value(new ValueNull());
	}
	else
	{
		return PTR_Value(new ValueBool(left.getVal() % m_val));
	}
}

PTR_Value ValueBool::mod(const ValueInt& left)     const
{
	if(m_val == 0)
	{
		WARN << _("Division (modulo) by zero") << endl;
		return PTR_Value(new ValueNull());
	}
	else
	{
		return PTR_Value(new ValueInt(left.getVal() % m_val));
	}
}

PTR_Value ValueBool::mod(const ValueFloat& /* left */)   const
{
	WARN << _("Invalid operands of types float and bool to modulo operator") << endl;
	return PTR_Value(new ValueNull());
}

// ==
PTR_Value ValueBool::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueBool::eq(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueBool::eq(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueBool::eq(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }

// !=
PTR_Value ValueBool::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueBool::ne(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueBool::ne(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueBool::ne(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }

// <=
PTR_Value ValueBool::le(const Value& right)        const { return right.le(*this); }
PTR_Value ValueBool::le(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueBool::le(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }
PTR_Value ValueBool::le(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() <= m_val)); }

// >=
PTR_Value ValueBool::ge(const Value& right)        const { return right.ge(*this); }
PTR_Value ValueBool::ge(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueBool::ge(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }
PTR_Value ValueBool::ge(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() >= m_val)); }

// <
PTR_Value ValueBool::lt(const Value& right)        const { return right.lt(*this); }
PTR_Value ValueBool::lt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueBool::lt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }
PTR_Value ValueBool::lt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() < m_val)); }

// >
PTR_Value ValueBool::gt(const Value& right)        const { return right.gt(*this); }
PTR_Value ValueBool::gt(const ValueBool& left)     const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueBool::gt(const ValueInt& left)      const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }
PTR_Value ValueBool::gt(const ValueFloat& left)    const { return PTR_Value(new ValueBool(left.getVal() > m_val)); }

// !
PTR_Value ValueBool::logNOT(void)  const { return PTR_Value(new ValueBool(!m_val)); }

// - (unary)
PTR_Value ValueBool::subUn(void)   const { return PTR_Value(new ValueBool(-m_val)); }

PTR_Value ValueBool::member(const Value& right)    const { return right.member(*this); } // .
PTR_Value ValueBool::index(const Value& right)     const { return right.index(*this); } // []

PTR_Value ValueBool::index(const ValueString& left) const
{
	if(m_val < left.getVal().length())
		return PTR_Value(new ValueString(char2string(left.getVal()[m_val])));
	else
	{
		WARN << _("Index out of range") << endl;
		return PTR_Value(new ValueNull());
	}
}
