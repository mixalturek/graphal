/*
 * Copyright 2009 Michal Turek
 *
 * This file is part of Graphal GUI.
 * http://graphal.sourceforge.net/
 *
 * Graphal GUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal GUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal GUI.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef GUILOGGER_HPP
#define GUILOGGER_HPP

#include <QObject>
#include "logger.h"


class GuiLogger : public QObject, public Logger
{
	Q_OBJECT

public:
	GuiLogger(void);
	virtual ~GuiLogger(void);

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

signals:
	void error(const QString& str);
	void error(const QString& pos, const QString& str);
	void warn(const QString& str);
	void warn(const QString& pos, const QString& str);
	void info(const QString& str);
	void info(const QString& pos, const QString& str);
	void scriptStdout(const QString& str);
};

#endif // GUILOGGER_HPP
