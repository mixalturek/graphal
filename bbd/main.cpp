/*
 *      main.cpp
 *
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

int parseCode(const string& str, bool is_file);


void runUnitTests(void)
{
	Tests* tests = new Tests();
	tests->run();
	delete tests;
	tests = NULL;
}


void usage(int /* argc */, char** argv)
{
	ERROR << _("Usage: ") << argv[0] << " [--unit-tests] [--ast-dump] " << _("<filename>") << endl;
}


int main(int argc, char** argv)
{
	INFO << "bbd [svn version 60]" << endl;

	if(argc < 2)
	{
		usage(argc, argv);
		return 1;
	}

	try
	{
		uint number_of_static_objects = BaseObject::getNumberOfLeaks();


		bool unit_tests = false;
		bool ast_dump = false;


		for(int i = 1; i < argc; i++)
		{
			if(!unit_tests && string(argv[i]) == string("--unit-tests"))
				unit_tests = true;

			if(!ast_dump && string(argv[i]) == string("--ast-dump"))
				ast_dump = true;
		}


		if(unit_tests)
		{
			runUnitTests();
			CONTEXT.clear();
		}


		parseCode(argv[argc-1], true);

		if(ast_dump)
			CONTEXT.dump(cout, 0);

		CONTEXT.execute(argc, argv);
		CONTEXT.clear();


#ifdef CHECK_MEMORY_LEAKS
		BaseObject::printMemoryLeaks(number_of_static_objects);
#endif // CHECK_MEMORY_LEAKS
	}
	catch(runtime_error& ex)
	{
		ERROR << ex.what() << endl;
		return 1;
	}
	catch(exception& ex)
	{
		ERROR << ex.what() << endl;
		return 1;
	}
	catch(...)
	{
		ERROR << _("Unknown exception catched!") << endl;
		return 1;
	}

	return 0;
}
