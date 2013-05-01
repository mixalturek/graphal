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


#include "clilogger.h"
#include "context.h"


/////////////////////////////////////////////////////////////////////////////
////

CliLogger::CliLogger(void)
	: Logger()
{

}

CliLogger::~CliLogger(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void CliLogger::dump(ostream& os, uint indent) const
{
	dumpIndent(os, indent);
	os << "<CliLogger />" << endl;
}

/////////////////////////////////////////////////////////////////////////////
////

void CliLogger::error(const string& str)
{
	cerr << _("[e] ") << str << endl;
}

void CliLogger::errorPos(const string& str)
{
	cerr << _("[e] ") << CONTEXT.getPosition()->toString() << ": " << str << endl;
}

void CliLogger::errorPos(const string& pos, const string& str)
{
	cerr << _("[e] ") << pos << ": " << str << endl;
}

void CliLogger::warn(const string& str)
{
	cerr << _("[w] ") << str << endl;
}

void CliLogger::warnPos(const string& str)
{
	cerr << _("[w] ") << CONTEXT.getPosition()->toString() << ": " << str << endl;
}

void CliLogger::warnPos(const string& pos, const string& str)
{
	cerr << _("[w] ") << pos << ": " << str << endl;
}

void CliLogger::info(const string& str)
{
	cout << _("[i] ") << str << endl;
}

void CliLogger::infoPos(const string& str)
{
	cerr << _("[i] ") << CONTEXT.getPosition()->toString() << ": " << str << endl;
}

void CliLogger::scriptStdout(const string& str)
{
	cout << str;
}
