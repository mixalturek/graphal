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


#ifndef GUICONTEXT_H
#define GUICONTEXT_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "context.hpp"


enum SteppingType
{
	ST_NONE = 0,
	ST_INTO,
	ST_OVER,
	ST_OUT
};


class GuiContext : public QObject, public Context
{
	Q_OBJECT

public:
	GuiContext(void);
	virtual ~GuiContext(void);

	virtual void clear(void);

	virtual void setPosition(const CodePosition* pos);

public slots:
	void pauseExecution(void);
	virtual void stopScript(void);
	virtual void breakpoint(void);
	virtual void debugRun(void);
	virtual void debugStep(void);
	virtual void debugOver(void);
	virtual void debugOut(void);
	virtual void enableBreakpoints(bool enable);
	virtual bool isBreakpointsEnabled(void);

signals:
	void executionPaused(void);

private:
	QMutex m_accessMutex;
	QMutex m_dbgMutex;
	QWaitCondition m_waitCondition;
	SteppingType m_steppingType;
	int m_callStackSize;
	bool m_stopScript;
};

#endif // GUICONTEXT_H
