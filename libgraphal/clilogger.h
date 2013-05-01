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


#ifndef CLILOGGER_HPP
#define CLILOGGER_HPP

#include "general.h"
#include "logger.h"


class CliLogger : public Logger
{
public:
	CliLogger(void);
	virtual ~CliLogger(void);

	virtual void dump(ostream& os, uint indent) const;

public:
	virtual void error(const string& str);
	virtual void errorPos(const string& str);
	virtual void errorPos(const string& pos, const string& str);

	virtual void warn(const string& str);
	virtual void warnPos(const string& str);
	virtual void warnPos(const string& pos, const string& str);

	virtual void info(const string& str);
	virtual void infoPos(const string& str);

	virtual void scriptStdout(const string& str);
};

#endif // CLILOGGER_HPP
