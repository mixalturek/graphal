/*
 *      graph.hpp
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


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <set>
#include "general.hpp"
#include "baseobject.hpp"

class Vertex;
class Edge;

class Graph : public BaseObject // TODO: ValueAdapter
{
public:
	Graph(bool oriented = false);
	virtual ~Graph();

	virtual string toString(void) const { return "Graph"; } // TODO:

	bool isOriented(void) const { return m_oriented; }

	Vertex* generateVertex(void);
	Edge* generateEdge(Vertex* begin, Vertex* end);

	void deleteVertex(Vertex* vertex);
	void deleteEdge(Edge* edge);

	uint getNumVertices(void) const { return m_vertices.size(); }
	uint getNumEdges(void) const { return m_edges.size(); }

private:
	bool m_oriented;
	set<Vertex*> m_vertices;
	set<Edge*> m_edges;

public:
	// TODO: prekryt operatory z ValueAdapter!!!!!
};

#endif
