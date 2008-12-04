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


#include "valuegraph.hpp"
#include "valuevertex.hpp"
#include "valueedge.hpp"


/////////////////////////////////////////////////////////////////////////////
////

ValueGraph::ValueGraph(bool oriented)
	: BaseObject(),
	m_oriented(oriented),
	m_vertices(),
	m_edges()
{

}

ValueGraph::~ValueGraph()
{
	set<ValueVertex*>::const_iterator vit;
	for(vit = m_vertices.begin(); vit != m_vertices.end(); vit++)
		delete *vit;

	set<ValueEdge*>::const_iterator eit;
	for(eit = m_edges.begin(); eit != m_edges.end(); eit++)
		delete *eit;
}


/////////////////////////////////////////////////////////////////////////////
////

ValueVertex* ValueGraph::generateValueVertex(void)
{
	ValueVertex* vertex = new ValueVertex(this);
	m_vertices.insert(vertex);
	return vertex;
}

ValueEdge* ValueGraph::generateValueEdge(ValueVertex* begin, ValueVertex* end)
{
	ValueEdge* edge = new ValueEdge(this, begin, end);
	m_edges.insert(edge);

	begin->addValueEdge(edge, BEGIN);
	end->addValueEdge(edge, END);

	return edge;
}

void ValueGraph::deleteValueVertex(ValueVertex* vertex)
{
	set< pair<ValueEdge*, ORIENTATION> >& edges = vertex->getValueEdges();

	set< pair<ValueEdge*, ORIENTATION> >::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
		deleteValueEdge(it->first);

	m_vertices.erase(vertex);
	delete vertex;
}

void ValueGraph::deleteValueEdge(ValueEdge* edge)
{
	edge->getBeginValueVertex()->deleteValueEdge(edge, BEGIN);
	edge->getEndValueVertex()->deleteValueEdge(edge, END);
	m_edges.erase(edge);
	delete edge;
}
