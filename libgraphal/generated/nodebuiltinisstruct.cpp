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
#include "generated/nodebuiltinisstruct.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "valuebool.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinIsStruct::NodeBuiltinIsStruct(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinIsStruct::~NodeBuiltinIsStruct(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinIsStruct::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 1);

	return (par[0]->toValueStruct() != NULL) ? VALUEBOOL_TRUE : VALUEBOOL_FALSE;

}

ostream& operator<<(ostream& os, const NodeBuiltinIsStruct& node)
{
	node.dump(os, 0);
	return os;
}

