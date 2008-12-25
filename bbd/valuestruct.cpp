/*
 *      valuestruct.cpp
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


/////////////////////////////////////////////////////////////////////////////
////


ValueStruct::ValueStruct()
	: Value(),
	m_val()
{

}


ValueStruct::~ValueStruct()
{
	map<KEY_TYPE, Value*>::iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		delete it->second;
}


/////////////////////////////////////////////////////////////////////////////
////

string ValueStruct::toString(void) const
{
	ostringstream os;
	map<KEY_TYPE, Value*>::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
		os << it->first << "=" << it->second->toString() << ",";

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueStruct::setItem(const string& name, Value* value)
{
	m_val[name] = value;
}


Value* ValueStruct::getItem(const string& name)
{
	map<KEY_TYPE, Value*>::iterator it = m_val.find(name);

	if(it != m_val.end())
		return it->second;
	else
		return &m_notfound;
}

bool ValueStruct::isItemSet(const string& name)
{
	return m_val.count(name);
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueStruct::execute(Context& context)
{
	return PTR_Value(new ValueStruct(*this));// TODO: deep copy!
}

void ValueStruct::dump(ostream& os, uint indent) const
{
	this->dumpIndent(os, indent);
	os << "<ValueStruct value=\"" << toString() << "\" />" << endl;// TODO: dump all
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
PTR_Value ValueStruct::eq(const ValueStruct& left) const { return PTR_Value(new ValueBool(left.m_val == m_val)); }
PTR_Value ValueStruct::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueStruct::ne(const ValueStruct& left) const { return PTR_Value(new ValueBool(left.m_val != m_val)); }
PTR_Value ValueStruct::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueStruct::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueStruct::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueStruct::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueStruct::logNOT(void)                const { return PTR_Value(new ValueBool(m_val.empty())); } // !
