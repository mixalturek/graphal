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


#include "clilogger.hpp"
#include "context.hpp"


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

void CliLogger::scriptStdout(const string& str)
{
	cout << str;
}
