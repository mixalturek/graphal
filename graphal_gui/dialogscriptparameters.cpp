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


#include <QInputDialog>
#include "dialogscriptparameters.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogScriptParameters::DialogScriptParameters(QWidget* parent, Qt::WindowFlags flags)
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

void DialogScriptParameters::buttonAddItem(void)
{
	bool ok;
	QString param = QInputDialog::getText(this, tr("Add item"), tr("Parameter"),
		QLineEdit::Normal, "", &ok);

	if(ok && !param.isEmpty())
	{
		QListWidgetItem* item = new QListWidgetItem(param, ui.listParameters);
		ui.listParameters->addItem(item);
		ui.listParameters->setCurrentItem(item);
	}
}

void DialogScriptParameters::buttonDeleteItem(void)
{
	QListWidgetItem* item = ui.listParameters->takeItem(ui.listParameters->currentRow());

	if(item != NULL)
	{
		delete item;
		item = NULL;
	}
}

void DialogScriptParameters::buttonMoveUp(void)
{
	int row = ui.listParameters->currentRow();
	if(row == 0)
		return;

	QListWidgetItem* item = ui.listParameters->takeItem(row);
	if(item != NULL)
	{
		ui.listParameters->insertItem(row-1, item);
		ui.listParameters->setCurrentItem(item);
	}
}

void DialogScriptParameters::buttonMoveDown(void)
{
	int row = ui.listParameters->currentRow();

	QListWidgetItem* item = ui.listParameters->takeItem(row);
	if(item != NULL)
	{
		ui.listParameters->insertItem(row+1, item);
		ui.listParameters->setCurrentItem(item);
	}
}


/////////////////////////////////////////////////////////////////////////////
////

QStringList DialogScriptParameters::getParameters(void) const
{
	QStringList ret;
	int rows = ui.listParameters->count();

	for(int i = 0; i < rows; i++)
		ret << ui.listParameters->item(i)->text();

	return ret;
}

void DialogScriptParameters::setParameters(const QStringList& parameters)
{
	ui.listParameters->clear();
	ui.listParameters->addItems(parameters);
}

