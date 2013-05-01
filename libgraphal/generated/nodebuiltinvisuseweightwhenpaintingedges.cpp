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

