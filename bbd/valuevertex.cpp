/*
 *      vertex.cpp
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


#include "valuevertex.hpp"
#include "valuebool.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex::ValueVertex(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges()
{

}

ValueVertex::~ValueVertex()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::addEdge(ValueEdge* edge, ORIENTATION orientation)
{
	m_edges.insert(pair<ValueEdge*, ORIENTATION>(edge, orientation));
}

void ValueVertex::deleteEdge(ValueEdge* edge, ORIENTATION orientation)
{
	m_edges.erase(pair<ValueEdge*, ORIENTATION>(edge, orientation));
}


/////////////////////////////////////////////////////////////////////////////
////

set<ValueEdge *> ValueVertex::getNeighbors(void)
{
	// TODO: implement the method body
	return set<ValueEdge *>();
}


/////////////////////////////////////////////////////////////////////////////
////

// +
PTR_Value ValueVertex::add(const Value& right)       const { return right.add(*this); }

// -
PTR_Value ValueVertex::sub(const Value& right)       const { return right.sub(*this); }

// *
PTR_Value ValueVertex::mult(const Value& right)      const { return right.mult(*this); }

// /
PTR_Value ValueVertex::div(const Value& right)       const { return right.div(*this); }

// %
PTR_Value ValueVertex::mod(const Value& right)       const { return right.mod(*this); }

// ==
PTR_Value ValueVertex::eq(const Value& right)        const { return right.eq(*this); }
PTR_Value ValueVertex::eq(const ValueVertex& left)   const { return PTR_Value(new ValueBool(true)); } // TODO

// !=
PTR_Value ValueVertex::ne(const Value& right)        const { return right.ne(*this); }
PTR_Value ValueVertex::ne(const ValueVertex& left)   const { return PTR_Value(new ValueBool(false)); } // TODO

// <=
PTR_Value ValueVertex::le(const Value& right)        const { return right.le(*this); }

// >=
PTR_Value ValueVertex::ge(const Value& right)        const { return right.ge(*this); }

// <
PTR_Value ValueVertex::lt(const Value& right)        const { return right.lt(*this); }

// >
PTR_Value ValueVertex::gt(const Value& right)        const { return right.gt(*this); }

// !
PTR_Value ValueVertex::logNOT(void)                  const { return PTR_Value(new ValueBool(false)); } // TODO
