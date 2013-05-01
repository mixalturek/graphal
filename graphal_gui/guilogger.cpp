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


#include "guilogger.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

GuiLogger::GuiLogger(void)
	: QObject(),
	Logger()
{

}

GuiLogger::~GuiLogger(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void GuiLogger::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<GuiLogger />" << endl;
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiLogger::error(const string& str)
{
	emit error(QString::fromStdString(str));
}

void GuiLogger::errorPos(const string& str)
{
	emit error(QString::fromStdString(CONTEXT.getPosition()->toString()),
		QString::fromStdString(str));
}

void GuiLogger::errorPos(const string& pos, const string& str)
{
	emit error(QString::fromStdString(pos), QString::fromStdString(str));
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiLogger::warn(const string& str)
{
	emit warn(QString::fromStdString(str));
}

void GuiLogger::warnPos(const string& str)
{
	emit warn(QString::fromStdString(CONTEXT.getPosition()->toString()),
		QString::fromStdString(str));
}

void GuiLogger::warnPos(const string& pos, const string& str)
{
	emit warn(QString::fromStdString(pos), QString::fromStdString(str));
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiLogger::info(const string& str)
{
	emit info(QString::fromStdString(str));
}

void GuiLogger::infoPos(const string& str)
{
	emit info(QString::fromStdString(CONTEXT.getPosition()->toString()),
		QString::fromStdString(str));
}


/////////////////////////////////////////////////////////////////////////////
////

void GuiLogger::scriptStdout(const string& str)
{
	emit scriptStdout(QString::fromStdString(str));
}
