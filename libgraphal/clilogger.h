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