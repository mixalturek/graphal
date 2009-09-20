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
#include "valuevertex.hpp"
#include "valuebool.hpp"
#include "valuegraph.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex::ValueVertex(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges(new set<ValueEdge*>),
	m_properties(new ValueStruct)
{
	assert(graph != NULL);
}

ValueVertex::~ValueVertex(void)
{
	ACCESS_MUTEX_LOCKER;
	delete m_edges;
	m_edges = NULL;
	delete m_properties;
	m_properties = NULL;
}

void ValueVertex::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	m_properties->clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::addEdge(ValueEdge* edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge != NULL);
	m_edges->insert(edge);
}

void ValueVertex::deleteEdge(ValueEdge* edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge != NULL);
	m_edges->erase(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueVertex::getNeighbors(void)
{
	ACCESS_MUTEX_LOCKER;
	ValueVertexSet* ret = new ValueVertexSet(m_graph);
	set<ValueEdge*>::iterator it;

	if(m_graph->isDirected())
	{
		for(it = m_edges->begin(); it != m_edges->end(); it++)
		{
			if((*it)->getBeginVertex() == this)
				ret->addVertex((*it)->getEndVertex());
		}
	}
	else
	{
		for(it = m_edges->begin(); it != m_edges->end(); it++)
		{
			if((*it)->getBeginVertex() == this)
				ret->addVertex((*it)->getEndVertex());
			else
				ret->addVertex((*it)->getBeginVertex());
		}
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueVertex::getDegree(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges->size();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<ValueVertex>" << endl;
	m_properties->dump(os, indent+1);
	dumpIndent(os, indent);
	os << "</ValueVertex>" << endl;
}

ostream& operator<<(ostream& os, const ValueVertex& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueVertex::add(const Value& right)     const { return right.add(*this); } // +
PTR_Value ValueVertex::sub(const Value& right)     const { return right.sub(*this); } // -
PTR_Value ValueVertex::mult(const Value& right)    const { return right.mult(*this); } // *
PTR_Value ValueVertex::div(const Value& right)     const { return right.div(*this); } // /
PTR_Value ValueVertex::mod(const Value& right)     const { return right.mod(*this); } // %
PTR_Value ValueVertex::eq(const Value& right)      const { return right.eq(*this); } // ==
PTR_Value ValueVertex::eq(const ValueVertex& left) const { return (&left == this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueVertex::ne(const Value& right)      const { return right.ne(*this); } // !=
PTR_Value ValueVertex::ne(const ValueVertex& left) const { return (&left != this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueVertex::le(const Value& right)      const { return right.le(*this); } // <=
PTR_Value ValueVertex::ge(const Value& right)      const { return right.ge(*this); } // >=
PTR_Value ValueVertex::lt(const Value& right)      const { return right.lt(*this); } // <
PTR_Value ValueVertex::gt(const Value& right)      const { return right.gt(*this); } // >
PTR_Value ValueVertex::member(const Value& right)  const { return right.member(*this); } // .
PTR_Value ValueVertex::index(const Value& right)   const { return right.index(*this); } // []
PTR_Value ValueVertex::logNOT(void)                const { return VALUEBOOL_FALSE; } // !
