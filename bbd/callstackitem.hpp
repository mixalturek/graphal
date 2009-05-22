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


#ifndef CALLSTACKITEM_HPP
#define CALLSTACKITEM_HPP

#include <map>
#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"

class CodePosition;

class CallStackItem : public BaseObject
{
public:
	CallStackItem(identifier function_name, const CodePosition* return_address);
	virtual ~CallStackItem(void);

	void dump(ostream& os, uint indent) const;

	identifier getFunctionName(void) const { return m_function_name; }
	const CodePosition* getReturnAddress(void) const { return m_return_address; }

	bool isVariableSet(identifier name);
	CountPtr<Value> getVariable(identifier name);
	CountPtr<Value> setVariable(identifier name, CountPtr<Value> val);
	CountPtr<Value> setVariableAllowRef(identifier name, CountPtr<Value> val);
	void deleteVariable(identifier name);

private:
	identifier m_function_name;
	const CodePosition* m_return_address;
	map<identifier, CountPtr<Value> > m_local_variables;
};

#endif // CALLSTACKITEM_HPP
