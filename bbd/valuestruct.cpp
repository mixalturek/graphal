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


ValueStruct::ValueStruct()
	: Value(),
	m_val()
{

}


ValueStruct::~ValueStruct()
{

}


/////////////////////////////////////////////////////////////////////////////
////

string ValueStruct::toString(void) const
{
	ostringstream os;
	map<identifier, CountPtr<Value> >::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		os << ID2STR(it->first) << "=" << it->second->toString() << ",";

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueStruct::setItem(identifier name, CountPtr<Value> val)
{
/*	if(val->isReference())
		return m_val[name] = val;
	else
		return m_val[name] = CountPtr<Value>(new ValueReference(val));
*/
	map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);
	if(it != m_val.end())
		m_val.erase(it);

	if(val->isReference())
		return m_val.insert(pair<identifier, CountPtr<Value> >(name, val)).first->second;
	else
		return m_val.insert(pair<identifier, CountPtr<Value> >(name, CountPtr<Value>(new ValueReference(val)))).first->second;
}


CountPtr<Value> ValueStruct::getItem(identifier name)
{
	map<identifier, CountPtr<Value> >::iterator it = m_val.find(name);

	if(it != m_val.end())
		return it->second;
	else
		return VALUENULL;
}

bool ValueStruct::isItemSet(identifier name)
{
	return m_val.count(name);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueStruct>" << endl;

	map<identifier, CountPtr<Value> >::const_iterator it;
	for(it = m_val.begin(); it != m_val.end(); it++)
	{
		dumpIndent(os, indent+1);
		os << "<Name name=\"" << ID2STR(it->first) << "\" />" << endl;
		it->second->dump(os, indent+1);
		os << endl;
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
PTR_Value ValueStruct::eq(const ValueStruct& /*left*/) const { return VALUEBOOL_FALSE; }// TODO
PTR_Value ValueStruct::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueStruct::ne(const ValueStruct& /*left*/) const { return VALUEBOOL_TRUE; }
PTR_Value ValueStruct::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueStruct::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueStruct::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueStruct::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueStruct::member(const Value& right)  const { return right.member(*this); } // .
PTR_Value ValueStruct::index(const Value& right)   const { return right.index(*this); } // []
PTR_Value ValueStruct::logNOT(void)                const { return (m_val.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
