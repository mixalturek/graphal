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


int main(int /* argc */, char** /* argv */)
{
	try
	{
		uint number_of_static_objects = BaseObject::getNumberOfLeaks();

		Tests* tests = new Tests();
		tests->run();
		delete tests;
		tests = NULL;

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
