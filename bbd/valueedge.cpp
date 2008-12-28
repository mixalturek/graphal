/*
 *      edge.cpp
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


#include "valueedge.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"
#include "node.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueEdge::ValueEdge(ValueGraph* graph, ValueVertex* begin, ValueVertex* end)
	: Value(),
	m_graph(graph),
	m_begin(begin),
	m_end(end),
	m_properties(new ValueStruct())
{

}

ValueEdge::~ValueEdge()
{
	delete m_properties;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdge::invertOrientation(void)
{
	ValueVertex* tmp = m_begin;
	m_begin = m_end;
	m_end = tmp;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdge::dump(ostream& os, uint indent) const
{
	Node::dumpIndent(os, indent);
	os << "<ValueEdge />" << endl;// TODO:
}

ostream& operator<<(ostream& os, const ValueEdge& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueEdge::add(const Value& right)   const { return right.add(*this); } // +
PTR_Value ValueEdge::sub(const Value& right)   const { return right.sub(*this); } // -
PTR_Value ValueEdge::mult(const Value& right)  const { return right.mult(*this); } // *
PTR_Value ValueEdge::div(const Value& right)   const { return right.div(*this); } // /
PTR_Value ValueEdge::mod(const Value& right)   const { return right.mod(*this); } // %
PTR_Value ValueEdge::eq(const Value& right)    const { return right.eq(*this); } // ==
PTR_Value ValueEdge::eq(const ValueEdge& left) const { return PTR_Value(new ValueBool(&left == this)); }
PTR_Value ValueEdge::ne(const Value& right)    const { return right.ne(*this); } // !=
PTR_Value ValueEdge::ne(const ValueEdge& left) const { return PTR_Value(new ValueBool(&left != this)); }
PTR_Value ValueEdge::le(const Value& right)    const { return right.le(*this); } // <=
PTR_Value ValueEdge::ge(const Value& right)    const { return right.ge(*this); } // >=
PTR_Value ValueEdge::lt(const Value& right)    const { return right.lt(*this); } // <
PTR_Value ValueEdge::gt(const Value& right)    const { return right.gt(*this); } // >
PTR_Value ValueEdge::logNOT(void)              const { return PTR_Value(new ValueBool(false)); } // !
