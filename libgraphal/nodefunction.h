/*
 *      Copyright 2008 Michal Turek <http://woq.nipax.cz/>
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
