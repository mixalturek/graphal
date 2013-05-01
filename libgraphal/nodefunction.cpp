/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal library.
 * http://graphal.sourceforge.net/
 *
 * Graphal library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "nodefunction.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunction::NodeFunction(identifier name, list<identifier>* parameters)
	: Node(),
	m_parameters((parameters != NULL) ? parameters : new list<identifier>),
	m_name(name)
{

}

NodeFunction::~NodeFunction(void)
{
	delete m_parameters;
	m_parameters = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

ostream& operator<<(ostream& os, const list<identifier>& node)
{
	uint num = node.size();
	if(num == 0)
		return os;

	list<identifier>::const_iterator it = node.begin();

	for(uint i = 0; i < num-1; i++, it++)
		os << ID2STR(*it) << ", ";

	if(num > 0)
		os << ID2STR(*it);

	return os;
}
