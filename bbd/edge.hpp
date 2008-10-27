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


#ifndef __EDGE_HPP__
#define __EDGE_HPP__

#include "general.hpp"
#include "baseobject.hpp"

class Graph;

class Edge : public BaseObject
{
public:
	Edge(Graph* graph, uint begin, uint end);
	~Edge(void) { }

	virtual string toString(void) const { return "Edge"; } // TODO:

	void setDeleteFlag(bool deleted) { m_deleted = deleted; }

private:
	Graph* m_graph;
	uint m_id_begin;
	uint m_id_end;
	bool m_deleted;
};

#endif
