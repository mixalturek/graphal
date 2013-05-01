/*
 * Copyright 2008 Michal Turek
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


#include "guicontext.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiContext::GuiContext(void)
	: QObject(),
	Context(),
	m_dbgMutex(),
	m_waitCondition(),
	m_steppingType(ST_NONE),
	m_callStackSize(0),
	m_stopScript(false)
{

}

GuiContext::~GuiContext(void)
{

}

void GuiContext::clear(void)
{
	ACCESS_MUTEX_LOCKER;
	Context::clear();

	m_steppingType = ST_NONE;
	m_stopScript = false;
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::setPosition(const CodePosition* pos)
{
	Context::setPosition(pos);

	ACCESS_MUTEX->lock();
	if(m_stopScript)
	{
		ACCESS_MUTEX->unlock();
		Context::stopScript();
	}

	switch(m_steppingType)
	{
	case ST_INTO:
		ACCESS_MUTEX->unlock();
		pauseExecution();
		break;

	case ST_OVER:
		ACCESS_MUTEX->unlock();
		if(getStackSize() <= m_callStackSize)
			pauseExecution();
		break;

	case ST_OUT:
		ACCESS_MUTEX->unlock();
		if(getStackSize() < m_callStackSize)
			pauseExecution();
		break;

	case ST_NONE:
	default:
		ACCESS_MUTEX->unlock();
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::pauseExecution(void)
{
	emit executionPaused();

	m_dbgMutex.lock();
	m_waitCondition.wait(&m_dbgMutex);
	m_dbgMutex.unlock();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::breakpoint(void)
{
	ACCESS_MUTEX_LOCKER;

	// Go outside of the breakpoint() inline function and pause
	if(isBreakpointsEnabled())
		debugStep();
}

/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::debugRun(void)
{
	ACCESS_MUTEX_LOCKER;
	m_steppingType = ST_NONE;
	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::debugStep(void)
{
	ACCESS_MUTEX_LOCKER;
	m_steppingType = ST_INTO;
	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::debugOver(void)
{
	ACCESS_MUTEX_LOCKER;
	m_steppingType = ST_OVER;
	m_callStackSize = getStackSize();
	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::debugOut(void)
{
	ACCESS_MUTEX_LOCKER;
	m_steppingType = ST_OUT;
	m_callStackSize = getStackSize();
	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::stopScript(void)
{
	ACCESS_MUTEX_LOCKER;
	m_stopScript = true;
	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::enableBreakpoints(bool enable)
{
	ACCESS_MUTEX_LOCKER;
	Context::enableBreakpoints(enable);
}

bool GuiContext::isBreakpointsEnabled(void)
{
	ACCESS_MUTEX_LOCKER;
	return Context::isBreakpointsEnabled();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::screenshotBegin(void)
{
	m_dbgMutex.lock();
	m_waitCondition.wait(&m_dbgMutex);
	m_dbgMutex.unlock();
}

void GuiContext::screenshotEnd(void)
{
	m_waitCondition.wakeAll();
}
