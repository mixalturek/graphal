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


#include <vector>
#include "nodefunctionbuiltin.h"
#include "context.h"
#include "logger.h"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunctionBuiltin::NodeFunctionBuiltin(identifier name, list<identifier>* parameters)
	: NodeFunction(name, parameters)
{

}

NodeFunctionBuiltin::~NodeFunctionBuiltin()
{

}


/////////////////////////////////////////////////////////////////////////////
////

vector< CountPtr<Value> > NodeFunctionBuiltin::getParametersValues(void) const
{
	const list<identifier>& pnames = getParameterNames();
	vector< CountPtr<Value> > pvalues;
	pvalues.reserve(pnames.size());

	list<identifier>::const_iterator it;
	for(it = pnames.begin(); it != pnames.end(); it++)
		pvalues.push_back(CONTEXT.getLocalVariable(*it));

	return pvalues;
}


/////////////////////////////////////////////////////////////////////////////
////

void NodeFunctionBuiltin::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<BuiltinFunction name=\"" << ID2STR(getName()) << "\" id=\"" << getName() << "\" />" << endl;
}
