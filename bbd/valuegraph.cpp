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
#include "valuegraph.hpp"
#include "logger.hpp"
#include "valuebool.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
#include "context.hpp"
#include "valueint.hpp"
#include "valuefloat.hpp"
#include "objectcreator.hpp"
#include "valuearray.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueGraph::ValueGraph(bool directed)
	: Value(),
	m_directed(directed),
	m_vertices(),
	m_edges(),
	m_vertices_deleted(),
	m_edges_deleted()
{

}

ValueGraph::~ValueGraph()
{
	ACCESS_MUTEX_LOCKER;
	for_each(m_vertices.begin(), m_vertices.end(), DeleteObject());
	for_each(m_edges.begin(), m_edges.end(), DeleteObject());
	for_each(m_vertices_deleted.begin(), m_vertices_deleted.end(), DeleteObject());
	for_each(m_edges_deleted.begin(), m_edges_deleted.end(), DeleteObject());
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
	map<int, ValueVertex*> vertices;

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
		vertex->setItem(STR2ID("__id"), CountPtr<Value>(new ValueInt(id)));

		for(int i = 0; i < num_vertices_props; i++)
		{
			float value = 0.0f;
			is >> value;
			vertex->setItem(vertices_props[i], CountPtr<Value>(new ValueFloat(value)));
		}

		m_vertices.insert(vertex);
		vertices.insert(make_pair(id, vertex));
	}

	// Edges
	for(int j = 0; j < num_edges; j++)
	{
		int id = 0;
		is >> id;

		ValueVertex* begin = vertices[id];
		if(begin == NULL)
		{
			stringstream sstream;
			sstream << _("Vertex with ID ") << id << _(" hasn't been defined");
			WARN_P(sstream.str());
			is.close();
			return false;
		}

		is >> id;

		ValueVertex* end = vertices[id];
		if(end == NULL)
		{
			stringstream sstream;
			sstream << _("Vertex with ID ") << id << _(" hasn't been defined");
			WARN_P(sstream.str());
			is.close();
			return false;
		}

		ValueEdge* edge = new ValueEdge(this, begin, end);
		begin->addEdge(edge);
		end->addEdge(edge);

		for(int i = 0; i < num_edges_props; i++)
		{
			float value = 0.0f;
			is >> value;
			edge->setItem(edges_props[i], CountPtr<Value>(new ValueFloat(value)));
		}

		m_edges.insert(edge);
	}

	if(!is.good())
	{
		WARN_P(_("An error occurred during the graph loading, stream state indicates problem"));
		is.close();
		return false;
	}

	is.close();
	return true;
}


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex* ValueGraph::generateVertex(void)
{
	ACCESS_MUTEX_LOCKER;
	ValueVertex* vertex = new ValueVertex(this);
	m_vertices.insert(vertex);
	return vertex;
}

ValueEdge* ValueGraph::generateEdge(ValueVertex* begin, ValueVertex* end)
{
	ACCESS_MUTEX_LOCKER;
	if(!(begin->getGraph() == this && end->getGraph() == this))
	{
		WARN_P(_("Vertex belongs to the different graph"));
		return NULL;
	}

	ValueEdge* edge = new ValueEdge(this, begin, end);
	m_edges.insert(edge);

	begin->addEdge(edge);
	end->addEdge(edge);

	return edge;
}

void ValueGraph::deleteVertex(ValueVertex* vertex)
{
	ACCESS_MUTEX_LOCKER;
	set<ValueEdge*> edges = vertex->getEdgesCopy();

	set<ValueEdge*>::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
		deleteEdge(*it);

	m_vertices.erase(vertex);
	m_vertices_deleted.insert(vertex);
	vertex->clear();
}

void ValueGraph::deleteEdge(ValueEdge* edge)
{
	ACCESS_MUTEX_LOCKER;
	edge->getBeginVertex()->deleteEdge(edge);
	edge->getEndVertex()->deleteEdge(edge);
	m_edges.erase(edge);
	m_edges_deleted.insert(edge);
	edge->clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void ValueGraph::invertEdgesDirection(void)
{
	ACCESS_MUTEX_LOCKER;
	set<ValueEdge*>::iterator eit;
	for(eit = m_edges.begin(); eit != m_edges.end(); eit++)
		(*eit)->invertDirection();
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::getVertices(void) const
{
	ACCESS_MUTEX_LOCKER;
	return CountPtr<Value>(new ValueVertexSet(const_cast<ValueGraph*>(this), m_vertices));
}

CountPtr<Value> ValueGraph::getEdges(void) const
{
	ACCESS_MUTEX_LOCKER;
	return CountPtr<Value>(new ValueEdgeSet(const_cast<ValueGraph*>(this), m_edges));
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
	return m_vertices.size();
}


/////////////////////////////////////////////////////////////////////////////
////

uint ValueGraph::getNumEdges(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.size();
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::contains(ValueVertex* vertex) const
{
	ACCESS_MUTEX_LOCKER;
	return m_vertices.count(vertex);
}


/////////////////////////////////////////////////////////////////////////////
////

bool ValueGraph::contains(ValueEdge* edge) const
{
	ACCESS_MUTEX_LOCKER;
	return m_edges.count(edge);
}


/////////////////////////////////////////////////////////////////////////////
////

CountPtr<Value> ValueGraph::getAdjacencyMatrix(void) const
{
	ACCESS_MUTEX_LOCKER;

	int size = m_vertices.size();
	map<ValueVertex*, int> trans_table;
	vector< vector<int> > matrix(size, vector<int>(size, 0));

	// Array of indices
	int pos = 0;
	set<ValueVertex*>::const_iterator it;
	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
		trans_table[*it] = pos++;

	// Adjacency Matrix
	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		CountPtr<Value> neighbors = (*it)->getNeighbors();
		assert(neighbors->toValueVertexSet() != NULL);
		set<ValueVertex*>& vertices = neighbors->toValueVertexSet()->getVertices();
		set<ValueVertex*>::const_iterator vertex;

		for(vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
		{
			if(!isDirected() && *vertex == *it)
				matrix[trans_table[*vertex]][trans_table[*it]] += 2;
			else
				++matrix[trans_table[*vertex]][trans_table[*it]];
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
	set<ValueVertex*>::iterator it;
	for(it = m_vertices.begin(); it != m_vertices.end(); ++it)
		(*it)->setItem(name, value);
}

void ValueGraph::setPropertyToAllEdges(identifier name, CountPtr<Value> value)
{
	set<ValueEdge*>::iterator it;
	for(it = m_edges.begin(); it != m_edges.end(); ++it)
		(*it)->setItem(name, value);
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

	set<ValueVertex*>::const_iterator itv;
	for(itv = m_vertices.begin(); itv != m_vertices.end(); itv++)
		(*itv)->dump(os, indent+2);

	dumpIndent(os, indent+1);
	os << "</Vertices>" << endl;

	dumpIndent(os, indent+1);
	os << "<Edges>" << endl;

	set<ValueEdge*>::const_iterator ite;
	for(ite = m_edges.begin(); ite != m_edges.end(); ite++)
		(*ite)->dump(os, indent+2);

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

PTR_Value ValueGraph::add(const Value& right)    const { return right.add(*this); } // +
PTR_Value ValueGraph::sub(const Value& right)    const { return right.sub(*this); } // -
PTR_Value ValueGraph::mult(const Value& right)   const { return right.mult(*this); } // *
PTR_Value ValueGraph::div(const Value& right)    const { return right.div(*this); } // /
PTR_Value ValueGraph::mod(const Value& right)    const { return right.mod(*this); } // %
PTR_Value ValueGraph::eq(const Value& right)     const { return right.eq(*this); } // ==
PTR_Value ValueGraph::eq(const ValueGraph& left) const { return (&left == this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueGraph::ne(const Value& right)     const { return right.ne(*this); } // !=
PTR_Value ValueGraph::ne(const ValueGraph& left) const { return (&left != this) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; }
PTR_Value ValueGraph::le(const Value& right)     const { return right.le(*this); } // <=
PTR_Value ValueGraph::ge(const Value& right)     const { return right.ge(*this); } // >=
PTR_Value ValueGraph::lt(const Value& right)     const { return right.lt(*this); } // <
PTR_Value ValueGraph::gt(const Value& right)     const { return right.gt(*this); } // >
PTR_Value ValueGraph::member(const Value& right) const { return right.member(*this); } // .
PTR_Value ValueGraph::index(const Value& right)  const { return right.index(*this); } // []
PTR_Value ValueGraph::logNOT(void)               const { ACCESS_MUTEX_LOCKER; return (m_vertices.empty()) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE; } // !
