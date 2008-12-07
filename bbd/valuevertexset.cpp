/*
 *      valuevertexset.cpp
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


#include "valuevertexset.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertexSet::ValueVertexSet(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_vertices()
{

}


ValueVertexSet::~ValueVertexSet()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertexSet::addVertex(ValueVertex* vertex)
{
	if(m_graph == vertex->getGraph())
		m_vertices.insert(vertex);
	else
		WARN << _("Vertex belongs to the different graph than VertexSet");
}

void ValueVertexSet::deleteVertex(ValueVertex* vertex)
{
	m_vertices.erase(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueVertexSet::add(const Value& right)        const { return right.add(*this); } // +
PTR_Value ValueVertexSet::sub(const Value& right)        const { return right.sub(*this); } // -
PTR_Value ValueVertexSet::mult(const Value& right)       const { return right.mult(*this); } // *
PTR_Value ValueVertexSet::div(const Value& right)        const { return right.div(*this); } // /
PTR_Value ValueVertexSet::mod(const Value& right)        const { return right.mod(*this); } // %
PTR_Value ValueVertexSet::eq(const Value& right)         const { return right.eq(*this); } // ==
PTR_Value ValueVertexSet::eq(const ValueVertexSet& left) const { return PTR_Value(new ValueBool(left.m_vertices == m_vertices)); }
PTR_Value ValueVertexSet::ne(const Value& right)         const { return right.ne(*this); } // !=
PTR_Value ValueVertexSet::ne(const ValueVertexSet& left) const { return PTR_Value(new ValueBool(left.m_vertices != m_vertices)); }
PTR_Value ValueVertexSet::le(const Value& right)         const { return right.le(*this); } // <=
PTR_Value ValueVertexSet::ge(const Value& right)         const { return right.ge(*this); } // >=
PTR_Value ValueVertexSet::lt(const Value& right)         const { return right.lt(*this); } // <
PTR_Value ValueVertexSet::gt(const Value& right)         const { return right.gt(*this); } // >
PTR_Value ValueVertexSet::logNOT(void)                   const { return PTR_Value(new ValueBool(m_vertices.empty())); } // !

