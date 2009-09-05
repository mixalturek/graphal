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


#include <cassert>
#include <fstream>
#include <stdexcept>
#include "context.hpp"
#include "valuenull.hpp"
#include "nodefunction.hpp"
#include "nodefunctioncall.hpp"
#include "valuearray.hpp"
#include "valuestring.hpp"
#include "valuereference.hpp"
#include "nodevalue.hpp"
#include "nodeblock.hpp"
#include "logger.hpp"
#include "exitvalue.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Context::Context()
	: BaseObject(),
	m_functions(),
	m_global_variables(),
	m_call_stack(),
	m_position(NULL),
	m_stringtable(),
	m_include_dirs(),
	m_breakpointsEnabled(true),
	m_builtin_declaration_pos(new CodePosition(m_stringtable.getID(_("built-in function")), 0))
{

}


Context::~Context()
{
	clear();

	if(m_builtin_declaration_pos != NULL)
	{
		delete m_builtin_declaration_pos;
		m_builtin_declaration_pos = NULL;
	}
}


void Context::clear(void)
{
	ACCESS_MUTEX_LOCKER;

	m_global_variables.clear();
	m_call_stack.clear();

	map<identifier, NodeFunction*>::iterator it;
	for(it = m_functions.begin(); it != m_functions.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	m_stringtable.clear();
	m_functions.clear();

	if(m_builtin_declaration_pos != NULL)
	{
		delete m_builtin_declaration_pos;
		m_builtin_declaration_pos = new CodePosition(m_stringtable.getID(_("built-in function")), 0);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::pushLocal(identifier function_name, const CodePosition* return_address)
{
	ACCESS_MUTEX_LOCKER;
	m_call_stack.push_back(CallStackItem(function_name, return_address));
}

void Context::popLocal(void)
{
	ACCESS_MUTEX_LOCKER;
	m_call_stack.pop_back();
}

void Context::printStackTrace() const
{
	ACCESS_MUTEX_LOCKER;

	// TODO: position in the code
	deque<CallStackItem>::const_iterator it;
	for(it = m_call_stack.begin(); it != m_call_stack.end(); it++)
		SCRIPT_STDOUT(ID2STR(it->getFunctionName()) + _("()\n"));
}


/////////////////////////////////////////////////////////////////////////////
////

bool Context::isVariableSet(identifier name)
{
	ACCESS_MUTEX_LOCKER;

	if(m_call_stack.empty())
		return false;

	return m_call_stack.back().isVariableSet(name);
}

CountPtr<Value> Context::getLocalVariable(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	assert(!m_call_stack.empty());
	return m_call_stack.back().getVariable(name);
}


CountPtr<Value> Context::setLocalVariable(identifier name, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	assert(!m_call_stack.empty());
	return m_call_stack.back().setVariable(name, val);
}

CountPtr<Value> Context::setLocalVariableAllowRef(identifier name, CountPtr<Value> val)
{
	ACCESS_MUTEX_LOCKER;
	assert(!m_call_stack.empty());
	return m_call_stack.back().setVariableAllowRef(name, val);
}

void Context::deleteLocalVariable(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	assert(!m_call_stack.empty());
	m_call_stack.back().deleteVariable(name);
}

CountPtr<Value> Context::propagateGlobalVariable(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, CountPtr<Value> >::iterator it = m_global_variables.find(name);
	if(it != m_global_variables.end())
	{
		assert(it->second->isLValue());
		setLocalVariableAllowRef(name, it->second);
		return it->second;
	}
	else
	{
		// Global variable does not exist, create and set local
		CountPtr<Value> tmp(new ValueReference(VALUENULL));
		m_global_variables.insert(pair<identifier, CountPtr<Value> >(name, tmp));

		setLocalVariableAllowRef(name, tmp);
		return tmp;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

NodeFunction* Context::getFunction(identifier name)
{
	ACCESS_MUTEX_LOCKER;
	map<identifier, NodeFunction*>::iterator it = m_functions.find(name);

	if(it != m_functions.end())
		return it->second;
	else
		return NULL;
}

void Context::addFunction(NodeFunction* function)
{
	ACCESS_MUTEX_LOCKER;
	assert(function != NULL);

	pair< map<identifier, NodeFunction*>::iterator, bool> ret
		= m_functions.insert(pair<identifier, NodeFunction*>(function->getName(), function));

	if(!ret.second)
	{
		WARN_PP(function->declarationPos()->toString(),
			_("Function ") + ID2STR(function->getName())
			+ _("() has been already defined, redefinition ignored"));
		WARN_PP(ret.first->second->declarationPos()->toString(),
			ID2STR(function->getName()) + _("()"));

		delete function;
		function = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::dump(ostream& os, uint indent) const
{
	ACCESS_MUTEX_LOCKER;

	dumpIndent(os, indent);
	os << "<Context>" << endl;

	map<identifier, NodeFunction*>::const_iterator it;
	for(it = m_functions.begin(); it != m_functions.end(); it++)
		it->second->dump(os, indent+1);

	m_stringtable.dump(os, indent+1);

	dumpIndent(os, indent);
	os << "</Context>" << endl;
}

ostream& operator<<(ostream& os, const Context& node)
{
	node.dump(os, 0);
	return os;
}


/////////////////////////////////////////////////////////////////////////////
////

int Context::executeScriptMain(int argc, char** argv)
{
	deque<string> parameters;

	for(int i = 0; i < argc; i++)
		parameters.push_back(argv[i]);

	return executeScriptMain(parameters);
}

int Context::executeScriptMain(const deque<string>& parameters)
{
	NodeFunction* maintest = getFunction(getStringTable()->getID("main"));
	if(maintest == NULL)
	{
		ERR(_("Function main(argv) has not been defined in the script, exiting"));
		return 1;
	}
	else if(maintest->getNumberOfParameters() != 1)
	{
		ERR_PP(maintest->declarationPos()->toString(),
			_("Function main(argv) does not expect one parameter, exiting"));
		return 1;
	}

	setPosition(maintest->declarationPos());

	ValueArray* argv_array = new ValueArray;
	argv_array->resize(parameters.size());

	for(uint i = 0; i < parameters.size(); i++)
		argv_array->setItem(i, CountPtr<Value>(new ValueString(parameters[i])));

	NodeFunctionCall main(getStringTable()->getID("main"),
		new NodeBlock(new NodeValue(argv_array)),
		NULL);

	INFO(_("*** ENTERING SCRIPT MAIN ***"));

	try
	{
		CountPtr<Value> main_retval = main.execute();
		INFO(_("*** EXITING SCRIPT MAIN, OK ***"));
		INFO(_("Return value: ") + main_retval->toString());
	}
	catch(ExitValue* ex)
	{
		if(ex->getValue()->isNull())// Context::stopScript()
			INFO(_("*** THE SCRIPT WAS STOPPED ***"));
		else
		{
			INFO(_("*** EXITING SCRIPT MAIN, OK ***"));
			INFO( _("Exit value: ") + ex->getValue()->toString());
		}

		delete ex;
		ex = NULL;
	}
	catch(runtime_error& ex)
	{
		ERR_P(string(_("Runtime error: ")) + ex.what());
		return 1;
	}
	catch(...)
	{
		ERR_P(_("Unexpected exception was thrown from the script!"));
		return 1;
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::stopScript(void)
{
	throw new ExitValue(VALUENULL);
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::addIncludeDirectory(const string& directory)
{
	ACCESS_MUTEX_LOCKER;
	m_include_dirs.insert(directory);
}

string Context::getIncludeFullPath(const string& filename) const
{
	ACCESS_MUTEX_LOCKER;

	ifstream infile;

	set<string>::const_iterator it;
	for(it = m_include_dirs.begin(); it != m_include_dirs.end(); it++)
	{
		infile.open((*it + filename).c_str());

		if(infile.is_open())
		{
			infile.close();
			return *it + filename;
		}
	}

	THROW(runtime_error(_("File was not found, check settings of include directories")));
	return filename;// Should not be called
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::breakpoint(void)
{
	ACCESS_MUTEX_LOCKER;

	// TODO: parse and execute specific commands here?
	if(m_breakpointsEnabled)
	{
		INFO_P(_("Breakpoint, press any key..."));
		getchar();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

identifier Context::getExecutedFunctionName(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_call_stack.back().getFunctionName();
}


/////////////////////////////////////////////////////////////////////////////
////

int Context::getStackSize(void) const
{
	ACCESS_MUTEX_LOCKER;
	return m_call_stack.size();
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::clearIncludeDirectories(void)
{
	ACCESS_MUTEX_LOCKER;
	m_include_dirs.clear();
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::setPosition(const CodePosition* pos)
{
	ACCESS_MUTEX_LOCKER;
	m_position = pos;
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::setPositionEnterToFunction(const CodePosition* pos)
{
	ACCESS_MUTEX_LOCKER;
	m_position = pos;
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::setPositionReturnFromFunction(const CodePosition* pos)
{
	ACCESS_MUTEX_LOCKER;
	m_position = pos;
}


/////////////////////////////////////////////////////////////////////////////
////

void Context::enableBreakpoints(bool enable)
{
	ACCESS_MUTEX_LOCKER;
	m_breakpointsEnabled = enable;
}


/////////////////////////////////////////////////////////////////////////////
////

bool Context::isBreakpointsEnabled(void)
{
	ACCESS_MUTEX_LOCKER;
	return m_breakpointsEnabled;
}
