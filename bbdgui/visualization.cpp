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


#include <set>
#include <QMetaType>
#include <QMouseEvent>
#include "visualization.h"
#include "guivisualizationconnector.h"
#include "settings.h"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
#include "valuefloat.hpp"
#include "guicontext.h"


/////////////////////////////////////////////////////////////////////////////
////

Visualization::Visualization(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags flags)
	: QGLWidget(parent, shareWidget, flags),
	m_graphs(),
	m_vertexSets(),
	m_edgeSets(),
	m_lastMousePos(),
	m_currentView(),
	m_views(),
	m_useWeightWhenPaintingEdges(false)
{
	GuiVisualizationConnector* viscon = dynamic_cast<GuiVisualizationConnector*>(VISUALIZATION_CONNECTOR);

	qRegisterMetaType<VisualizationItemData>("VisualizationItemData");
	connect(viscon, SIGNAL(visRegisterSig(VisualizationItemData)),
			this, SLOT(visRegister(VisualizationItemData)));

	connect(viscon, SIGNAL(repaintRequest()), this, SLOT(updateGL()));
	connect(viscon, SIGNAL(setView(float, float, float, float, float)),
			this, SLOT(setView(float, float, float, float, float)));
	connect(viscon, SIGNAL(useWeightWhenPaintingEdges(bool)),
			this, SLOT(useWeightWhenPaintingEdges(bool)));
	connect(viscon, SIGNAL(screenshot(QString)), this, SLOT(screenshot(QString)));

	VisualizationView::initInstance(this);
}

Visualization::~Visualization(void)
{

}

void Visualization::clear(void)
{
	m_graphs.clear();
	m_vertexSets.clear();
	m_edgeSets.clear();
	m_currentView.clear();
	m_useWeightWhenPaintingEdges = false;

	emit containersChanged();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::initializeGL(void)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::resizeGL(int width, int height)
{
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::paintGL(void)
{
	ACCESS_MUTEX_LOCKER;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPointSize(SETTINGS.getVisualizationPointSize());
	glLineWidth(SETTINGS.getVisualizationLineWidth());

	glTranslatef(m_currentView.getPosX(), m_currentView.getPosY(), m_currentView.getPosZ() - 10.0f);
	glRotatef(m_currentView.getRotX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_currentView.getRotY(), 0.0f, 1.0f, 0.0f);

	VIS_DATA_CONTAINER::iterator its;
	for(its = m_graphs.begin(); its != m_graphs.end(); ++its)
	{
		if(its->isEnabled())
		{
			assert(its->getValue()->toValueGraph() != NULL);
			paintVertices(its->getValue()->toValueGraph()->getVerticesSet(), its->getColor());
			paintEdges(its->getValue()->toValueGraph()->getEdgesSet(), its->getColor());
		}
	}

	for(its = m_vertexSets.begin(); its != m_vertexSets.end(); ++its)
	{
		if(its->isEnabled())
		{
			assert(its->getValue()->toValueVertexSet() != NULL);
			paintVertices(its->getValue()->toValueVertexSet()->getVertices(), its->getColor());
		}
	}

	for(its = m_edgeSets.begin(); its != m_edgeSets.end(); ++its)
	{
		if(its->isEnabled())
		{
			assert(its->getValue()->toValueEdgeSet() != NULL);
			paintEdges(its->getValue()->toValueEdgeSet()->getEdges(), its->getColor());
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::paintVertices(const set<ValueVertex*>& vertices, const QColor& color)
{
	identifier id_x = STR2ID("__x");
	identifier id_y = STR2ID("__y");
	identifier id_z = STR2ID("__z");
	identifier id_r = STR2ID("__r");
	identifier id_g = STR2ID("__g");
	identifier id_b = STR2ID("__b");

	glBegin(GL_POINTS);
	set<ValueVertex*>::iterator it;
	for(it = vertices.begin(); it != vertices.end(); ++it)
	{
		ValueVertex* vertex = (*it)->toValueVertex();
		assert(vertex != NULL);

		CountPtr<Value> val_r = vertex->getItem(id_r);
		CountPtr<Value> val_g = vertex->getItem(id_g);
		CountPtr<Value> val_b = vertex->getItem(id_b);

		if(val_r->isNumeric() && val_g->isNumeric() && val_b->isNumeric())
			glColor3ub(val_r->toInt(), val_g->toInt(), val_b->toInt());
		else
			glColor3ub(color.red(), color.green(), color.blue());

		CountPtr<Value> val_x = vertex->getItem(id_x);
		CountPtr<Value> val_y = vertex->getItem(id_y);
		CountPtr<Value> val_z = vertex->getItem(id_z);

		if(val_x->isNumeric() && val_y->isNumeric() && val_z->isNumeric())
			glVertex3f(val_x->toFloat(), val_y->toFloat(), val_z->toFloat());
	}
	glEnd();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::paintEdges(const set<ValueEdge*>& edges, const QColor& color)
{
	identifier id_x = STR2ID("__x");
	identifier id_y = STR2ID("__y");
	identifier id_z = STR2ID("__z");
	identifier id_r = STR2ID("__r");
	identifier id_g = STR2ID("__g");
	identifier id_b = STR2ID("__b");
	identifier id_w = STR2ID("__w");

	glBegin(GL_LINES);
	set<ValueEdge*>::iterator it;
	for(it = edges.begin(); it != edges.end(); ++it)
	{
		ValueEdge* edge = (*it)->toValueEdge();
		assert(edge != NULL);

		ValueVertex* begin = edge->getBeginVertex();
		ValueVertex* end = edge->getEndVertex();

		CountPtr<Value> val_w = edge->getItem(id_w);
		CountPtr<Value> val_begin_x = begin->getItem(id_x);
		CountPtr<Value> val_begin_y = begin->getItem(id_y);
		CountPtr<Value> val_begin_z = begin->getItem(id_z);
		CountPtr<Value> val_end_x = end->getItem(id_x);
		CountPtr<Value> val_end_y = end->getItem(id_y);
		CountPtr<Value> val_end_z = end->getItem(id_z);

		if(val_begin_x->isNumeric() && val_begin_y->isNumeric() && val_begin_z->isNumeric()
			&& val_end_x->isNumeric() && val_end_y->isNumeric() && val_end_z->isNumeric())
		{
			CountPtr<Value> val_r = edge->getItem(id_r);
			CountPtr<Value> val_g = edge->getItem(id_g);
			CountPtr<Value> val_b = edge->getItem(id_b);


			if(begin->getGraph()->isDirected())
				glColor3ub(0, 0, 0);
			else if(val_r->isNumeric() && val_g->isNumeric() && val_b->isNumeric())
				glColor3ub(val_r->toInt(), val_g->toInt(), val_b->toInt());
			else
				glColor3ub(color.red(), color.green(), color.blue());


			if(m_useWeightWhenPaintingEdges && val_w->isNumeric())
				glVertex3f(val_begin_x->toFloat(), val_begin_y->toFloat(), val_begin_z->toFloat() + val_w->toFloat());
			else
				glVertex3f(val_begin_x->toFloat(), val_begin_y->toFloat(), val_begin_z->toFloat());


			if(val_r->isNumeric() && val_g->isNumeric() && val_b->isNumeric())
				glColor3ub(val_r->toInt(), val_g->toInt(), val_b->toInt());
			else
				glColor3ub(color.red(), color.green(), color.blue());


			if(m_useWeightWhenPaintingEdges && val_w->isNumeric())
				glVertex3f(val_end_x->toFloat(), val_end_y->toFloat(), val_end_z->toFloat() + val_w->toFloat());
			else
				glVertex3f(val_end_x->toFloat(), val_end_y->toFloat(), val_end_z->toFloat());
		}
	}
	glEnd();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::visRegister(const VisualizationItemData& item)
{
	if(item.getValue()->toValueVertexSet() != NULL)
		m_vertexSets.push_back(item);
	else if(item.getValue()->toValueEdgeSet() != NULL)
		m_edgeSets.push_back(item);
	else if(item.getValue()->toValueGraph() != NULL)
		m_graphs.push_back(item);

	emit containersChanged();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::mousePressEvent(QMouseEvent* event)
{
	m_lastMousePos = event->pos();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::mouseMoveEvent(QMouseEvent* event)
{
	if(event->buttons() & Qt::LeftButton)
	{
		QPoint diff = (m_lastMousePos - event->pos());

		m_currentView.getPosX() -= diff.x() / 60.0f;
		m_currentView.getPosY() += diff.y() / 60.0f;

		updateGL();
	}

	if(event->buttons() & Qt::RightButton)
	{
		QPoint diff = (m_lastMousePos - event->pos());

		if(event->modifiers() & Qt::ControlModifier)
			m_currentView.getRotX() -= diff.y();
		else if(event->modifiers() & Qt::ShiftModifier)
			m_currentView.getRotY() -= diff.x();
		else
		{
			m_currentView.getRotX() -= diff.y();
			m_currentView.getRotY() -= diff.x();
		}

		updateGL();
	}

	m_lastMousePos = event->pos();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::wheelEvent(QWheelEvent* event)
{
	if(event->orientation() == Qt::Vertical)
	{
		m_currentView.getPosZ() += event->delta() / 120;
		updateGL();
	}
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::saveCurrentView(const QString& name)
{
	m_currentView.setName(name);
	m_views.push_back(m_currentView);
	emit containersChanged();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::setView(float x, float y, float z, float rotx, float roty)
{
	m_currentView.setAll(x, y, z, rotx, roty);
	updateGL();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::useWeightWhenPaintingEdges(bool enable)
{
	m_useWeightWhenPaintingEdges = enable;
	updateGL();
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::screenshot(const QString& filename)
{
	QPixmap pixmap = QPixmap::grabWindow(this->winId());
	pixmap.save(filename);

	GuiContext* context = dynamic_cast<GuiContext*>(&CONTEXT);
	assert(context != NULL);
	context->screenshotEnd();
}
