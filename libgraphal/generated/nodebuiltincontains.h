/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
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

/****************************************************************************
 *                                                                          *
 *             This file was generated by gen_builtin.pl script.            *
 *                        Don't update it manually!                         *
 *                                                                          *
 ****************************************************************************/


#ifndef NODEBUILTINCONTAINS_H
#define NODEBUILTINCONTAINS_H

#include "general.h"
#include "nodefunctionbuiltin.h"

class NodeBuiltinContains : public NodeFunctionBuiltin
{
public:
	NodeBuiltinContains(identifier name, list<identifier>* parameters);
	virtual ~NodeBuiltinContains(void);

	virtual CountPtr<Value> execute(void);

private:
	NodeBuiltinContains(void);
	NodeBuiltinContains(const NodeBuiltinContains& object);
	NodeBuiltinContains& operator=(const NodeBuiltinContains& object);
};

ostream& operator<<(ostream& os, const NodeBuiltinContains& node);

#endif /* NODEBUILTINCONTAINS_H */

