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


#ifndef OBJECTCREATOR_HPP
#define OBJECTCREATOR_HPP

#include "general.hpp"

#define CREATOR ObjectCreator::getInstance()
#define FACTORY ObjectCreator::getInstance().getFactory()
#define LOGGER ObjectCreator::getInstance().getLogger()
#define CONTEXT ObjectCreator::getInstance().getContext()


class ObjectFactory;
class Logger;
class Context;
class CodePosition;


class ObjectCreator
{
public:
	static inline ObjectCreator& getInstance(void)
	{
		return m_instance;
	}

	void init(ObjectFactory* factory);
	void destroy(void);

	ObjectFactory& getFactory(void) { return *m_factory; }
	Logger* getLogger(void) { return m_logger; }
	Context& getContext(void) { return *m_context; }

	const CodePosition* getBuiltinDeclarationPos(void) const { return m_builtin_declaration_pos; }

private:
	ObjectCreator(void);
	virtual ~ObjectCreator(void);
	ObjectCreator(const ObjectCreator& object);
	ObjectCreator& operator=(const ObjectCreator& object);

private:
	static ObjectCreator m_instance;

	ObjectFactory* m_factory;
	Logger* m_logger;
	Context* m_context;
	const CodePosition* m_builtin_declaration_pos;
};

#endif // OBJECTCREATOR_HPP
