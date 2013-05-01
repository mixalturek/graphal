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
#include "generated/nodebuiltindifference.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "valueset.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinDifference::NodeBuiltinDifference(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinDifference::~NodeBuiltinDifference(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinDifference::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 2);

	ValueSet* vset1 = NULL;
	ValueSet* vset2 = NULL;

	if((vset1 = par[0]->toValueSet()) != NULL && (vset2 = par[1]->toValueSet()) != NULL)
		return vset1->getDifference(*vset2);
	else
	{
		WARN_P(_("Bad parameters type: difference(set, set) : set|null"));
		return VALUENULL;
	}

}

ostream& operator<<(ostream& os, const NodeBuiltinDifference& node)
{
	node.dump(os, 0);
	return os;
}

