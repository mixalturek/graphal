/*
 *	  Copyright 2009 Michal Turek <http://woq.nipax.cz/>
 *
 *	  This program is free software; you can redistribute it and/or modify
 *	  it under the terms of the GNU General Public License as published by
 *	  the Free Software Foundation; either version 2 of the License, or
 *	  (at your option) any later version.
 *
 *	  This program is distributed in the hope that it will be useful,
 *	  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	  GNU General Public License for more details.
 *
 *	  You should have received a copy of the GNU General Public License
 *	  along with this program; if not, write to the Free Software
 *	  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *	  MA 02110-1301, USA.
 */


#include <QFileDialog>
#include <QCloseEvent>
#include <QDebug>
#include "dialogsettingsvisualization.h"
#include "settings.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogSettingsVisualization::DialogSettingsVisualization(QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	m_ui.m_edgesWidth->setValue(SETTINGS.getVisualizationLineWidth());
	m_ui.m_verticesSize->setValue(SETTINGS.getVisualizationPointSize());
	m_ui.m_screenshotDirectory->setText(SETTINGS.getScreenshotsDirectory());

	connect(m_ui.m_browseButton, SIGNAL(clicked()), this, SLOT(selectDirectory()));
}

DialogSettingsVisualization::~DialogSettingsVisualization(void)
{
	SETTINGS.setVisualizationPointSize(m_ui.m_verticesSize->value());
	SETTINGS.setVisualizationLineWidth(m_ui.m_edgesWidth->value());
	SETTINGS.setScreenshotsDirectory(m_ui.m_screenshotDirectory->text());
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogSettingsVisualization::changeEvent(QEvent* e)
{
	QWidget::changeEvent(e);
	switch(e->type())
	{
	case QEvent::LanguageChange:
		m_ui.retranslateUi(this);
		break;
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogSettingsVisualization::selectDirectory(void)
{
	QString directory = QFileDialog::getExistingDirectory(this, tr("Screnshot directory"),
		SETTINGS.getScreenshotsDirectory());

	if(!directory.isEmpty())
		m_ui.m_screenshotDirectory->setText(directory);
}
