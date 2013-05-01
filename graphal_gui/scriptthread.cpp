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


#include <QStringList>
#include "scriptthread.h"
#include "context.h"
#include "nodebuiltin_inst.h"
#include "logger.h"
#include "settings.h"


int parseCode(const string& str);


/////////////////////////////////////////////////////////////////////////////
////

ScriptThread::ScriptThread(QObject* parent)
	: QThread(parent),
	m_scriptFilename(""),
	m_includeDirectories(),
	m_scriptParameters(),
	m_breakpointsEnabled(true)
{

}

ScriptThread::~ScriptThread(void)
{

}

void ScriptThread::run(void)
{
	Context& context = CONTEXT;

	context.clear();
	context.clearIncludeDirectories();
	generateBuiltinFunctions();

	foreach(QString dir, m_includeDirectories)
		context.addIncludeDirectory(dir.toStdString());

	context.enableBreakpoints(m_breakpointsEnabled);

	try
	{
		if(parseCode(m_scriptFilename.toStdString()) == 0)
		{
			deque<string> params;
			params.push_back(m_scriptFilename.toStdString());
			foreach(QString parameter, m_scriptParameters)
				params.push_back(parameter.toStdString());

			context.executeScriptMain(params);
		}
		else
			ERR(_("Error while parsing"));
	}
	catch(exception& ex)
	{
		ERR(ex.what());
	}
	catch(...)
	{
		ERR(_("Unknown exception caught!"));
	}
}
