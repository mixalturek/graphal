/*
 * Copyright 2008 Michal Turek
 *
 * This file is part of Graphal CLI.
 * http://graphal.sourceforge.net/
 *
 * Graphal CLI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal CLI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal CLI.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <typeinfo>
#include <stdexcept>
#include "general.h"
#include "baseobject.h"
#include "logger.h"
#include "tests.h"
#include "context.h"
#include "nodebuiltin_inst.h"
#include "graphal_version.h"
#include "objectcreator.h"
#include "clifactory.h"
#include "valuenull.h"
#include "valuebool.h"


int parseCode(const string& str);


/////////////////////////////////////////////////////////////////////////////
////

void runUnitTests(void)
{
	Tests* tests = new Tests;
	tests->run();
	delete tests;
	tests = NULL;
}


/////////////////////////////////////////////////////////////////////////////
////

void usage(int /* argc */, char** argv)
{
	cout << "Graph Algorithms Interpreter - graphal version " << GRAPHAL_VERSION << endl << endl;

	cout << _("Usage: ") << argv[0]
		<< _(" [-I<directory>] [-u | --unit-tests] [-a | --ast-dump] [-b | --enable-breakpoints] ")
		<< _("<filename> [parameters]") << endl
		<< endl
		<< "\t-I<directory>" << endl
		<< "\t\tSpecify include directories (relative to the current working directory)." << endl
		<< "\t\t-I<directory_1> -I<directory_2> ... -I<directory_N>" << endl
		<< endl
		<< "\t-u | --unit-tests" << endl
		<< "\t\tRun unit tests." << endl
		<< endl
		<< "\t-a | --ast-dump" << endl
		<< "\t\tDump abstract syntax tree of the script." << endl
		<< endl
		<< "\t-b | --breakpoints" << endl
		<< "\t\tEnable breakpoints." << endl
		<< endl
		<< "\tfilename" << endl
		<< "\t\tFile to be executed." << endl
		<< endl
		<< "\tparameters" << endl
		<< "\t\tScript parameters." << endl
		<< endl
		;
}


/////////////////////////////////////////////////////////////////////////////
////

void init(void)
{
	ObjectCreator::initInstance();
	ObjectCreator::getInstance().init(new CliFactory);
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

	if(argc < 2)
	{
		usage(argc, argv);
		destroy();
		return 1;
	}

	bool error_occurred = false;

#ifdef CHECK_MEMORY_LEAKS
	uint number_of_static_objects = BaseObject::getNumberOfLeaks();
#endif // CHECK_MEMORY_LEAKS

	try
	{
		bool unit_tests = false;
		bool ast_dump = false;
		bool breakpoints_enabled = false;
		int i = 0;

		for(i = 1; i < argc; i++)
		{
			string param(argv[i]);

			if(!unit_tests && (param == "--unit-tests" || param == "-u"))
				unit_tests = true;
			else if(!ast_dump && (param == "--ast-dump" || param == "-a"))
				ast_dump = true;
			else if(!breakpoints_enabled && (param == "--breakpoints" || param == "-b"))
				breakpoints_enabled = true;
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

				CONTEXT.enableBreakpoints(breakpoints_enabled);
				CONTEXT.executeScriptMain(argc-i, &argv[i]);
			}
			else
			{
				ERR(_("Error while parsing"));
				error_occurred = true;
			}
		}
	}
	catch(runtime_error& ex)
	{
		ERR(ex.what());
		error_occurred = true;
	}
	catch(exception& ex)
	{
		ERR(ex.what());
		error_occurred = true;
	}
	catch(...)
	{
		ERR(_("Unknown exception caught!"));
		error_occurred = true;
	}

	CONTEXT.clear();

#ifdef CHECK_MEMORY_LEAKS
	BaseObject::printMemoryLeaks(number_of_static_objects);
#endif // CHECK_MEMORY_LEAKS

	if(error_occurred)
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
