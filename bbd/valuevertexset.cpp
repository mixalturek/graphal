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
#include "valuevertexset.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"
#include "logger.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertexSet::ValueVertexSet(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_vertices(),
	m_it(m_vertices.begin())
{
	assert(graph != NULL);
}

ValueVertexSet::ValueVertexSet(ValueGraph* graph, const set<ValueVertex*>& vertices)
	: Value(),
	m_graph(graph),
	m_vertices(vertices),
	m_it(m_vertices.begin())
{
	assert(graph != NULL);
}

ValueVertexSet::~ValueVertexSet(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertexSet::addVertex(ValueVertex* vertex)
{
	ACCESS_MUTEX_LOCKER;
	assert(vertex != NULL);

	if(m_graph == vertex->getGraph())
		m_vertices.insert(vertex);
	else
		WARN_P(_("Vertex belongs to the different graph than VertexSet"));
}

void ValueVertexSet::deleteVertex(ValueVertex* vertex)
{
	ACCESS_MUTEX_LOCKER;
	assert(vertex != NULL);
	m_vertices.erase(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueVertexSet::iterator(void) const
{
	ACCESS_MUTEX_LOCKER;
	ValueVertexSet* tmp = new ValueVertexSet(m_graph);
	tmp->m_vertices = m_vertices;
	tmp->resetIterator();

	return CountPtr<Value>(tmp);
}

CountPtr<Value> ValueVertexSet::hasNext(void) const
{
	ACCESS_MUTEX_LOCKER;
	return (m_it == m_vertices.end()) ? VALUEBOOL_FALSE : VALUEBOOL_TRUE;
}

CountPtr<Value> ValueVertexSet::next(void)
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> ret(*m_it);
	ret.dontDeleteAutomatically();// TODO: is it needed?
	m_it++;
	return ret;
}

void ValueVertexSet::resetIterator(void)
{
	ACCESS_MUTEX_LOCKER;
	m_it = m_vertices.begin();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueVertexSet::getUnion(const ValueVertexSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != vs.m_graph)
	{
		WARN_P(_("VertexSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueVertex*>::iterator it;
	ValueVertexSet* ret = new ValueVertexSet(m_graph);

	for(it = m_vertices.begin(); it != m_vertices.end(); it++)
		ret->addVertex(*it);

	for(it = vs.m_vertices.begin(); it != vs.m_vertices.end(); it++)
		ret->addVertex(*it);

	return CountPtr<Value>(ret);
}

CountPtr<Value> ValueVertexSet::getIntersection(const ValueVertexSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != vs.m_graph)
	{
		WARN_P(_("VertexSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueVertex*>::iterator it;
	ValueVertexSet* ret = new ValueVertexSet(m_graph);

	for(it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		if(vs.contains(*it))
			ret->addVertex(*it);
	}

	return CountPtr<Value>(ret);
}


CountPtr<Value> ValueVertexSet::getDifference(const ValueVertexSet& vs) const
{
	ACCESS_MUTEX_LOCKER;

	if(m_graph != vs.m_graph)
	{
		WARN_P(_("VertexSet belongs to the different graph"));
		return VALUENULL;
	}

	set<ValueVertex*>::iterator it;
	ValueVertexSet* ret = new ValueVertexSet(m_graph);

	for(it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		if(!vs.contains(*it))
			ret->addVertex(*it);
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueVertexSet::toBool(void) const
{
	ACCESS_MUTEX_LOCKER;
	return !m_vertices.empty();
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueVertexSet::getNumVertices(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.size();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueVertexSet::contains(ValueVertex* vertex) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.count(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertexSet::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<ValueVertexSet>" << endl;

	set<ValueVertex*>::const_iterator it;
	for(it = m_vertices.begin(); it != m_vertices.end(); it++)
		(*it)->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</ValueVertexSet>" << endl;
}

ostream& operator<<(ostream& os, const ValueVertexSet& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

PTR_Value ValueVertexSet::add(const Value& right)        const { return right.add(*this); } // +
PTR_Value ValueVertexSet::sub(const Value& right)        const { return right.sub(*this); } // -
PTR_Value ValueVertexSet::mult(const Value& right)       const { return right.mult(*this); } // *
PTR_Value ValueVertexSet::div(const Value& right)        const { return right.div(*this); } // /
PTR_Value ValueVertexSet::mod(const Value& right)        const { return right.mod(*this); } // %
PTR_Value ValueVertexSet::eq(const Value& right)         const { return right.eq(*this); } // ==
PTR_Value ValueVertexSet::eq(const ValueVertexSet& left) const { return (left.m_vertices == m_vertices) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueVertexSet::ne(const Value& right)         const { return right.ne(*this); } // !=
PTR_Value ValueVertexSet::ne(const ValueVertexSet& left) const { return (left.m_vertices != m_vertices) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueVertexSet::le(const Value& right)         const { return right.le(*this); } // <=
PTR_Value ValueVertexSet::ge(const Value& right)         const { return right.ge(*this); } // >=
PTR_Value ValueVertexSet::lt(const Value& right)         const { return right.lt(*this); } // <
PTR_Value ValueVertexSet::gt(const Value& right)         const { return right.gt(*this); } // >
PTR_Value ValueVertexSet::member(const Value& right)     const { return right.member(*this); } // .
PTR_Value ValueVertexSet::index(const Value& right)      const { return right.index(*this); } // []
PTR_Value ValueVertexSet::logNOT(void)                   const { ACCESS_MUTEX_LOCKER; return (m_vertices.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !

