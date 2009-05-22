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


#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <deque>
#include <map>
#include <set>
#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"
#include "stringtable.hpp"
#include "codeposition.hpp"
#include "objectcreator.hpp"
#include "callstackitem.hpp"

#define STR2ID(str) CONTEXT.getStringTable()->getID(str)
#define ID2STR(id) CONTEXT.getStringTable()->getString(id)

class NodeFunction;

// Singleton
class Context : public BaseObject
{
public:
	Context(void);
	virtual ~Context(void);

	virtual void clear(void);
	void dump(ostream& os, uint indent) const;
	int executeScriptMain(int argc, char** argv);
	virtual void stopScript(void);

	bool isVariableSet(identifier name);
	CountPtr<Value> getLocalVariable(identifier name);
	CountPtr<Value> setLocalVariable(identifier name, CountPtr<Value> val);
	CountPtr<Value> setLocalVariableAllowRef(identifier name, CountPtr<Value> val);
	void deleteLocalVariable(identifier name);
	CountPtr<Value> propagateGlobalVariable(identifier name);

	void pushLocal(identifier function_name, const CodePosition* return_address);
	void popLocal(void);
	identifier getExecutedFunctionName(void) const { return m_call_stack.back().getFunctionName(); }
	int getStackSize(void) const { return m_call_stack.size(); }
	void printStackTrace() const;
	const deque<CallStackItem>& getCallStack(void) const { return m_call_stack; }

	NodeFunction* getFunction(identifier name);
	void addFunction(NodeFunction* function);

	StringTable* getStringTable(void) { return &m_stringtable; }

	// TODO: move to settings class
	void addIncludeDirectory(const string& directory);
	string getIncludeFullPath(const string& filename) const;

	virtual void setPosition(const CodePosition* pos) { m_position = pos; }
	virtual void setPositionEnterToFunction(const CodePosition* pos) { m_position = pos; }
	virtual void setPositionReturnFromFunction(const CodePosition* pos) { m_position = pos; }
	const CodePosition* getPosition(void) const { return m_position; }

	virtual void breakpoint(void);
	virtual void debugRun(void) { }
	virtual void debugStep(void) { }
	virtual void debugOver(void) { }
	virtual void debugOut(void) { }

private:
	Context(const Context& object);
	Context& operator=(const Context& object);

private:
	map<identifier, NodeFunction*> m_functions;
	map<identifier, CountPtr<Value> > m_global_variables;
	deque<CallStackItem> m_call_stack;
	const CodePosition* m_position;
	StringTable m_stringtable;

	set<string> m_include_dirs;
};

ostream& operator<<(ostream& os, const Context& node);

#endif /* CONTEXT_HPP */
