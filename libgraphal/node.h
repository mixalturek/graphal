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


#ifndef NODE_HPP
#define NODE_HPP

#include "general.h"
#include "baseobject.h"
#include "countptr.h"
#include "value.h"


class Node : public BaseObject
{
public:
	Node(void);
	virtual ~Node(void);

	virtual CountPtr<Value> execute(void) = 0;

private:
	Node(const Node& object);
	Node& operator=(const Node& object);
};

#endif /* NODE_HPP */
