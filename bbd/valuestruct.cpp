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


#include <sstream>
#include "valuestruct.hpp"
#include "valuebool.hpp"
#include "valuereference.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueStruct::ValueStruct(void)
	: Value(),
	m_val(),
	m_it()
{

}

ValueStruct::~ValueStruct(void)
{

}

void ValueStruct::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	m_val.clear();
	resetIterator();
}


/////////////////////////////////////////////////////////////////////////////
////
/*
string ValueStruct::toString(void) const
{
	ACCESS_MUTEX_LOCKER;
	ostringstream os;
	map<identifier, CountPtr<Value> >::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		os << ID2STR(it->first) << "=" << it->second->toString() << ",";

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}
*/

/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::setItem(identifier name, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);
	if(it != m_val.end())
		m_val.erase(it);

	if(val->isLValue())
		m_val.insert(pair<identifier, CountPtr<Value> >(name,
			CountPtr<Value>(new ValueReference(val->getReferredValue()))));
	else
		m_val.insert(pair<identifier, CountPtr<Value> >(name,
			CountPtr<Value>(new ValueReference(val))));

	return val;
}


CountPtr<Value> ValueStruct::getItem(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);

	if(it != m_val.end())
		return it->second;
	else
		return m_val.insert(pair<identifier, CountPtr<Value> >(name,
			CountPtr<Value>(new ValueReference(VALUENULL)))).first->second;
}

bool ValueStruct::isItemSet(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	return m_val.count(name);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::iterator(void) const
{
	ACCESS_MUTEX_LOCKER;
	ValueStruct* tmp = new ValueStruct;
	tmp->m_val = m_val;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}

CountPtr<Value> ValueStruct::hasNext(void) const
{
	ACCESS_MUTEX_LOCKER;
	return (m_it == m_val.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}

CountPtr<Value> ValueStruct::next(void)
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> ret(m_it->second);
	m_it++;
	return ret;
}

void ValueStruct::resetIterator(void)
{
	ACCESS_MUTEX_LOCKER;
	m_it = m_val.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::setPropertyToAllStructItems(identifier name, CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;

	map<identifier, CountPtr<Value> >::iterator it;
	for(it = m_val.begin(); it != m_val.end(); ++it)
	{
		ValueStruct* tmp = (*it).second->toValueStruct();
		if(tmp != NULL)
			tmp->setItem(name, value);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;
	dumpIndent(os, indent);
	os << "<ValueStruct>" << endl;

	map<identifier, CountPtr<Value> >::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); it++)
	{
		dumpIndent(os, indent+1);
		os << "<Item name=\"" << ID2STR(it->first) << "\">" << endl;
		it->second->dump(os, indent+2);
		dumpIndent(os, indent+1);
		os << "</Item>" << endl;
	}

	dumpIndent(os, indent);
	os << "</ValueStruct>" << endl;
}

ostream& operator<<(ostream& os, const ValueStruct& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueStruct::add(const Value& right)     const { return right.add(*this); } // +
PTR_Value ValueStruct::sub(const Value& right)     const { return right.sub(*this); } // -
PTR_Value ValueStruct::mult(const Value& right)    const { return right.mult(*this); } // *
PTR_Value ValueStruct::div(const Value& right)     const { return right.div(*this); } // /
PTR_Value ValueStruct::mod(const Value& right)     const { return right.mod(*this); } // %
PTR_Value ValueStruct::eq(const Value& right)      const { return right.eq(*this); } // ==
PTR_Value ValueStruct::eq(const ValueStruct& /*left*/) const { return VALUEBOOL_FALSE; }
PTR_Value ValueStruct::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueStruct::ne(const ValueStruct& /*left*/) const { return VALUEBOOL_TRUE; }
PTR_Value ValueStruct::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueStruct::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueStruct::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueStruct::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueStruct::member(const Value& right)  const { return right.member(*this); } // .
PTR_Value ValueStruct::index(const Value& right)   const { return right.index(*this); } // []
PTR_Value ValueStruct::logNOT(void)                const { ACCESS_MUTEX_LOCKER; return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !


/////////////////////////////////////////////////////////////////////////////
////

bool ValueStruct::toBool(void) const
{
	ACCESS_MUTEX_LOCKER;
	return !m_val.empty();
}
