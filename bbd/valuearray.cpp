/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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


#include <sstream>
#include "valuearray.hpp"
#include "valuebool.hpp"
#include "valuereference.hpp"
#include "valuenull.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueArray::ValueArray()
	: Value(),
	m_val(),
	m_it(m_val.begin())
{

}

ValueArray::ValueArray(uint size)
	: Value(),
	m_val()
{
	resize(size);
}

ValueArray::~ValueArray()
{

}


/////////////////////////////////////////////////////////////////////////////
////

string ValueArray::toString(void) const
{
	ostringstream os;
	deque< CountPtr<Value> >::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		os << (*it)->toString() << ",";

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::resize(uint newsize)
{
	// All references are the same object, assigning to a[5] causes assign to all indices
	// m_val.resize(newsize, CountPtr<Value>(new ValueReference(VALUENULL)));

	if(newsize <= m_val.size())
		return;

	// old vector code, deque does not have this method
//	m_val.reserve(newsize);

	for(uint i = m_val.size(); i < newsize; i++)
		m_val.push_back(CountPtr<Value>(new ValueReference(VALUENULL)));
}


CountPtr<Value> ValueArray::getItem(uint pos) const
{
	if(pos < m_val.size())
		return m_val[pos];
	else
	{
		WARN << _("Index out of bounds (size: ") << m_val.size()
			<< _(", index: ") << pos << ")" << endl;
		return VALUENULL;
	}
}

CountPtr<Value> ValueArray::setItem(uint pos, CountPtr<Value> val)
{
	if(pos >= m_val.size())
	{
		WARN << _("Index out of bounds (size: ") << m_val.size()
			<< _(", index: ") << pos << _("), resizing array") << endl;
		resize(pos+1);
	}

	if(val->isLValue())
	{
		m_val[pos]->toValueReference()->assign(val->getReferredValue());
		return val;
	}
	else
	{
		m_val[pos]->toValueReference()->assign(val);
		return val;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::pushFront(CountPtr<Value>& val)
{
	if(val->isLValue())
		m_val.push_front(CountPtr<Value>(new ValueReference(val->getReferredValue())));
	else
		m_val.push_front(CountPtr<Value>(new ValueReference(val)));
}

void ValueArray::pushBack(CountPtr<Value>& val)
{
	if(val->isLValue())
		m_val.push_back(CountPtr<Value>(new ValueReference(val->getReferredValue())));
	else
		m_val.push_back(CountPtr<Value>(new ValueReference(val)));
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::iterator(void) const
{
	ValueArray* tmp = new ValueArray();
	tmp->m_val = m_val;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}

CountPtr<Value> ValueArray::hasNext(void) const
{
	return (m_it == m_val.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}

CountPtr<Value> ValueArray::next(void)
{
	CountPtr<Value> ret(*m_it);
	m_it++;
	return ret;
}

void ValueArray::resetIterator(void)
{
	m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueArray>" << endl;

	deque< CountPtr<Value> >::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); it++)
		(*it)->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueArray>" << endl;
}

ostream& operator<<(ostream& os, const ValueArray& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueArray::add(const Value& right)     const { return right.add(*this); } // +
PTR_Value ValueArray::sub(const Value& right)     const { return right.sub(*this); } // -
PTR_Value ValueArray::mult(const Value& right)    const { return right.mult(*this); } // *
PTR_Value ValueArray::div(const Value& right)     const { return right.div(*this); } // /
PTR_Value ValueArray::mod(const Value& right)     const { return right.mod(*this); } // %
PTR_Value ValueArray::eq(const Value& right)      const { return right.eq(*this); } // ==
PTR_Value ValueArray::eq(const ValueArray& /*left*/) const { return VALUEBOOL_FALSE; }
PTR_Value ValueArray::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueArray::ne(const ValueArray& /*left*/) const { return VALUEBOOL_TRUE; }
PTR_Value ValueArray::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueArray::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueArray::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueArray::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueArray::member(const Value& right)  const { return right.member(*this); } // .

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
PTR_Value ValueArray::index(const Value& right)   const { return right.index(*this); } // []

PTR_Value ValueArray::logNOT(void)                const { return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
