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


#include <cassert>
#include "valueedge.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueEdge::ValueEdge(ValueGraph* graph, CountPtr<Value> begin, CountPtr<Value> end)
	: Value(),
	m_graph(graph),
	m_begin(begin->toValueVertex()),
	m_end(end->toValueVertex()),
	m_properties(new ValueStruct)
{
	assert(graph != NULL);
	assert(m_begin != NULL);
	assert(m_end != NULL);
}

ValueEdge::~ValueEdge(void)
{
	ACCESS_MUTEX_LOCKER;
	delete m_properties;
	m_properties = NULL;
}

void ValueEdge::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	m_properties->clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdge::invertDirection(void)
{
	ACCESS_MUTEX_LOCKER;
	ValueVertex* tmp = m_begin;
	m_begin = m_end;
	m_end = tmp;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueEdge::getBeginVertex(void)
{
	ACCESS_MUTEX_LOCKER;
	return (m_begin == NULL) ? VALUENULL : m_graph->findVertex(m_begin);
}

CountPtr<Value> ValueEdge::getEndVertex(void)
{
	ACCESS_MUTEX_LOCKER;
	return (m_end == NULL) ? VALUENULL : m_graph->findVertex(m_end);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdge::removeVertex(ValueVertex* vertex)
{
	ACCESS_MUTEX_LOCKER;
	if(m_begin == vertex)
		m_begin = NULL;

	if(m_end == vertex)
		m_end = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdge::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<ValueEdge>" << endl;
	m_properties->dump(os, indent+1);
	dumpIndent(os, indent);
	os << "</ValueEdge>" << endl;
}

ostream& operator<<(ostream& os, const ValueEdge& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueEdge::add(const Value& right)   const { return right.add(*this); } // +
CountPtr<Value> ValueEdge::sub(const Value& right)   const { return right.sub(*this); } // -
CountPtr<Value> ValueEdge::mult(const Value& right)  const { return right.mult(*this); } // *
CountPtr<Value> ValueEdge::div(const Value& right)   const { return right.div(*this); } // /
CountPtr<Value> ValueEdge::mod(const Value& right)   const { return right.mod(*this); } // %
CountPtr<Value> ValueEdge::eq(const Value& right)    const { return right.eq(*this); } // ==
CountPtr<Value> ValueEdge::eq(const ValueEdge& left) const { return (&left == this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueEdge::ne(const Value& right)    const { return right.ne(*this); } // !=
CountPtr<Value> ValueEdge::ne(const ValueEdge& left) const { return (&left != this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueEdge::le(const Value& right)    const { return right.le(*this); } // <=
CountPtr<Value> ValueEdge::ge(const Value& right)    const { return right.ge(*this); } // >=
CountPtr<Value> ValueEdge::lt(const Value& right)    const { return right.lt(*this); } // <
CountPtr<Value> ValueEdge::gt(const Value& right)    const { return right.gt(*this); } // >
CountPtr<Value> ValueEdge::member(const Value& right) const { return right.member(*this); } // .
CountPtr<Value> ValueEdge::index(const Value& right) const { return right.index(*this); } // []
CountPtr<Value> ValueEdge::logNOT(void)              const { return VALUEBOOL_FALSE; } // !
