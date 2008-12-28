/*
 *      context.hpp
 *
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


#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <deque>
#include <map>
#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"


class NodeFunction;

class Context: public BaseObject
{
public:
	Context();
	virtual ~Context();

	void dump(ostream& os, uint indent) const;

	CountPtr<Value> getLocalVariable(identifier name);
	CountPtr<Value> setLocalVariable(identifier name, CountPtr<Value> val);

	void pushLocal(void);
	void popLocal(void);

	NodeFunction* getFunction(identifier name);
	void addFunction(identifier name, NodeFunction* function);

private:
	Context(const Context& object);
	Context& operator=(const Context& object);

private:
	map<identifier, NodeFunction*> m_functions;
	deque< map<identifier, CountPtr<Value> > > m_local_variables;
};

ostream& operator<<(ostream& os, const Context& node);

#endif /* CONTEXT_HPP */
