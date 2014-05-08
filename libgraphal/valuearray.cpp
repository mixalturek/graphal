/*
 * Copyright 2009 Michal Turek
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


#include <sstream>
#include "valuearray.h"
#include "valuebool.h"
#include "valuereference.h"
#include "valuenull.h"
#include "valueint.h"
#include "valuefloat.h"
#include "valuestruct.h"
#include "logger.h"


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
/*
string ValueArray::toString(void) const
{
	ACCESS_MUTEX_LOCKER;

	ostringstream os;
	deque< CountPtr<Value> >::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		os << (*it)->toString() << ",";

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}
*/

/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::resize(uint newsize)
{
	ACCESS_MUTEX_LOCKER;

	// All references would be the same object, assigning to a[5] causes assign to all indices
	// m_val.resize(newsize, CountPtr<Value>(new ValueReference(VALUENULL)));

	if(newsize <= m_val.size())
		return;

	// old vector code, deque does not have this method
//	m_val.reserve(newsize);

	for(uint i = m_val.size(); i < newsize; i++)
		m_val.push_back(CountPtr<Value>(new ValueReference(VALUENULL)));
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::getItem(uint pos) const
{
	ACCESS_MUTEX_LOCKER;

	if(pos < m_val.size())
		return m_val[pos];
	else
	{
		stringstream ss;
		ss << _("Index out of bounds (size: ") << m_val.size()
			<< _(", index: ") << pos << _(")");
		WARN_P(ss.str());

		return VALUENULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::setItem(uint pos, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;

	if(pos >= m_val.size())
	{
		stringstream ss;
		ss << _("Index out of bounds (size: ") << m_val.size()
			<< _(", index: ") << pos << _("), resizing array");
		WARN_P(ss.str());

		resize(pos+1);
	}

	if(val->isLValue())
		m_val[pos]->toValueReference()->assign(val->getReferredValue());
	else
		m_val[pos]->toValueReference()->assign(val);

	return val;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::pushFront(CountPtr<Value>& val)
{
	ACCESS_MUTEX_LOCKER;
	if(val->isLValue())
		m_val.push_front(CountPtr<Value>(new ValueReference(val->getReferredValue())));
	else
		m_val.push_front(CountPtr<Value>(new ValueReference(val)));
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::pushBack(CountPtr<Value>& val)
{
	ACCESS_MUTEX_LOCKER;
	if(val->isLValue())
		m_val.push_back(CountPtr<Value>(new ValueReference(val->getReferredValue())));
	else
		m_val.push_back(CountPtr<Value>(new ValueReference(val)));
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::popFront(void)
{
	ACCESS_MUTEX_LOCKER;
	if(m_val.size() != 0)
		m_val.pop_front();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::popBack(void)
{
	ACCESS_MUTEX_LOCKER;
	if(m_val.size() != 0)
		m_val.pop_back();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::front(void)
{
	ACCESS_MUTEX_LOCKER;
	return (m_val.size() == 0) ? VALUENULL : m_val.front();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::back(void)
{
	ACCESS_MUTEX_LOCKER;
	return (m_val.size() == 0) ? VALUENULL : m_val.back();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::iterator(void) const
{
	ACCESS_MUTEX_LOCKER;
	ValueArray* tmp = new ValueArray();
	tmp->m_val = m_val;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::hasNext(void) const
{
	ACCESS_MUTEX_LOCKER;
	return (m_it == m_val.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueArray::next(void)
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> ret(*m_it);
	m_it++;
	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::resetIterator(void)
{
	ACCESS_MUTEX_LOCKER;
	m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::setPropertyToAllStructItems(identifier name, CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;

	deque< CountPtr<Value> >::iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		ValueStruct* tmp = (*it)->toValueStruct();
		if(tmp != NULL)
			tmp->setItem(name, value);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

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

CountPtr<Value> ValueArray::add(const Value& right)     const { return right.add(*this); } // +
CountPtr<Value> ValueArray::sub(const Value& right)     const { return right.sub(*this); } // -
CountPtr<Value> ValueArray::mult(const Value& right)    const { return right.mult(*this); } // *
CountPtr<Value> ValueArray::div(const Value& right)     const { return right.div(*this); } // /
CountPtr<Value> ValueArray::mod(const Value& right)     const { return right.mod(*this); } // %
CountPtr<Value> ValueArray::eq(const Value& right)      const { return right.eq(*this); } // ==
CountPtr<Value> ValueArray::eq(const ValueArray& /*left*/) const { return VALUEBOOL_FALSE; }
CountPtr<Value> ValueArray::ne(const Value& right)      const { return right.ne(*this); } // !=
CountPtr<Value> ValueArray::ne(const ValueArray& /*left*/) const { return VALUEBOOL_TRUE; }
CountPtr<Value> ValueArray::le(const Value& right)      const { return right.le(*this); } // <=
CountPtr<Value> ValueArray::ge(const Value& right)      const { return right.ge(*this); } // >=
CountPtr<Value> ValueArray::lt(const Value& right)      const { return right.lt(*this); } // <
CountPtr<Value> ValueArray::gt(const Value& right)      const { return right.gt(*this); } // >
CountPtr<Value> ValueArray::member(const Value& right)  const { return right.member(*this); } // .

/*
// TODO: ??? gcc bug ???
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
CountPtr<Value> ValueArray::index(const Value& right)   const { return right.index(*this); } // []

CountPtr<Value> ValueArray::logNOT(void)                const { ACCESS_MUTEX_LOCKER; return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !


/////////////////////////////////////////////////////////////////////////////
////

deque< CountPtr<Value> > ValueArray::getVal(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_val;
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueArray::toBool(void) const
{
	ACCESS_MUTEX_LOCKER;
	return !m_val.empty();
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueArray::getSize(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_val.size();
}
