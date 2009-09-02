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

#include <typeinfo>
#include <stdexcept>
#include "general.hpp"
#include "baseobject.hpp"
#include "logger.hpp"
#include "tests.hpp"
#include "context.hpp"
#include "nodebuiltin_inst.hpp"
#include "version.hpp"
#include "objectcreator.hpp"
#include "clifactory.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"


int parseCode(const string& str);


/////////////////////////////////////////////////////////////////////////////
////

void runUnitTests(void)
{
	Tests* tests = new Tests();
	tests->run();
	delete tests;
	tests = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void usage(int /* argc */, char** argv)
{
	cout << _("Usage: ") << argv[0] << " [-I<directory>] [--unit-tests] [--ast-dump] " << _("<filename> [parameters]") << endl
		<< endl
		<< "\t-I<directory>" << endl
		<< "\t\tSpecify include directories (relative to the current working directory)" << endl
		<< "\t\t-I<directory_1> -I<directory_2> ... -I<directory_N>" << endl
		<< endl
		<< "\t--unit-tests" << endl
		<< "\t\tRun unit tests" << endl
		<< endl
		<< "\t--ast-dump" << endl
		<< "\t\tDump abstract syntax tree of the script" << endl
		<< endl
		<< "\tfilename" << endl
		<< "\t\tFile to be executed" << endl
		<< endl
		<< "\tparameters" << endl
		<< "\t\tScript parameters" << endl
		<< endl
		;
}


/////////////////////////////////////////////////////////////////////////////
////

void init(void)
{
	ObjectCreator::initInstance();
	ObjectCreator::getInstance().init(new CliFactory());
	ValueNull::initInstance();
	ValueBool::initInstance();
}

void destroy(void)
{
	ValueBool::destroyInstance();
	ValueNull::destroyInstance();
	ObjectCreator::destroyInstance();
}


/////////////////////////////////////////////////////////////////////////////
////

int main(int argc, char** argv)
{
	init();

	cout << "bbd [svn version " << SVN_VERSION << "]" << endl;

	if(argc < 2)
	{
		usage(argc, argv);
		destroy();
		return 1;
	}

	bool error_occured = false;

#ifdef CHECK_MEMORY_LEAKS
	uint number_of_static_objects = BaseObject::getNumberOfLeaks();
#endif // CHECK_MEMORY_LEAKS

	try
	{
		bool unit_tests = false;
		bool ast_dump = false;
		int i = 0;

		for(i = 1; i < argc; i++)
		{
			string param(argv[i]);

			if(!unit_tests && param == "--unit-tests")
				unit_tests = true;
			else if(!ast_dump && param == "--ast-dump")
				ast_dump = true;
			else if(param.find("-I") == 0)
			{
				param.erase(0, 2);

				if(param.length() == 0)
				{
					usage(argc, argv);
					WARN(_("There should be no space after -I command line option"));
				}
				else
				{
					if(param[param.length()-1] != '/')
						param.push_back('/');

					CONTEXT.addIncludeDirectory(param);
				}
			}
			else
			{
				// The first unknown parameter should be the filename
				break;
			}
		}


		if(unit_tests)
		{
			runUnitTests();
			CONTEXT.clear();
		}

		generateBuiltinFunctions();

		if(i < argc)
		{
			if(parseCode(argv[i]) == 0)
			{
				if(ast_dump)
					CONTEXT.dump(cout, 0);

				CONTEXT.executeScriptMain(argc-i, &argv[i]);
			}
			else
			{
				ERR(_("Error while parsing"));
				error_occured = true;
			}
		}
	}
	catch(runtime_error& ex)
	{
		ERR(ex.what());
		error_occured = true;
	}
	catch(exception& ex)
	{
		ERR(ex.what());
		error_occured = true;
	}
	catch(...)
	{
		ERR(_("Unknown exception caught!"));
		error_occured = true;
	}

	CONTEXT.clear();

#ifdef CHECK_MEMORY_LEAKS
	BaseObject::printMemoryLeaks(number_of_static_objects);
#endif // CHECK_MEMORY_LEAKS

	if(error_occured)
	{
		INFO(_("*** EXITING MAIN, FAILED ***"));
		destroy();
		return 1;
	}
	else
	{
		INFO(_("*** EXITING MAIN, OK ***"));
		destroy();
		return 0;
	}
}
