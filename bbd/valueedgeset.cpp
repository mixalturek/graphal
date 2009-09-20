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
#include "valueedgeset.hpp"
#include "logger.hpp"
#include "valuebool.hpp"
#include "valueedge.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueEdgeSet::ValueEdgeSet(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges(),
	m_it(m_edges.begin())
{
	assert(graph != NULL);
}

ValueEdgeSet::ValueEdgeSet(ValueGraph* graph, const set<ValueEdge*>& edges)
	: Value(),
	m_graph(graph),
	m_edges(edges),
	m_it(m_edges.begin())
{
	assert(graph != NULL);
}

ValueEdgeSet::~ValueEdgeSet(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdgeSet::addEdge(ValueEdge* edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge != NULL);

	if(m_graph == edge->getGraph())
		m_edges.insert(edge);
	else
		WARN_P(_("Edge belongs to the different graph than EdgeSet"));
}

void ValueEdgeSet::deleteEdge(ValueEdge* edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge != NULL);
	m_edges.erase(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueEdgeSet::iterator(void) const
{
	ACCESS_MUTEX_LOCKER;
	ValueEdgeSet* tmp = new ValueEdgeSet(m_graph);
	tmp->m_edges = m_edges;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}

CountPtr<Value> ValueEdgeSet::hasNext(void) const
{
	ACCESS_MUTEX_LOCKER;
	return (m_it == m_edges.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}

CountPtr<Value> ValueEdgeSet::next(void)
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> ret(*m_it);
	ret.dontDeleteAutomatically();// TODO: is it needed?
	m_it++;
	return ret;
}

void ValueEdgeSet::resetIterator(void)
{
	ACCESS_MUTEX_LOCKER;
	m_it = m_edges.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueEdgeSet::getUnion(const ValueEdgeSet& es) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != es.m_graph)
	{
		WARN_P(_("EdgeSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueEdge*>::iterator it;
	ValueEdgeSet* ret = new ValueEdgeSet(m_graph);

	for(it = m_edges.begin(); it != m_edges.end(); it++)
		ret->addEdge(*it);

	for(it = es.m_edges.begin(); it != es.m_edges.end(); it++)
		ret->addEdge(*it);

	return CountPtr<Value>(ret);
}


CountPtr<Value> ValueEdgeSet::getIntersection(const ValueEdgeSet& es) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != es.m_graph)
	{
		WARN_P(_("EdgeSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueEdge*>::iterator it;
	ValueEdgeSet* ret = new ValueEdgeSet(m_graph);

	for(it = m_edges.begin(); it != m_edges.end(); it++)
	{
		if(es.contains(*it))
			ret->addEdge(*it);
	}

	return CountPtr<Value>(ret);
}


CountPtr<Value> ValueEdgeSet::getDifference(const ValueEdgeSet& es) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != es.m_graph)
	{
		WARN_P(_("EdgeSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueEdge*>::iterator it;
	ValueEdgeSet* ret = new ValueEdgeSet(m_graph);

	for(it = m_edges.begin(); it != m_edges.end(); it++)
	{
		if(!es.contains(*it))
			ret->addEdge(*it);
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueEdgeSet::toBool(void) const
{
	ACCESS_MUTEX_LOCKER;
	return !m_edges.empty();
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueEdgeSet::getNumEdges(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.size();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueEdgeSet::contains(ValueEdge* edge) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.count(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdgeSet::setPropertyToAllEdges(identifier name, CountPtr<Value> value)
{
	set<ValueEdge*>::iterator it;
	for(it = m_edges.begin(); it != m_edges.end(); ++it)
		(*it)->setItem(name, value);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueEdgeSet::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<ValueEdgeSet>" << endl;

	set<ValueEdge*>::const_iterator it;
	for(it = m_edges.begin(); it != m_edges.end(); it++)
		(*it)->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueEdgeSet>" << endl;
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
PTR_Value ValueEdgeSet::eq(const ValueEdgeSet& left) const { return (left.m_edges == m_edges) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueEdgeSet::ne(const Value& right)       const { return right.ne(*this); } // !=
PTR_Value ValueEdgeSet::ne(const ValueEdgeSet& left) const { return (left.m_edges != m_edges) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueEdgeSet::le(const Value& right)       const { return right.le(*this); } // <=
PTR_Value ValueEdgeSet::ge(const Value& right)       const { return right.ge(*this); } // >=
PTR_Value ValueEdgeSet::lt(const Value& right)       const { return right.lt(*this); } // <
PTR_Value ValueEdgeSet::gt(const Value& right)       const { return right.gt(*this); } // >
PTR_Value ValueEdgeSet::member(const Value& right)   const { return right.member(*this); } // .
PTR_Value ValueEdgeSet::index(const Value& right)    const { return right.index(*this); } // []
PTR_Value ValueEdgeSet::logNOT(void)                 const { ACCESS_MUTEX_LOCKER; return (m_edges.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
