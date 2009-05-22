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


#include "guicontext.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiContext::GuiContext(void)
	: QObject(),
	Context(),
	m_accessMutex(),
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
	Context::clear();

	m_steppingType = ST_NONE;
	m_stopScript = false;
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::setPosition(CodePosition* pos)
{
	Context::setPosition(pos);

	m_accessMutex.lock();
	if(m_stopScript)
	{
		m_accessMutex.unlock();
		Context::stopScript();
	}

	switch(m_steppingType)
	{
	case ST_INTO:
		m_accessMutex.unlock();
		breakpoint();
		break;

	case ST_OVER:
		m_accessMutex.unlock();
		if(getStackSize() <= m_callStackSize)
			breakpoint();
		break;

	case ST_OUT:
		m_accessMutex.unlock();
		if(getStackSize() < m_callStackSize)
			breakpoint();
		break;

	case ST_NONE:
	default:
		m_accessMutex.unlock();
		break;
	}
}

void GuiContext::breakpoint(void)
{
	emit breakpointOccured();

	m_dbgMutex.lock();
	m_waitCondition.wait(&m_dbgMutex);
	m_dbgMutex.unlock();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::debugRun(void)
{
	m_accessMutex.lock();
	m_steppingType = ST_NONE;
	m_accessMutex.unlock();

	m_waitCondition.wakeAll();
}

void GuiContext::debugStep(void)
{
	m_accessMutex.lock();
	m_steppingType = ST_INTO;
	m_accessMutex.unlock();

	m_waitCondition.wakeAll();
}

void GuiContext::debugOver(void)
{
	m_accessMutex.lock();
		m_steppingType = ST_OVER;
		m_callStackSize = getStackSize();
	m_accessMutex.unlock();

	m_waitCondition.wakeAll();
}

void GuiContext::debugOut(void)
{
	m_accessMutex.lock();
		m_steppingType = ST_OUT;
		m_callStackSize = getStackSize();

		if(getExecutedFunctionName() == STR2ID("breakpoint"))
			m_callStackSize--;
	m_accessMutex.unlock();

	m_waitCondition.wakeAll();
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiContext::stopScript(void)
{
	m_accessMutex.lock();
	m_stopScript = true;
	m_accessMutex.unlock();

	m_waitCondition.wakeAll();
}
