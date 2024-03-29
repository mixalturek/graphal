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


#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <deque>
#include <map>
#include <set>
#include "general.h"
#include "baseobject.h"
#include "countptr.h"
#include "value.h"
#include "stringtable.h"
#include "codeposition.h"
#include "objectcreator.h"
#include "callstackitem.h"

#define STR2ID(str) CONTEXT.getStringTable()->getID(str)
#define ID2STR(id) CONTEXT.getStringTable()->getString(id)

class NodeFunction;

class Context : public BaseObject
{
public:
	Context(void);
	virtual ~Context(void);

	virtual void clear(void);
	void dump(ostream& os, uint indent) const;
	int executeScriptMain(int argc, char** argv);
	int executeScriptMain(const deque<string>& parameters);
	virtual void stopScript(void);

	bool isVariableSet(identifier name);
	CountPtr<Value> getLocalVariable(identifier name);
	CountPtr<Value> setLocalVariable(identifier name, CountPtr<Value> val);
	CountPtr<Value> setLocalVariableAllowRef(identifier name, CountPtr<Value> val);
	void deleteLocalVariable(identifier name);
	CountPtr<Value> propagateGlobalVariable(identifier name);

	void pushLocal(identifier function_name, const CodePosition* return_address);
	void popLocal(void);
	identifier getExecutedFunctionName(void) const;
	int getStackSize(void) const;
	void printStackTrace() const;
	const deque<CallStackItem>& getCallStack(void) const { return m_call_stack; }

	NodeFunction* getFunction(identifier name);
	void addFunction(NodeFunction* function);

	StringTable* getStringTable(void) { return &m_stringtable; }

	void addIncludeDirectory(const string& directory);
	string getIncludeFullPath(const string& filename) const;
	void clearIncludeDirectories(void);

	virtual void setPosition(const CodePosition* pos);
	virtual void setPositionEnterToFunction(const CodePosition* pos);
	virtual void setPositionReturnFromFunction(const CodePosition* pos);
	const CodePosition* getPosition(void) const { return m_position; }

	virtual void breakpoint(void);
	virtual void debugRun(void) { }
	virtual void debugStep(void) { }
	virtual void debugOver(void) { }
	virtual void debugOut(void) { }
	virtual void enableBreakpoints(bool enable);
	virtual bool isBreakpointsEnabled(void);

	const CodePosition* getBuiltinDeclarationPos(void) const { return m_builtin_declaration_pos; }

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
	bool m_breakpointsEnabled;

	const CodePosition* m_builtin_declaration_pos;
};

ostream& operator<<(ostream& os, const Context& node);

#endif /* CONTEXT_HPP */
