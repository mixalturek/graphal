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


#include <vector>
#include "nodefunctionbuiltin.hpp"
#include "context.hpp"
#include "logger.hpp"


/////////////////////////////////////////////////////////////////////////////
////

NodeFunctionBuiltin::NodeFunctionBuiltin(list<identifier>* parameters, identifier name)
	: NodeFunction(parameters, NULL, name)
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
