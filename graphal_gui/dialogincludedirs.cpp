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


#include <QFileDialog>
#include "dialogincludedirs.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogIncludeDirs::DialogIncludeDirs(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	connect(ui.buttonAdd, SIGNAL(clicked()), this, SLOT(buttonAddItem()));
	connect(ui.buttonDelete, SIGNAL(clicked()), this, SLOT(buttonDeleteItem()));
	connect(ui.buttonMoveUp, SIGNAL(clicked()), this, SLOT(buttonMoveUp()));
	connect(ui.buttonMoveDown, SIGNAL(clicked()), this, SLOT(buttonMoveDown()));
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogIncludeDirs::buttonAddItem(void)
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Select directory"));

	if(!dir.isEmpty())
	{
		QListWidgetItem* item = new QListWidgetItem(dir, ui.listIncludes);
		ui.listIncludes->addItem(item);
		ui.listIncludes->setCurrentItem(item);
	}
}

void DialogIncludeDirs::buttonDeleteItem(void)
{
	QListWidgetItem* item = ui.listIncludes->takeItem(ui.listIncludes->currentRow());

	if(item != NULL)
	{
		delete item;
		item = NULL;
	}
}

void DialogIncludeDirs::buttonMoveUp(void)
{
	int row = ui.listIncludes->currentRow();
	if(row == 0)
		return;

	QListWidgetItem* item = ui.listIncludes->takeItem(row);
	if(item != NULL)
	{
		ui.listIncludes->insertItem(row-1, item);
		ui.listIncludes->setCurrentItem(item);
	}
}

void DialogIncludeDirs::buttonMoveDown(void)
{
	int row = ui.listIncludes->currentRow();

	QListWidgetItem* item = ui.listIncludes->takeItem(row);
	if(item != NULL)
	{
		ui.listIncludes->insertItem(row+1, item);
		ui.listIncludes->setCurrentItem(item);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

QStringList DialogIncludeDirs::getDirectories(void) const
{
	QStringList ret;
	int rows = ui.listIncludes->count();

	for(int i = 0; i < rows; i++)
		ret << ui.listIncludes->item(i)->text();

	return ret;
}

void DialogIncludeDirs::setDirectories(const QStringList& directories)
{
	ui.listIncludes->clear();
	ui.listIncludes->addItems(directories);
}
