/*
 *      graph.cpp
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


#include "valuegraph.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueGraph::ValueGraph(bool oriented)
	: Value(),
	m_oriented(oriented),
	m_vertices(),
	m_edges()
{

}

ValueGraph::~ValueGraph()
{
	set<ValueVertex*>::const_iterator vit;
	for(vit = m_vertices.begin(); vit != m_vertices.end(); vit++)
		delete *vit;

	set<ValueEdge*>::const_iterator eit;
	for(eit = m_edges.begin(); eit != m_edges.end(); eit++)
		delete *eit;
}


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex* ValueGraph::generateVertex(void)
{
	ValueVertex* vertex = new ValueVertex(this);
	m_vertices.insert(vertex);
	return vertex;
}

ValueEdge* ValueGraph::generateEdge(ValueVertex* begin, ValueVertex* end)
{
	ValueEdge* edge = new ValueEdge(this, begin, end);
	m_edges.insert(edge);

	begin->addEdge(edge, BEGIN);
	end->addEdge(edge, END);

	return edge;
}

void ValueGraph::deleteVertex(ValueVertex* vertex)
{
	set< pair<ValueEdge*, ORIENTATION> >& edges = vertex->getEdges();

	set< pair<ValueEdge*, ORIENTATION> >::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
		deleteEdge(it->first);

	m_vertices.erase(vertex);
	delete vertex;
}

void ValueGraph::deleteEdge(ValueEdge* edge)
{
	edge->getBeginVertex()->deleteEdge(edge, BEGIN);
	edge->getEndVertex()->deleteEdge(edge, END);
	m_edges.erase(edge);
	delete edge;
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueGraph::add(const Value& right)       const { return right.add(*this); }

// -
PTR_Value ValueGraph::sub(const Value& right)       const { return right.sub(*this); }

// *
PTR_Value ValueGraph::mult(const Value& right)      const { return right.mult(*this); }

// /
PTR_Value ValueGraph::div(const Value& right)       const { return right.div(*this); }

// %
PTR_Value ValueGraph::mod(const Value& right)       const { return right.mod(*this); }

// ==
PTR_Value ValueGraph::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueGraph::eq(const ValueGraph& left)    const { return PTR_Value(new ValueBool(true)); } // TODO

// !=
PTR_Value ValueGraph::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueGraph::ne(const ValueGraph& left)    const { return PTR_Value(new ValueBool(false)); } // TODO

// <=
PTR_Value ValueGraph::le(const Value& right)        const { return right.le(*this); }

// >=
PTR_Value ValueGraph::ge(const Value& right)        const { return right.ge(*this); }

// <
PTR_Value ValueGraph::lt(const Value& right)        const { return right.lt(*this); }

// >
PTR_Value ValueGraph::gt(const Value& right)        const { return right.gt(*this); }

// !
PTR_Value ValueGraph::logNOT(void)                  const { return PTR_Value(new ValueBool(m_vertices.empty())); }
