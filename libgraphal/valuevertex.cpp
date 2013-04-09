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
#include "valuevertex.h"
#include "valuebool.h"
#include "valuegraph.h"
#include "valueedge.h"
#include "context.h"
#include "valueset.h"
#include "logger.h"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex::ValueVertex(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges(new ValueSet),
	m_properties(new ValueStruct)
{
	assert(graph != NULL);
}

ValueVertex::~ValueVertex(void)
{
	ACCESS_MUTEX_LOCKER;

	set_container::iterator it;
	for(it = m_edges->begin(); it != m_edges->end(); ++it)
		(*it)->toValueEdge()->removeVertex(this);

	delete m_edges;
	m_edges = NULL;
	delete m_properties;
	m_properties = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	m_edges->clear();
	m_properties->clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::addEdge(CountPtr<Value> edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge->toValueEdge() != NULL);
	m_edges->insert(edge);
}

void ValueVertex::deleteEdge(CountPtr<Value> edge)
{
	ACCESS_MUTEX_LOCKER;
	assert(edge->toValueEdge() != NULL);
	m_edges->remove(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueVertex::getNeighbors(void)
{
	ACCESS_MUTEX_LOCKER;
	ValueSet* ret = new ValueSet;
	CountPtr<Value> retval(ret);
	set_container::iterator it;

	if(m_graph == NULL)
	{
		WARN_P(_("The graph is invalid (deleted?)"));
		return VALUENULL;
	}

	if(m_graph->isDirected())
	{
		for(it = m_edges->begin(); it != m_edges->end(); ++it)
		{
			ValueEdge* edge = (*it)->toValueEdge();
			assert(edge != NULL);

			if(edge->getBeginVertex()->toValueVertex() == this)
				ret->insert((*it)->toValueEdge()->getEndVertex());
		}
	}
	else
	{
		for(it = m_edges->begin(); it != m_edges->end(); ++it)
		{
			ValueEdge* edge = (*it)->toValueEdge();
			assert(edge != NULL);

			if(edge->getBeginVertex()->toValueVertex() == this)
				ret->insert(edge->getEndVertex());
			else
				ret->insert(edge->getBeginVertex());
		}
	}

	return retval;
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueVertex::getDegree(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges->getSize();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueVertex::getEdgesCopy(void)
{
	ACCESS_MUTEX_LOCKER;
	return m_edges->clone();
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

CountPtr<Value> ValueVertex::add(const Value& right)     const { return right.add(*this); } // +
CountPtr<Value> ValueVertex::sub(const Value& right)     const { return right.sub(*this); } // -
CountPtr<Value> ValueVertex::mult(const Value& right)    const { return right.mult(*this); } // *
CountPtr<Value> ValueVertex::div(const Value& right)     const { return right.div(*this); } // /
CountPtr<Value> ValueVertex::mod(const Value& right)     const { return right.mod(*this); } // %
CountPtr<Value> ValueVertex::eq(const Value& right)      const { return right.eq(*this); } // ==
CountPtr<Value> ValueVertex::eq(const ValueVertex& left) const { return (&left == this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueVertex::ne(const Value& right)      const { return right.ne(*this); } // !=
CountPtr<Value> ValueVertex::ne(const ValueVertex& left) const { return (&left != this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueVertex::le(const Value& right)      const { return right.le(*this); } // <=
CountPtr<Value> ValueVertex::ge(const Value& right)      const { return right.ge(*this); } // >=
CountPtr<Value> ValueVertex::lt(const Value& right)      const { return right.lt(*this); } // <
CountPtr<Value> ValueVertex::gt(const Value& right)      const { return right.gt(*this); } // >
CountPtr<Value> ValueVertex::member(const Value& right)  const { return right.member(*this); } // .
CountPtr<Value> ValueVertex::index(const Value& right)   const { return right.index(*this); } // []
CountPtr<Value> ValueVertex::logNOT(void)                const { return VALUEBOOL_FALSE; } // !
