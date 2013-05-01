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


#include "callstackitem.h"
#include "context.h"
#include "valuenull.h"
#include "valuereference.h"


/////////////////////////////////////////////////////////////////////////////
////

CallStackItem::CallStackItem(identifier function_name, const CodePosition* return_address)
	: BaseObject(),
	m_function_name(function_name),
	m_return_address(return_address),
	m_local_variables()
{
	assert(return_address != NULL);
}

CallStackItem::~CallStackItem(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void CallStackItem::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;
	dumpIndent(os, indent);
	os << "<CallStackItem function=\"" << ID2STR(m_function_name) << "\">" << endl;

	m_return_address->dump(os, indent+1);

	map<identifier, CountPtr<Value> >::const_iterator it;
	for(it = m_local_variables.begin(); it != m_local_variables.end(); ++it)
		it->second->dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</CallStackItem>" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

bool CallStackItem::isVariableSet(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	return m_local_variables.count(name);
}

CountPtr<Value> CallStackItem::getVariable(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, CountPtr<Value> >::iterator it = m_local_variables.find(name);

	if(it != m_local_variables.end())
		return it->second;
	else
	{
		// WARN << _("Variable has not been initialized: ") << ID2STR(name) << endl;
		// Variable have to be created because of assigning
		return m_local_variables.insert(pair<identifier, CountPtr<Value> >(name,
				CountPtr<Value>(new ValueReference(VALUENULL)))).first->second;
	}
}


CountPtr<Value> CallStackItem::setVariable(identifier name, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, CountPtr<Value> >::iterator it = m_local_variables.find(name);
	if(it != m_local_variables.end())
	{
		assert((*it).second->toValueReference() != NULL);

		if(val->isLValue())
			(*it).second->toValueReference()->assign(val->getReferredValue());
		else
			(*it).second->toValueReference()->assign(val);
	}
	else
	{
		if(val->isLValue())
			m_local_variables.insert(pair<identifier, CountPtr<Value> >(name,
					CountPtr<Value>(new ValueReference(val->getReferredValue()))));
		else
			m_local_variables.insert(pair<identifier, CountPtr<Value> >(name,
					CountPtr<Value>(new ValueReference(val))));
	}

	return val;
}

CountPtr<Value> CallStackItem::setVariableAllowRef(identifier name, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	deleteVariable(name);

	if(val->isLValue())
		m_local_variables.insert(pair<identifier, CountPtr<Value> >(name, val));
	else
		m_local_variables.insert(pair<identifier, CountPtr<Value> >(name,
				CountPtr<Value>(new ValueReference(val))));

	return val;
}

void CallStackItem::deleteVariable(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	m_local_variables.erase(name);
}
