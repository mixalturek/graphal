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


#ifndef NODEBUILTINISSTRUCT_H
#define NODEBUILTINISSTRUCT_H

#include "general.h"
#include "nodefunctionbuiltin.h"

class NodeBuiltinIsStruct : public NodeFunctionBuiltin
{
public:
	NodeBuiltinIsStruct(identifier name, list<identifier>* parameters);
	virtual ~NodeBuiltinIsStruct(void);

	virtual CountPtr<Value> execute(void);

private:
	NodeBuiltinIsStruct(void);
	NodeBuiltinIsStruct(const NodeBuiltinIsStruct& object);
	NodeBuiltinIsStruct& operator=(const NodeBuiltinIsStruct& object);
};

ostream& operator<<(ostream& os, const NodeBuiltinIsStruct& node);

#endif /* NODEBUILTINISSTRUCT_H */

