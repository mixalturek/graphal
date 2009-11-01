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


#include "valueset.hpp"
#include "valuebool.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueSet::ValueSet(void)
	: Value(),
	m_data(),
	m_it(m_data.begin())
{

}

ValueSet::~ValueSet(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<ValueSet>" << endl;

	set_container::const_iterator it;
	for(it = m_data.begin(); it != m_data.end(); ++it)
		(*it)->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueSet>" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::insert(CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;

	if(contains(value))
		return;

	m_data.push_back(value);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::remove(CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;

	set_container::iterator it;
	for(it = m_data.begin(); it != m_data.end(); ++it)
	{
		if(*it == value)
		{
			m_data.erase(it);
			break;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueSet::contains(CountPtr<Value> value) const
{
	ACCESS_MUTEX_LOCKER;

	set_container::const_iterator it;
	for(it = m_data.begin(); it != m_data.end(); ++it)
	{
		if(*it == value)
			return true;
	}

	return false;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getUnion(const ValueSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_data.begin(); it != m_data.end(); ++it)
		ret->insert(*it);

	for(it = vs.m_data.begin(); it != vs.m_data.end(); it++)
		ret->insert(*it);

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getIntersection(const ValueSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_data.begin(); it != m_data.end(); ++it)
	{
		if(vs.contains(*it))
			ret->insert(*it);
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::getDifference(const ValueSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	set_container::const_iterator it;
	ValueSet* ret = new ValueSet;

	for(it = m_data.begin(); it != m_data.end(); ++it)
	{
		if(!vs.contains(*it))
			ret->insert(*it);
	}

	return CountPtr<Value>(ret);
}

/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::iterator(void) const
{
	ACCESS_MUTEX_LOCKER;
	ValueSet* tmp = new ValueSet;
	tmp->m_data = m_data;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::hasNext(void) const
{
	ACCESS_MUTEX_LOCKER;
	return (m_it == m_data.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueSet::next(void)
{
	ACCESS_MUTEX_LOCKER;
	return *(m_it++);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueSet::resetIterator(void)
{
	ACCESS_MUTEX_LOCKER;
	m_it = m_data.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueSet::add(const Value& right)        const { return right.add(*this); } // +
PTR_Value ValueSet::sub(const Value& right)        const { return right.sub(*this); } // -
PTR_Value ValueSet::mult(const Value& right)       const { return right.mult(*this); } // *
PTR_Value ValueSet::div(const Value& right)        const { return right.div(*this); } // /
PTR_Value ValueSet::mod(const Value& right)        const { return right.mod(*this); } // %
PTR_Value ValueSet::eq(const Value& right)         const { return right.eq(*this); } // ==
PTR_Value ValueSet::eq(const ValueSet& left) const { return (left.m_data == m_data) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueSet::ne(const Value& right)         const { return right.ne(*this); } // !=
PTR_Value ValueSet::ne(const ValueSet& left) const { return (left.m_data != m_data) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueSet::le(const Value& right)         const { return right.le(*this); } // <=
PTR_Value ValueSet::ge(const Value& right)         const { return right.ge(*this); } // >=
PTR_Value ValueSet::lt(const Value& right)         const { return right.lt(*this); } // <
PTR_Value ValueSet::gt(const Value& right)         const { return right.gt(*this); } // >
PTR_Value ValueSet::member(const Value& right)     const { return right.member(*this); } // .
PTR_Value ValueSet::index(const Value& right)      const { return right.index(*this); } // []
PTR_Value ValueSet::logNOT(void)                   const { ACCESS_MUTEX_LOCKER; return (m_data.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !


/////////////////////////////////////////////////////////////////////////////
////
