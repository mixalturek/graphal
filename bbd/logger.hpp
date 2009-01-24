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

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "general.hpp"
#include "baseobject.hpp"

#define ERROR Logger::getInstance().error()
#define WARN Logger::getInstance().warn()
#define INFO Logger::getInstance().info()
#define DBG Logger::getInstance().debug()

// Singleton
class Logger : public BaseObject
{
public:
	static inline Logger& getInstance(void)
	{
		return instance;
	}

	ostream& error(void)
	{
		return cerr << _("[e] ");
	}

	ostream& warn(void)
	{
		return cerr << _("[w] ");
	}

	ostream& info(void)
	{
		return cerr << _("[i] ");
	}

	ostream& debug(void)
	{
		return cerr << _("[d] ");
	}

	virtual void dump(ostream& os, uint indent) const;

private:
	static Logger instance;

private:
	Logger(void);
	~Logger(void);

	Logger(const Logger& object);
	Logger& operator=(const Logger& object);
};

ostream& operator<<(ostream& os, const Logger& node);

#endif
