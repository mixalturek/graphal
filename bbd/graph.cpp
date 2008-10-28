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


#include "graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Graph::Graph(bool oriented)
	: BaseObject(),
	m_oriented(oriented),
	m_vertices(),
	m_edges()
{

}

Graph::~Graph()
{
	set<Vertex*>::const_iterator vit;
	for(vit = m_vertices.begin(); vit != m_vertices.end(); vit++)
		delete *vit;

	set<Edge*>::const_iterator eit;
	for(eit = m_edges.begin(); eit != m_edges.end(); eit++)
		delete *eit;
}


/////////////////////////////////////////////////////////////////////////////
////

Vertex* Graph::generateVertex(void)
{
	Vertex* vertex = new Vertex(this);
	m_vertices.insert(vertex);
	return vertex;
}

Edge* Graph::generateEdge(Vertex* begin, Vertex* end)
{
	Edge* edge = new Edge(this, begin, end);
	m_edges.insert(edge);
	begin->addEdge(edge, BEGIN);
	end->addEdge(edge, END);
	return edge;
}

void Graph::deleteVertex(Vertex* vertex)
{
	set< pair<Edge*, ORIENTATION> >& edges = vertex->getEdges();

	set< pair<Edge*, ORIENTATION> >::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
		deleteEdge(it->first);

	m_vertices.erase(vertex);
	delete vertex;
}

void Graph::deleteEdge(Edge* edge)
{
	edge->getBeginVertex()->deleteEdge(edge, BEGIN);
	edge->getEndVertex()->deleteEdge(edge, END);
	m_edges.erase(edge);
	delete edge;
}
