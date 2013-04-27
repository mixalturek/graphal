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


#include <cassert>
#include "generated/nodebuiltinunion.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "valueset.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinUnion::NodeBuiltinUnion(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinUnion::~NodeBuiltinUnion(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinUnion::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 2);

	ValueSet* vset1 = NULL;
	ValueSet* vset2 = NULL;

	if((vset1 = par[0]->toValueSet()) != NULL && (vset2 = par[1]->toValueSet()) != NULL)
		return vset1->getUnion(*vset2);
	else
	{
		WARN_P(_("Bad parameters type: union(set, set) : set|null"));
		return VALUENULL;
	}

}

ostream& operator<<(ostream& os, const NodeBuiltinUnion& node)
{
	node.dump(os, 0);
	return os;
}

