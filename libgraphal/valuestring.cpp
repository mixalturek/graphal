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


/////////////////////////////////////////////////////////////////////////////
////

ValueString::ValueString(const string& val)
	: Value(),
	m_val(val)
{

}

ValueString::~ValueString()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueString::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueString value=\"" << toString() << "\" />" << endl;
}

ostream& operator<<(ostream& os, const ValueString& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

// Double dispatching not needed here
// CountPtr<Value> ValueString::add(const Value& right)     const { return right.add(*this); } // +
// CountPtr<Value> ValueString::add(const ValueString& left) const { return CountPtr<Value>(new ValueString(left.getVal() + m_val)); }
CountPtr<Value> ValueString::add(const Value& right)     const { return CountPtr<Value>(new ValueString(m_val + right.toString())); } // +

CountPtr<Value> ValueString::sub(const Value& right)     const { return right.sub(*this); } // -
CountPtr<Value> ValueString::mult(const Value& right)    const { return right.mult(*this); } // *
CountPtr<Value> ValueString::div(const Value& right)     const { return right.div(*this); } // /
CountPtr<Value> ValueString::mod(const Value& right)     const { return right.mod(*this); } // %
CountPtr<Value> ValueString::eq(const Value& right)      const { return right.eq(*this); } // ==
CountPtr<Value> ValueString::eq(const ValueString& left) const { return (left.getVal() == m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::ne(const Value& right)      const { return right.ne(*this); } // !=
CountPtr<Value> ValueString::ne(const ValueString& left) const { return (left.getVal() != m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::le(const Value& right)      const { return right.le(*this); } // <=
CountPtr<Value> ValueString::le(const ValueString& left) const { return (left.getVal() <= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::ge(const Value& right)      const { return right.ge(*this); } // >=
CountPtr<Value> ValueString::ge(const ValueString& left) const { return (left.getVal() >= m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::lt(const Value& right)      const { return right.lt(*this); } // <
CountPtr<Value> ValueString::lt(const ValueString& left) const { return (left.getVal() < m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::gt(const Value& right)      const { return right.gt(*this); } // >
CountPtr<Value> ValueString::gt(const ValueString& left) const { return (left.getVal() > m_val) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueString::member(const Value& right)  const { return right.member(*this); } // .
CountPtr<Value> ValueString::index(const Value& right)   const { return right.index(*this); } // []
CountPtr<Value> ValueString::logNOT(void)                const { return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
