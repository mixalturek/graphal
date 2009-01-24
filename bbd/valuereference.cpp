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


#include "valuereference.hpp"
#include "valuebool.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueReference::ValueReference(Value* val)
	: Value(),
	m_val(val)
{
	assert(m_val != NULL);
}


ValueReference::~ValueReference()
{
	// Don't delete m_val, ValueReference is not the owner
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueReference::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueReference>" << endl;

	m_val->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueReference>" << endl;
}

ostream& operator<<(ostream& os, const ValueReference& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueReference::add(const Value& right)        const { return right.add(*this); } // +
PTR_Value ValueReference::sub(const Value& right)        const { return right.sub(*this); } // -
PTR_Value ValueReference::mult(const Value& right)       const { return right.mult(*this); } // *
PTR_Value ValueReference::div(const Value& right)        const { return right.div(*this); } // /
PTR_Value ValueReference::mod(const Value& right)        const { return right.mod(*this); } // %
PTR_Value ValueReference::eq(const Value& right)         const { return right.eq(*this); } // ==
PTR_Value ValueReference::ne(const Value& right)         const { return right.ne(*this); } // !=
PTR_Value ValueReference::le(const Value& right)         const { return right.le(*this); } // <=
PTR_Value ValueReference::ge(const Value& right)         const { return right.ge(*this); } // >=
PTR_Value ValueReference::lt(const Value& right)         const { return right.lt(*this); } // <
PTR_Value ValueReference::gt(const Value& right)         const { return right.gt(*this); } // >
PTR_Value ValueReference::member(const Value& right)     const { return right.member(*this); } // .
PTR_Value ValueReference::index(const Value& right)      const { return right.index(*this); } // []
PTR_Value ValueReference::logNOT(void)                   const { return m_val->logNOT(); } // !
