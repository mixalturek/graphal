/*
 *      vertex.hpp
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


#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include "general.hpp"
#include "valuestruct.hpp"

class Graph;

class Vertex : public BaseObject
{
public:
	Vertex(Graph* graph);
	~Vertex(void) { }

	virtual string toString(void) const { return "Vertex"; } // TODO:

	void setDeleted(bool deleted) { m_deleted = deleted; }
	bool isDeleted(void) { return m_deleted; }

private:
	Graph* m_graph;
	bool m_deleted;
	ValueStruct m_properties;
};

#endif
