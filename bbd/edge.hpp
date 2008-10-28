/*
 *      edge.hpp
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


#ifndef EDGE_HPP
#define EDGE_HPP

#include "general.hpp"
#include "valuestruct.hpp"

class Graph;
class Vertex;

class Edge : public ValueStruct
{
public:
	Edge(Graph* graph, Vertex* begin, Vertex* end);
	virtual ~Edge();

	virtual string toString(void) const { return "Edge"; } // TODO:

	Vertex* getBeginVertex(void) { return m_begin; }
	Vertex* getEndVertex(void)   { return m_end; }

private:
	Graph*  m_graph;
	Vertex* m_begin;
	Vertex* m_end;

public:
	// TODO: prekryt operatory z ValueStruct!!!!!
};

#endif
