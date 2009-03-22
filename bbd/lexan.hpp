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

#ifndef LEXAN_HPP
#define LEXAN_HPP

#include <stack>
#include <map>
#include "general.hpp"
#include "baseobject.hpp"
#include "lexaniterator.hpp"
#include "lexantokens.hpp"


class Lexan : public BaseObject
{
public:
	Lexan(identifier filename);
	Lexan(const string& source);
	~Lexan(void);

	virtual void dump(ostream& os, uint indent) const;

	LEXTOKEN nextToken(void);

	int getInt(void) const { return m_int; }
	float getFloat(void) const { return m_float; }
	string& getString(void) { return m_string; }
	identifier getIdentifier(void) { return m_identifier; }

	inline identifier getFile(void) const { return m_source.empty() ? 0 : m_source.top()->getFile(); }
	inline uint getLine(void) const { return m_source.empty() ? 0 : m_source.top()->getLine(); }

	void setCurrentlyProcessedFunction(identifier name) { m_currently_processed_function = name; }

private:
	LEXTOKEN checkKeyword(void);
	bool expandMacro(void);
	void parseInclude(void);
	void parseDefine(void);
	inline void unget(void) { m_source.top()->unget(); }

private:
	stack<LexanIterator*> m_source;
	map<identifier, string> m_defines;

	int m_int;
	float m_float;
	string m_string;
	identifier m_identifier;

	identifier m_currently_processed_function;
};

ostream& operator<<(ostream& os, const Lexan& node);

#endif
