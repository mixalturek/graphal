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


#ifndef NODEFUNCTIONBUILTIN_HPP
#define NODEFUNCTIONBUILTIN_HPP

#include <vector>
#include "general.h"
#include "nodefunction.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

class NodeFunctionBuiltin : public NodeFunction
{
public:
	NodeFunctionBuiltin(identifier name, list<identifier>* parameters);
	virtual ~NodeFunctionBuiltin();

	virtual void dump(ostream& os, uint indent) const;
	virtual const CodePosition* declarationPos(void) const { return CONTEXT.getBuiltinDeclarationPos(); }
	virtual bool isBuiltIn(void) const { return true; }

	vector< CountPtr<Value> > getParametersValues(void) const;
};

#endif // NODEFUNCTIONBUILTIN_HPP
