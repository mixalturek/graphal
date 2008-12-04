/*
 *      vertex.cpp
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


#include "valuevertex.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex::ValueVertex(ValueGraph* graph)
	: Value(),
	m_graph(graph),
	m_edges()
{

}

ValueVertex::~ValueVertex()
{

}


/////////////////////////////////////////////////////////////////////////////
////

void ValueVertex::addValueEdge(ValueEdge* edge, ORIENTATION orientation)
{
	m_edges.insert(pair<ValueEdge*, ORIENTATION>(edge, orientation));
}

void ValueVertex::deleteValueEdge(ValueEdge* edge, ORIENTATION orientation)
{
	m_edges.erase(pair<ValueEdge*, ORIENTATION>(edge, orientation));
}


/////////////////////////////////////////////////////////////////////////////
////

set<ValueEdge *> ValueVertex::getNeighbors(void)
{
	// TODO: implement the method body
	return set<ValueEdge *>();
}
