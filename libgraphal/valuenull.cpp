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

void ValueNull::initInstance(void)
{
	m_instance = new CountPtr<Value>(new ValueNull);
}

void ValueNull::destroyInstance(void)
{
	delete m_instance;
	m_instance = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueNull::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueNull />" << endl;
}

ostream& operator<<(ostream& os, const ValueNull& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueNull::add(const Value& right)   const { return right.add(*this); } // +
CountPtr<Value> ValueNull::sub(const Value& right)   const { return right.sub(*this); } // -
CountPtr<Value> ValueNull::mult(const Value& right)  const { return right.mult(*this); } // *
CountPtr<Value> ValueNull::div(const Value& right)   const { return right.div(*this); } // /
CountPtr<Value> ValueNull::mod(const Value& right)   const { return right.mod(*this); } // %
CountPtr<Value> ValueNull::eq(const Value& right)    const { return right.eq(*this); } // ==
CountPtr<Value> ValueNull::eq(const ValueNull& /* left */) const { return VALUEBOOL_TRUE; }
CountPtr<Value> ValueNull::ne(const Value& right)    const { return right.ne(*this); } // !=
CountPtr<Value> ValueNull::ne(const ValueNull& /* left */) const { return VALUEBOOL_FALSE; }
CountPtr<Value> ValueNull::le(const Value& right)    const { return right.le(*this); } // <=
CountPtr<Value> ValueNull::ge(const Value& right)    const { return right.ge(*this); } // >=
CountPtr<Value> ValueNull::lt(const Value& right)    const { return right.lt(*this); } // <
CountPtr<Value> ValueNull::gt(const Value& right)    const { return right.gt(*this); } // >
CountPtr<Value> ValueNull::member(const Value& right) const { return right.member(*this); } // .
CountPtr<Value> ValueNull::index(const Value& right) const { return right.index(*this); } // []
CountPtr<Value> ValueNull::logNOT(void)              const { return VALUEBOOL_TRUE; } // !
