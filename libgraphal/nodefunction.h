/*
 * Copyright 2008 Michal Turek
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


#ifndef NODEFUNCTION_HPP
#define NODEFUNCTION_HPP

#include <list>
#include "general.h"
#include "node.h"

class CodePosition;

class NodeFunction : public Node
{
public:
	NodeFunction(identifier name, list<identifier>* parameters);
	virtual ~NodeFunction(void);

	identifier getName(void) const { return m_name; }
	const list<identifier>& getParameterNames(void) const { return *m_parameters; }
	uint getNumberOfParameters(void) const { return m_parameters->size(); }

	virtual const CodePosition* declarationPos(void) const = 0;
	virtual bool isBuiltIn(void) const = 0;

private:
	list<identifier>* m_parameters;
	identifier m_name;// Actually not needed, for dump() only
};

ostream& operator<<(ostream& os, const list<identifier>& node);

#endif // NODEFUNCTION_HPP
