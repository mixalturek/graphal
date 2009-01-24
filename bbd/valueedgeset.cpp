/*
 *      valueedgeset.cpp
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


#include "valueedgeset.hpp"
#include "logger.hpp"
#include "valuebool.hpp"
#include "valueedge.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueEdgeSet::ValueEdgeSet(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges()
{

}


ValueEdgeSet::~ValueEdgeSet()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdgeSet::addEdge(ValueEdge* edge)
{
	if(m_graph == edge->getGraph())
		m_edges.insert(edge);
	else
		WARN << _("Edge belongs to the different graph than EdgeSet");
}

void ValueEdgeSet::deleteEdge(ValueEdge* edge)
{
	m_edges.erase(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdgeSet::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<ValueEdgeSet />" << endl;// TODO:
}

ostream& operator<<(ostream& os, const ValueEdgeSet& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueEdgeSet::add(const Value& right)      const { return right.add(*this); } // +
PTR_Value ValueEdgeSet::sub(const Value& right)      const { return right.sub(*this); } // -
PTR_Value ValueEdgeSet::mult(const Value& right)     const { return right.mult(*this); } // *
PTR_Value ValueEdgeSet::div(const Value& right)      const { return right.div(*this); } // /
PTR_Value ValueEdgeSet::mod(const Value& right)      const { return right.mod(*this); } // %
PTR_Value ValueEdgeSet::eq(const Value& right)       const { return right.eq(*this); } // ==
PTR_Value ValueEdgeSet::eq(const ValueEdgeSet& left) const { return PTR_Value(new ValueBool(left.m_edges == m_edges)); }
PTR_Value ValueEdgeSet::ne(const Value& right)       const { return right.ne(*this); } // !=
PTR_Value ValueEdgeSet::ne(const ValueEdgeSet& left) const { return PTR_Value(new ValueBool(left.m_edges == m_edges)); }
PTR_Value ValueEdgeSet::le(const Value& right)       const { return right.le(*this); } // <=
PTR_Value ValueEdgeSet::ge(const Value& right)       const { return right.ge(*this); } // >=
PTR_Value ValueEdgeSet::lt(const Value& right)       const { return right.lt(*this); } // <
PTR_Value ValueEdgeSet::gt(const Value& right)       const { return right.gt(*this); } // >
PTR_Value ValueEdgeSet::member(const Value& right)   const { return right.member(*this); } // .
PTR_Value ValueEdgeSet::index(const Value& right)    const { return right.index(*this); } // []
PTR_Value ValueEdgeSet::logNOT(void)                 const { return PTR_Value(new ValueBool(m_edges.empty())); } // !
