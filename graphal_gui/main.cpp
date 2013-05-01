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


#include <QApplication>
#include <QIcon>
#include "mainwindow.h"
#include "settings.h"
#include "objectcreator.h"
#include "guifactory.h"
#include "valuenull.h"
#include "valuebool.h"


/////////////////////////////////////////////////////////////////////////////
////

void init(void)
{
	ObjectCreator::initInstance();
	ObjectCreator::getInstance().init(new GuiFactory);
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
	app.setOrganizationName("graphal");
	app.setOrganizationDomain("graphal.sourceforge.net");
	app.setApplicationName("graphal");
	app.setWindowIcon(QIcon(":/applogo.png"));

	SETTINGS.init();

	MainWindow mainWin;
	mainWin.show();
	int ret = app.exec();

	destroy();
	return ret;
}
