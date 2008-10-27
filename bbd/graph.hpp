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


#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include "general.hpp"
#include "vertex.hpp"
#include "edge.hpp"

class Graph : public BaseObject
{
public:
	Graph(void) { }
	~Graph(void) { }

	virtual string toString(void) const { return "Graph"; } // TODO:

public:
	Vertex& createNewVertex(void);
	Edge& createNewEdge(uint begin, uint end);

private:
	vector<Vertex> m_vertices;
	vector<Edge> m_edges;
};

#endif
