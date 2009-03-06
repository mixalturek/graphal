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
#include "general.hpp"
#include "baseobject.hpp"
#include "countptr.hpp"
#include "value.hpp"
#include "stringtable.hpp"
#include "codeposition.hpp"

#define CONTEXT Context::getInstance()
#define STR2ID(str) Context::getInstance().getStringTable()->getID((str))
#define ID2STR(id) Context::getInstance().getStringTable()->getString((id))

class NodeFunction;

// Singleton
class Context : public BaseObject
{
public:
	static inline Context& getInstance(void)
	{
		return m_instance;
	}

	void clear(void);
	void dump(ostream& os, uint indent) const;
	int executeScriptMain(int argc, char** argv);

	bool isVariableSet(identifier name);
	CountPtr<Value> getLocalVariable(identifier name);
	CountPtr<Value> setLocalVariable(identifier name, CountPtr<Value> val);
	void deleteLocalVariable(identifier name);
	CountPtr<Value> propagateGlobalVariable(identifier name);

	void pushLocal(void);
	void popLocal(void);

	NodeFunction* getFunction(identifier name);
	void addFunction(NodeFunction* function);

	StringTable* getStringTable(void) { return &m_stringtable; }

	// TODO: move to settings class
	void addIncludeDirectory(const string& directory);
	string getIncludeFullPath(const string& filename) const;

	void setPosition(const CodePosition& pos) { m_position = pos; }
	const CodePosition& getPosition(void) const { return m_position; }

private:
	Context(void);
	virtual ~Context(void);
	Context(const Context& object);
	Context& operator=(const Context& object);

private:
	static Context m_instance;

	map<identifier, NodeFunction*> m_functions;
	deque< map<identifier, CountPtr<Value> > > m_local_variables;
	map<identifier, CountPtr<Value> > m_global_variables;
	CodePosition m_position;
	StringTable m_stringtable;

	set<string> m_include_dirs;
};

ostream& operator<<(ostream& os, const Context& node);

#endif /* CONTEXT_HPP */
