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
#include "generated/nodebuiltinvisuseweightwhenpaintingedges.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "objectcreator.h"
#include "visualizationconnector.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinVisUseWeightWhenPaintingEdges::NodeBuiltinVisUseWeightWhenPaintingEdges(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinVisUseWeightWhenPaintingEdges::~NodeBuiltinVisUseWeightWhenPaintingEdges(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinVisUseWeightWhenPaintingEdges::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 1);

	VISUALIZATION_CONNECTOR->visUseWeightWhenPaintingEdges(par[0]->toBool());
	return VALUENULL;

}

ostream& operator<<(ostream& os, const NodeBuiltinVisUseWeightWhenPaintingEdges& node)
{
	node.dump(os, 0);
	return os;
}

