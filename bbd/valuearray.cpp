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
#include "node.hpp"
#include "valuebool.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueArray::ValueArray()
	: Value(),
	m_val()
{

}

ValueArray::~ValueArray()
{
	vector<Value*>::iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
	{
		if(*it != NULL)
		{
			delete *it;
			*it = NULL;
		}
	}

	m_val.clear();
}


/////////////////////////////////////////////////////////////////////////////
////

string ValueArray::toString(void) const
{
	ostringstream os;
	vector<Value*>::const_iterator it;

	for(it = m_val.begin(); it != m_val.end(); it++)
	{
		if(*it != NULL)
			os << (*it)->toString() << ",";
		else
			os << "NULL" << ",";
	}

	string ret = os.str();
	if(ret.size() != 0)
		ret.resize(ret.size()-1);// remove last ","

	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::resize(uint newsize)
{
	m_val.resize(newsize, NULL);
}


Value* ValueArray::getItem(uint pos)
{
	if(pos < m_val.size())
		return m_val[pos];
	else
	{
		WARN << _("Array index out of bounds") << endl;
		return NULL;
	}
}

void ValueArray::setItem(uint pos, Value* val)
{
	if(pos < m_val.size())
	{
		if(m_val[pos] != NULL)
			delete m_val[pos];

		m_val[pos] = val;
	}
	else
	{
		// TODO: resize?
		WARN << _("Array index out of bounds") << endl;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueArray::dump(ostream& os, uint indent) const
{
	Node::dumpIndent(os, indent);
	os << "<ValueArray value=\"" << toString() << "\" />" << endl;
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
PTR_Value ValueArray::eq(const ValueArray& left)  const { return PTR_Value(new ValueBool(left.getVal() == m_val)); }
PTR_Value ValueArray::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueArray::ne(const ValueArray& left)  const { return PTR_Value(new ValueBool(left.getVal() != m_val)); }
PTR_Value ValueArray::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueArray::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueArray::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueArray::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueArray::member(const Value& right)  const { return right.member(*this); } // .
PTR_Value ValueArray::index(const Value& right)   const { return right.index(*this); } // []
PTR_Value ValueArray::logNOT(void)                const { return PTR_Value(new ValueBool(m_val.empty())); } // !
