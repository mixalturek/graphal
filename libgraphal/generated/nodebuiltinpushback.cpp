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
#include "generated/nodebuiltinpushback.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "valuearray.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinPushBack::NodeBuiltinPushBack(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinPushBack::~NodeBuiltinPushBack(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinPushBack::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 2);

	ValueArray* a = NULL;

	if((a = par[0]->toValueArray()) != NULL)
	{
		a->pushBack(par[1]);
		return VALUENULL;
	}
	else
	{
		WARN_P(_("Bad parameters type: pushBack(array, object) : null"));
		return VALUENULL;
	}

}

ostream& operator<<(ostream& os, const NodeBuiltinPushBack& node)
{
	node.dump(os, 0);
	return os;
}

