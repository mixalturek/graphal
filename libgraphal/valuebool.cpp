/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
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

void ValueBool::initInstance(void)
{
	m_instance_true = new CountPtr<Value>(new ValueBool(true));
	m_instance_false = new CountPtr<Value>(new ValueBool(false));
}

void ValueBool::destroyInstance(void)
{
	delete m_instance_true;
	m_instance_true = NULL;

	delete m_instance_false;
	m_instance_false = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueBool::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
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
CountPtr<Value> ValueBool::add(const Value& right)       const { return right.add(*this); }
CountPtr<Value> ValueBool::add(const ValueBool& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() + m_val)); }
CountPtr<Value> ValueBool::add(const ValueInt& left)     const { return CountPtr<Value>(new ValueInt(left.getVal() + m_val)); }
CountPtr<Value> ValueBool::add(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() + m_val)); }

// -
CountPtr<Value> ValueBool::sub(const Value& right)       const { return right.sub(*this); }
CountPtr<Value> ValueBool::sub(const ValueBool& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() - m_val)); }
CountPtr<Value> ValueBool::sub(const ValueInt& left)     const { return CountPtr<Value>(new ValueInt(left.getVal() - m_val)); }
CountPtr<Value> ValueBool::sub(const ValueFloat& left)   const { return CountPtr<Value>(new ValueFloat(left.getVal() - m_val)); }

// *
CountPtr<Value> ValueBool::mult(const Value& right)      const { return right.mult(*this); }
CountPtr<Value> ValueBool::mult(const ValueBool& left)   const { return CountPtr<Value>(new ValueBool(left.getVal() * m_val)); }
CountPtr<Value> ValueBool::mult(const ValueInt& left)    const { return CountPtr<Value>(new ValueInt(left.getVal() * m_val)); }
CountPtr<Value> ValueBool::mult(const ValueFloat& left)  const { return CountPtr<Value>(new ValueFloat(left.getVal() * m_val)); }

// /
CountPtr<Value> ValueBool::div(const Value& right)       const { return right.div(*this); }

CountPtr<Value> ValueBool::div(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN_P(_("Division by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueBool(left.getVal() / m_val));
	}
}

CountPtr<Value> ValueBool::div(const ValueInt& left)     const
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

CountPtr<Value> ValueBool::div(const ValueFloat& left)   const
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
CountPtr<Value> ValueBool::mod(const Value& right)       const { return right.mod(*this); }

CountPtr<Value> ValueBool::mod(const ValueBool& left)    const
{
	if(m_val == 0)
	{
		WARN_P(_("Division (modulo) by zero"));
		return VALUENULL;
	}
	else
	{
		return CountPtr<Value>(new ValueBool(left.getVal() % m_val));
	}
}

CountPtr<Value> ValueBool::mod(const ValueInt& left)     const
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

CountPtr<Value> ValueBool::mod(const ValueFloat& /* left */)   const
{
	WARN_P(_("Invalid operands of types float and bool to modulo operator"));
	return VALUENULL;
}

// ==
CountPtr<Value> ValueBool::eq(const Value& right)        const { return right.eq(*this); }
CountPtr<Value> ValueBool::eq(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() == m_val)); }
CountPtr<Value> ValueBool::eq(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() == m_val)); }
CountPtr<Value> ValueBool::eq(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() == m_val)); }

// !=
CountPtr<Value> ValueBool::ne(const Value& right)        const { return right.ne(*this); }
CountPtr<Value> ValueBool::ne(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() != m_val)); }
CountPtr<Value> ValueBool::ne(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() != m_val)); }
CountPtr<Value> ValueBool::ne(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() != m_val)); }

// <=
CountPtr<Value> ValueBool::le(const Value& right)        const { return right.le(*this); }
CountPtr<Value> ValueBool::le(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() <= m_val)); }
CountPtr<Value> ValueBool::le(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() <= m_val)); }
CountPtr<Value> ValueBool::le(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() <= m_val)); }

// >=
CountPtr<Value> ValueBool::ge(const Value& right)        const { return right.ge(*this); }
CountPtr<Value> ValueBool::ge(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() >= m_val)); }
CountPtr<Value> ValueBool::ge(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() >= m_val)); }
CountPtr<Value> ValueBool::ge(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() >= m_val)); }

// <
CountPtr<Value> ValueBool::lt(const Value& right)        const { return right.lt(*this); }
CountPtr<Value> ValueBool::lt(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() < m_val)); }
CountPtr<Value> ValueBool::lt(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() < m_val)); }
CountPtr<Value> ValueBool::lt(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() < m_val)); }

// >
CountPtr<Value> ValueBool::gt(const Value& right)        const { return right.gt(*this); }
CountPtr<Value> ValueBool::gt(const ValueBool& left)     const { return CountPtr<Value>(new ValueBool(left.getVal() > m_val)); }
CountPtr<Value> ValueBool::gt(const ValueInt& left)      const { return CountPtr<Value>(new ValueBool(left.getVal() > m_val)); }
CountPtr<Value> ValueBool::gt(const ValueFloat& left)    const { return CountPtr<Value>(new ValueBool(left.getVal() > m_val)); }

// !
CountPtr<Value> ValueBool::logNOT(void)  const { return CountPtr<Value>(new ValueBool(!m_val)); }

// - (unary)
CountPtr<Value> ValueBool::subUn(void)   const { return CountPtr<Value>(new ValueBool(-m_val)); }

CountPtr<Value> ValueBool::member(const Value& right)    const { return right.member(*this); } // .
CountPtr<Value> ValueBool::index(const Value& right)     const { return right.index(*this); } // []

CountPtr<Value> ValueBool::index(const ValueString& left) const
{
	if(m_val < left.getVal().length())
		return CountPtr<Value>(new ValueString(char2string(left.getVal()[m_val])));
	else
	{
		stringstream ss;
		ss << _("Index out of bounds (size: ") << left.getVal().length()
			<< _(", index: ") << m_val << ")";
		WARN_P(ss.str());

		return VALUENULL;
	}
}

CountPtr<Value> ValueBool::index(const ValueArray& left) const { return left.getItem(m_val); }
