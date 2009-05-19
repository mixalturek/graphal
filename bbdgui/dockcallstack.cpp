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


#include <QTreeView>
#include <QStandardItemModel>
#include "dockcallstack.h"

void addMail(QAbstractItemModel *model, const QString &subject,
			 const QString &sender, const QDateTime &date)
{
	model->insertRow(0);
	model->setData(model->index(0, 0), subject);
	model->setData(model->index(0, 1), sender);
	model->setData(model->index(0, 2), date);
}

QAbstractItemModel *createMailModel(QObject *parent)
{
	QStandardItemModel *model = new QStandardItemModel(0, 3, parent);

	model->setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
	model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

/*
	addMail(model, "Happy New Year!", "Grace K. <grace@software-inc.com>",
			QDateTime(QDate(2006, 12, 31), QTime(17, 03)));
	addMail(model, "Radically new concept", "Grace K. <grace@software-inc.com>",
			QDateTime(QDate(2006, 12, 22), QTime(9, 44)));
	addMail(model, "Accounts", "pascale@nospam.com",
			QDateTime(QDate(2006, 12, 31), QTime(12, 50)));
	addMail(model, "Expenses", "Joe Bloggs <joe@bloggs.com>",
			QDateTime(QDate(2006, 12, 25), QTime(11, 39)));
	addMail(model, "Re: Expenses", "Andy <andy@nospam.com>",
			QDateTime(QDate(2007, 01, 02), QTime(16, 05)));
	addMail(model, "Re: Accounts", "Joe Bloggs <joe@bloggs.com>",
			QDateTime(QDate(2007, 01, 03), QTime(14, 18)));
	addMail(model, "Re: Accounts", "Andy <andy@nospam.com>",
			QDateTime(QDate(2007, 01, 03), QTime(14, 26)));
	addMail(model, "Sports", "Linda Smith <linda.smith@nospam.com>",
			QDateTime(QDate(2007, 01, 05), QTime(11, 33)));
	addMail(model, "AW: Sports", "Rolf Newschweinstein <rolfn@nospam.com>",
			QDateTime(QDate(2007, 01, 05), QTime(12, 00)));
	addMail(model, "RE: Sports", "Petra Schmidt <petras@nospam.com>",
			QDateTime(QDate(2007, 01, 05), QTime(12, 01)));
*/
	return model;
}

/////////////////////////////////////////////////////////////////////////////
////

DockCallStack::DockCallStack(QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(tr("Call stack"), parent, flags),
	m_table(new QTreeView(this)),
	m_itemModel(new QStandardItemModel(0, 3, m_table))
{
	QStringList headers;
	headers << tr("Function") << tr("File") << tr("Line");
	m_itemModel->setHorizontalHeaderLabels(headers);

	m_table->setModel(m_itemModel);
	m_table->setRootIsDecorated(false);
	m_table->setAlternatingRowColors(true);
	m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	setWidget(m_table);
}

DockCallStack::~DockCallStack(void)
{

}


/////////////////////////////////////////////////////////////////////////////
////

void DockCallStack::insert(const QString& function, const QString& filename, int line)
{
	m_itemModel->insertRow(0);
	m_itemModel->setData(m_itemModel->index(0, 0), function);
	m_itemModel->setData(m_itemModel->index(0, 1), filename);
	m_itemModel->setData(m_itemModel->index(0, 2), line);
	m_table->scrollToTop();
}


/////////////////////////////////////////////////////////////////////////////
////

void DockCallStack::clear(void)
{
	m_itemModel->removeRows(0, m_itemModel->rowCount());
}
