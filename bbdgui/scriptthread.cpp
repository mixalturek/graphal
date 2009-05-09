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

// TODO: delete
#include <iostream>
using namespace std;

#include "scriptthread.h"
#include "context.hpp"
#include "nodebuiltin_inst.hpp"
#include "logger.hpp"

int parseCode(const string& str);


/////////////////////////////////////////////////////////////////////////////
////

ScriptThread::ScriptThread(QObject* parent)
	: QThread(parent),
	m_scriptFilename("")
{

}

ScriptThread::~ScriptThread(void)
{

}

void ScriptThread::run(void)
{
	CONTEXT.clear();
	generateBuiltinFunctions();

	if(parseCode(m_scriptFilename.toStdString()) == 0)
		CONTEXT.executeScriptMain(0, NULL);
	else
		ERROR_S << _("Error while parsing") << endl;
}
