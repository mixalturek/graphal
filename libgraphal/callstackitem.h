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


#ifndef CALLSTACKITEM_HPP
#define CALLSTACKITEM_HPP

#include <map>
#include "general.h"
#include "baseobject.h"
#include "countptr.h"
#include "value.h"

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

	const map<identifier, CountPtr<Value> >& getVariables(void) const { return m_local_variables; }

private:
	identifier m_function_name;
	const CodePosition* m_return_address;
	map<identifier, CountPtr<Value> > m_local_variables;
};

#endif // CALLSTACKITEM_HPP
