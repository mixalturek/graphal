/*
 * Copyright 2009 Michal Turek
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


/****************************************************************************
 *                                                                          *
 *             This file was generated by gen_builtin.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/


#ifndef NODEBUILTININTERSECTION_H
#define NODEBUILTININTERSECTION_H

#include "general.h"
#include "nodefunctionbuiltin.h"

class NodeBuiltinIntersection : public NodeFunctionBuiltin
{
public:
	NodeBuiltinIntersection(identifier name, list<identifier>* parameters);
	virtual ~NodeBuiltinIntersection(void);

	virtual CountPtr<Value> execute(void);

private:
	NodeBuiltinIntersection(void);
	NodeBuiltinIntersection(const NodeBuiltinIntersection& object);
	NodeBuiltinIntersection& operator=(const NodeBuiltinIntersection& object);
};

ostream& operator<<(ostream& os, const NodeBuiltinIntersection& node);

#endif /* NODEBUILTININTERSECTION_H */

