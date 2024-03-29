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

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <sstream>
#include "general.h"
#include "baseobject.h"
#include "objectcreator.h"

#define ERR_P(str) ObjectCreator::getInstance().getLogger()->errorPos(str)
#define WARN_P(str) ObjectCreator::getInstance().getLogger()->warnPos(str)
#define ERR_PP(pos, str) ObjectCreator::getInstance().getLogger()->errorPos((pos), (str))
#define WARN_PP(pos, str) ObjectCreator::getInstance().getLogger()->warnPos((pos), (str))
#define ERR(str) ObjectCreator::getInstance().getLogger()->error(str)
#define WARN(str) ObjectCreator::getInstance().getLogger()->warn(str)
#define INFO(str) ObjectCreator::getInstance().getLogger()->info(str)
#define INFO_P(str) ObjectCreator::getInstance().getLogger()->infoPos(str)
#define SCRIPT_STDOUT(str) ObjectCreator::getInstance().getLogger()->scriptStdout(str)


class Logger : public BaseObject
{
public:
	Logger(void);
	virtual ~Logger(void);

public:
	virtual void error(const string& str) = 0;
	virtual void errorPos(const string& str) = 0;
	virtual void errorPos(const string& pos, const string& str) = 0;

	virtual void warn(const string& str) = 0;
	virtual void warnPos(const string& str) = 0;
	virtual void warnPos(const string& pos, const string& str) = 0;

	virtual void info(const string& str) = 0;
	virtual void infoPos(const string& str) = 0;

	virtual void scriptStdout(const string& str) = 0;

private:
	Logger(const Logger& object);
	Logger& operator=(const Logger& object);
};

#endif
