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


#include <QFontDialog>
#include "dialogsettingseditor.h"
#include "settings.h"


/////////////////////////////////////////////////////////////////////////////
////

DialogSettingsEditor::DialogSettingsEditor(QWidget* parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	const QFont& font(SETTINGS.getEditorFont());
	m_ui.m_fontName->setText(font.family());
	m_ui.m_fontSize->setValue(font.pointSize());
	m_ui.m_tabWidth->setValue(SETTINGS.getTabStopWidth());
	m_ui.m_useSpaces->setChecked(SETTINGS.getUseSpaces());
	m_ui.m_verticalLinePos->setValue(SETTINGS.getVertLinePos());
	m_ui.m_wrapLines->setChecked(SETTINGS.getWrapLines());

	connect(m_ui.m_selectFontButton, SIGNAL(clicked()), this, SLOT(selectFont()));
}

DialogSettingsEditor::~DialogSettingsEditor(void)
{
	QFont font(m_ui.m_fontName->text(), m_ui.m_fontSize->value());
	SETTINGS.setEditorFont(font);
	SETTINGS.setTabStopWidth(m_ui.m_tabWidth->value());
	SETTINGS.setUseSpaces(m_ui.m_useSpaces->isChecked());
	SETTINGS.setVertLinePos(m_ui.m_verticalLinePos->value());
	SETTINGS.setWrapLines(m_ui.m_wrapLines->isChecked());
}


/////////////////////////////////////////////////////////////////////////////
////

void DialogSettingsEditor::changeEvent(QEvent* event)
{
	QWidget::changeEvent(event);
	switch (event->type())
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

void DialogSettingsEditor::selectFont(void)
{
	QFont font(QFontDialog::getFont(NULL, SETTINGS.getEditorFont(), this));
	m_ui.m_fontName->setText(font.family());
	m_ui.m_fontSize->setValue(font.pointSize());
}
