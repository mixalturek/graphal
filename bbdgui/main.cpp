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


#include <QApplication>
#include <QIcon>
#include "mainwindow.h"
#include "settings.h"
#include "objectcreator.hpp"
#include "guifactory.hpp"
#include "valuenull.hpp"
#include "valuebool.hpp"


/////////////////////////////////////////////////////////////////////////////
////

void init(void)
{
	ObjectCreator::initInstance();
	ObjectCreator::getInstance().init(new GuiFactory());
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

int main(int argc, char *argv[])
{
	init();

	Q_INIT_RESOURCE(resources);

	QApplication app(argc, argv);
	app.setOrganizationName("bbdgui");
	app.setOrganizationDomain("woq.nipax.cz");
	app.setApplicationName("bbdgui");
	app.setWindowIcon(QIcon(":/applogo.png"));

	SETTINGS.initSingleton();

	MainWindow mainWin;
	mainWin.show();
	int ret = app.exec();

	destroy();
	return ret;
}
