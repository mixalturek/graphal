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


#include <fstream>
#include <vector>
#include <algorithm>
#include "valuegraph.h"
#include "logger.h"
#include "valuebool.h"
#include "valuevertex.h"
#include "valueedge.h"
#include "context.h"
#include "valueint.h"
#include "valuefloat.h"
#include "objectcreator.h"
#include "valuearray.h"
#include "valueset.h"


/////////////////////////////////////////////////////////////////////////////
////

ValueGraph::ValueGraph(bool directed)
	: Value(),
	m_directed(directed),
	m_vertices(),
	m_edges()
{

}

ValueGraph::~ValueGraph(void)
{
	set_container::iterator it;

	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
		(*it)->toValueVertex()->setGraphToNULL();

	for(it = m_edges.begin(); it != m_edges.end(); ++it)
		(*it)->toValueEdge()->setGraphToNULL();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::loadFromFile(const string& filename)
{
	ACCESS_MUTEX_LOCKER;

	ifstream is(filename.c_str());

	if(!is.is_open())
	{
		WARN_P(_("File was not found or is not readable: ") + filename);
		return false;
	}

	m_vertices.clear();
	m_edges.clear();

	int num_vertices = 0;
	int num_edges = 0;
	int num_vertices_props = 0;
	int num_edges_props = 0;
	vector<identifier> vertices_props;
	vector<identifier> edges_props;
	map<int, CountPtr<Value> > vertices;

	// Is directed flag, number of vertices, number of edges
	is >> m_directed;
	is >> num_vertices;
	is >> num_edges;

	// Number of properties for vertices, names of properties for vertices
	is >> num_vertices_props;
	vertices_props.reserve(num_vertices_props);

	for(int i = 0; i < num_vertices_props; i++)
	{
		string name;
		is >> name;
		vertices_props.push_back(STR2ID(name));
	}

	// Number of properties for edges, names of properties for edges
	is >> num_edges_props;
	edges_props.reserve(num_edges_props);

	for(int i = 0; i < num_edges_props; i++)
	{
		string name;
		is >> name;
		edges_props.push_back(STR2ID(name));
	}

	// Vertices
	for(int j = 0; j < num_vertices; j++)
	{
		int id = 0;
		is >> id;

		ValueVertex* vertex = new ValueVertex(this);
		CountPtr<Value> valvertex(vertex);
		vertex->setItem(STR2ID("__id"), CountPtr<Value>(new ValueInt(id)));

		for(int i = 0; i < num_vertices_props; i++)
		{
			float value = 0.0f;
			is >> value;
			vertex->setItem(vertices_props[i], CountPtr<Value>(new ValueFloat(value)));
		}

		m_vertices.insert(valvertex);
		vertices.insert(make_pair(id, valvertex));
	}

	// Edges
	for(int j = 0; j < num_edges; j++)
	{
		int id = 0;
		is >> id;

		map<int, CountPtr<Value> >::iterator begin = vertices.find(id);
		if(begin == vertices.end())
		{
			stringstream sstream;
			sstream << _("Vertex with ID ") << id << _(" hasn't been defined");
			WARN_P(sstream.str());
			is.close();
			m_vertices.clear();
			m_edges.clear();
			return false;
		}

		is >> id;

		map<int, CountPtr<Value> >::iterator end = vertices.find(id);
		if(end == vertices.end())
		{
			stringstream sstream;
			sstream << _("Vertex with ID ") << id << _(" hasn't been defined");
			WARN_P(sstream.str());
			is.close();
			m_vertices.clear();
			m_edges.clear();
			return false;
		}

		ValueEdge* edge = new ValueEdge(this, begin->second, end->second);
		CountPtr<Value> valedge(edge);
		(*begin).second->toValueVertex()->addEdge(valedge);
		(*end).second->toValueVertex()->addEdge(valedge);

		for(int i = 0; i < num_edges_props; i++)
		{
			float value = 0.0f;
			is >> value;
			edge->setItem(edges_props[i], CountPtr<Value>(new ValueFloat(value)));
		}

		m_edges.insert(valedge);
	}

	if(!is.good())
	{
		WARN_P(_("An error occurred during the graph loading, stream state indicates problem"));
		is.close();
		m_vertices.clear();
		m_edges.clear();
		return false;
	}

	is.close();
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::generateVertex(void)
{
	ACCESS_MUTEX_LOCKER;
	CountPtr<Value> vertex(new ValueVertex(this));
	m_vertices.insert(vertex);
	return vertex;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::generateEdge(CountPtr<Value> begin, CountPtr<Value> end)
{
	ACCESS_MUTEX_LOCKER;

	ValueVertex* bv = begin->toValueVertex();
	ValueVertex* ev = end->toValueVertex();

	if(bv == NULL || ev == NULL)
	{
		WARN_P(_("The parameter is not a vertex"));
		return VALUENULL;
	}

	if(!(bv->getGraph() == this && ev->getGraph() == this))
	{
		WARN_P(_("The vertices belong to the different graphs"));
		return VALUENULL;
	}

	CountPtr<Value> edge(new ValueEdge(this, begin, end));
	m_edges.insert(edge);

	bv->addEdge(edge);
	ev->addEdge(edge);

	return edge;
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::deleteVertex(CountPtr<Value> vertex)
{
	ACCESS_MUTEX_LOCKER;

	ValueVertex* vv = vertex->toValueVertex();

	if(vv == NULL)
	{
		WARN_P(_("The parameter is not a vertex"));
		return;
	}

	CountPtr<Value> edges = vv->getEdgesCopy();
	ValueSet* ev = edges->toValueSet();
	assert(ev != NULL);

	set_container::iterator it;
	for(it = ev->begin(); it != ev->end(); ++it)
	{
		(*it)->toValueEdge()->removeVertex(vv);
		deleteEdge(*it);
	}

	vv->clear();
	m_vertices.remove(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::deleteEdge(CountPtr<Value> edge)
{
	ACCESS_MUTEX_LOCKER;

	ValueEdge* ev = edge->toValueEdge();

	if(ev == NULL)
	{
		WARN_P(_("The parameter is not an edge"));
		return;
	}

	if(ev->getBeginVertex()->toValueVertex() != NULL)
		ev->getBeginVertex()->toValueVertex()->deleteEdge(edge);
	if(ev->getEndVertex()->toValueVertex() != NULL)
		ev->getEndVertex()->toValueVertex()->deleteEdge(edge);

	m_edges.remove(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::invertEdgesDirection(void)
{
	ACCESS_MUTEX_LOCKER;

	set_container::iterator it;
	for(it = m_edges.begin(); it != m_edges.end(); ++it)
		(*it)->toValueEdge()->invertDirection();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::toBool(void) const
{
	ACCESS_MUTEX_LOCKER;
	return !m_vertices.empty();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::isDirected(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_directed;
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::setDirected(bool directed)
{
	ACCESS_MUTEX_LOCKER;
	bool ret = m_directed;
	m_directed = directed;
	return ret;
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueGraph::getNumVertices(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.getSize();
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueGraph::getNumEdges(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.getSize();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::containsVertex(CountPtr<Value> vertex) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.contains(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::containsEdge(CountPtr<Value> edge) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.contains(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::getAdjacencyMatrix(void) const
{
	ACCESS_MUTEX_LOCKER;

	int size = m_vertices.getSize();
	map<ValueVertex*, int> trans_table;
	vector< vector<int> > matrix(size, vector<int>(size, 0));

	// Array of indices
	int pos = 0;
	set_container::const_iterator it;
	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
		trans_table[(*it)->toValueVertex()] = pos++;

	// Adjacency Matrix
	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		CountPtr<Value> neighbors = (*it)->toValueVertex()->getNeighbors();
		ValueSet* vertices = neighbors->toValueSet();
		assert(vertices != NULL);
		set_container::const_iterator vertex;

		for(vertex = vertices->begin(); vertex != vertices->end(); ++vertex)
		{
			if(!isDirected() && *vertex == *it)
				matrix[trans_table[(*vertex)->toValueVertex()]][trans_table[(*it)->toValueVertex()]] += 2;
			else
				++matrix[trans_table[(*vertex)->toValueVertex()]][trans_table[(*it)->toValueVertex()]];
		}
	}

	// Convert the matrix to the script form
	ValueArray* ret = new ValueArray(size);
	for(int j = 0; j < size; j++)
	{
		ValueArray* line = new ValueArray(size);
		ret->setItem(j, CountPtr<Value>(line));

		for(int i = 0; i < size; i++)
			line->setItem(i, CountPtr<Value>(new ValueInt(matrix[i][j])));
	}

	return CountPtr<Value>(ret);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::setPropertyToAllVertices(identifier name, CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;
	m_vertices.setPropertyToAllStructItems(name, value);
}

void ValueGraph::setPropertyToAllEdges(identifier name, CountPtr<Value> value)
{
	ACCESS_MUTEX_LOCKER;
	m_edges.setPropertyToAllStructItems(name, value);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::findVertex(ValueVertex* vertex) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.findItem(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<Graph>" << endl;

	dumpIndent(os, indent+1);
	os << "<Vertices>" << endl;

	m_vertices.dump(os, indent+2);

	dumpIndent(os, indent+1);
	os << "</Vertices>" << endl;

	dumpIndent(os, indent+1);
	os << "<Edges>" << endl;

	m_edges.dump(os, indent+2);

	dumpIndent(os, indent+1);
	os << "</Edges>" << endl;

	dumpIndent(os, indent);
	os << "</Graph>" << endl;
}

ostream& operator<<(ostream& os, const ValueGraph& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::add(const Value& right)    const { return right.add(*this); } // +
CountPtr<Value> ValueGraph::sub(const Value& right)    const { return right.sub(*this); } // -
CountPtr<Value> ValueGraph::mult(const Value& right)   const { return right.mult(*this); } // *
CountPtr<Value> ValueGraph::div(const Value& right)    const { return right.div(*this); } // /
CountPtr<Value> ValueGraph::mod(const Value& right)    const { return right.mod(*this); } // %
CountPtr<Value> ValueGraph::eq(const Value& right)     const { return right.eq(*this); } // ==
CountPtr<Value> ValueGraph::eq(const ValueGraph& left) const { return (&left == this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueGraph::ne(const Value& right)     const { return right.ne(*this); } // !=
CountPtr<Value> ValueGraph::ne(const ValueGraph& left) const { return (&left != this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
CountPtr<Value> ValueGraph::le(const Value& right)     const { return right.le(*this); } // <=
CountPtr<Value> ValueGraph::ge(const Value& right)     const { return right.ge(*this); } // >=
CountPtr<Value> ValueGraph::lt(const Value& right)     const { return right.lt(*this); } // <
CountPtr<Value> ValueGraph::gt(const Value& right)     const { return right.gt(*this); } // >
CountPtr<Value> ValueGraph::member(const Value& right) const { return right.member(*this); } // .
CountPtr<Value> ValueGraph::index(const Value& right)  const { return right.index(*this); } // []
CountPtr<Value> ValueGraph::logNOT(void)               const { ACCESS_MUTEX_LOCKER; return (m_vertices.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
