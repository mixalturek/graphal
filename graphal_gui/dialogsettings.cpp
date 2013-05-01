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


#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "dialogsettings.h"
#include "dialogsettingsvisualization.h"
#include "dialogsettingseditor.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogSettings::DialogSettings(QWidget* parent, Qt::WindowFlags flags)
	: QDialog(parent, flags),
	m_contents(new QListWidget(this)),
	m_pages(new QStackedWidget(this))
{
	setWindowTitle(tr("Settings"));

	m_contents->setMovement(QListView::Static);
	m_contents->setMaximumWidth(128);

	createPages();

	m_contents->setCurrentRow(0);

	QPushButton* closeButton = new QPushButton(tr("Close"));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QHBoxLayout* horizontalLayout = new QHBoxLayout;
	horizontalLayout->addWidget(m_contents);
	horizontalLayout->addWidget(m_pages, 1);

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(closeButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(horizontalLayout);
	mainLayout->addStretch(1);
	mainLayout->addSpacing(12);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);
}

DialogSettings::~DialogSettings(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DialogSettings::createPages(void)
{
	m_pages->addWidget(new DialogSettingsEditor);
	new QListWidgetItem(tr("Editor"), m_contents);

	m_pages->addWidget(new DialogSettingsVisualization);
	new QListWidgetItem(tr("Visualization"), m_contents);

	connect(m_contents, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
			this, SLOT(changePage(QListWidgetItem*, QListWidgetItem*)));
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogSettings::changePage(QListWidgetItem* current, QListWidgetItem* previous)
{
	if(!current)
		current = previous;

	m_pages->setCurrentIndex(m_contents->row(current));
}
