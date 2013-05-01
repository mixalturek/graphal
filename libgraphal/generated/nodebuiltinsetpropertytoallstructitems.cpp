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
#include "generated/nodebuiltinsetpropertytoallstructitems.h"
#include "valuenull.h"
#include "context.h"
#include "logger.h"
#include "valuearray.h"
#include "valuestruct.h"
#include "valueset.h"
#include "valuestring.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeBuiltinSetPropertyToAllStructItems::NodeBuiltinSetPropertyToAllStructItems(identifier name, list<identifier>* parameters)
	: NodeFunctionBuiltin(name, parameters)
{

}

NodeBuiltinSetPropertyToAllStructItems::~NodeBuiltinSetPropertyToAllStructItems(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////


CountPtr<Value> NodeBuiltinSetPropertyToAllStructItems::execute(void)
{
	vector< CountPtr<Value> > par = getParametersValues();
	assert(par.size() == 3);

	ValueArray* a = NULL;
	ValueStruct* st = NULL;
	ValueSet* se = NULL;
	ValueString* s = NULL;

	if((a = par[0]->toValueArray()) != NULL && (s = par[1]->toValueString()) != NULL)
		a->setPropertyToAllStructItems(STR2ID(s->getVal()), par[2]);
	if((st = par[0]->toValueStruct()) != NULL && (s = par[1]->toValueString()) != NULL)
		st->setPropertyToAllStructItems(STR2ID(s->getVal()), par[2]);
	if((se = par[0]->toValueSet()) != NULL && (s = par[1]->toValueString()) != NULL)
		se->setPropertyToAllStructItems(STR2ID(s->getVal()), par[2]);
	else
		WARN_P(_("Bad parameters type: setPropertyToAllStructItems(array|struct|set, string, object) : null"));

	return VALUENULL;

}

ostream& operator<<(ostream& os, const NodeBuiltinSetPropertyToAllStructItems& node)
{
	node.dump(os, 0);
	return os;
}

