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
#include "visualization.h"
#include "guivisualizationconnector.h"
#include "valuevertex.hpp"
#include "valueedge.hpp"
#include "valuevertexset.hpp"
#include "valueedgeset.hpp"
#include "valuefloat.hpp"
#include "context.hpp"


/////////////////////////////////////////////////////////////////////////////
////

Visualization::Visualization(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags flags)
	: QGLWidget(parent, shareWidget, flags),
	m_vertexSets(),
	m_edgeSets()
{
	GuiVisualizationConnector* viscon = dynamic_cast<GuiVisualizationConnector*>(VISUALIZATION_CONNECTOR);

	qRegisterMetaType< CountPtr<Value> >("CountPtr<Value>");
	connect(viscon, SIGNAL(visRegisterSig(CountPtr<Value>)), this, SLOT(visRegister(CountPtr<Value>)));
}

Visualization::~Visualization(void)
{

}

void Visualization::clear(void)
{
	m_vertexSets.clear();
	m_edgeSets.clear();
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

	glPointSize(10.0f);// TODO: add to settings
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

	identifier id_x = STR2ID("__x");
	identifier id_y = STR2ID("__y");
	identifier id_z = STR2ID("__z");
//	identifier id_w = STR2ID("__w");

	glBegin(GL_POINTS);
	DATA_CONTAINER::iterator its;
	for(its = m_vertexSets.begin(); its != m_vertexSets.end(); ++its)
	{
		QColor color(its->getColor());
		glColor3ub(color.red(), color.green(), color.blue());

		set<ValueVertex*>& vertices = its->getValue()->toValueVertexSet()->getVertices();
		assert(its->getValue()->toValueVertexSet() != NULL);

		set<ValueVertex*>::iterator it;
		for(it = vertices.begin(); it != vertices.end(); ++it)
		{
			ValueVertex* vertex = (*it)->toValueVertex();
			assert(vertex != NULL);

			ValueFloat* val_x = vertex->getItem(id_x)->toValueFloat();
			ValueFloat* val_y = vertex->getItem(id_y)->toValueFloat();
			ValueFloat* val_z = vertex->getItem(id_z)->toValueFloat();

			if(val_x != NULL && val_y != NULL && val_z != NULL)
				glVertex3f(val_x->getVal(), val_y->getVal(), val_z->getVal());
		}
	}
	glEnd();


	glBegin(GL_LINES);
	for(its = m_edgeSets.begin(); its != m_edgeSets.end(); ++its)
	{
		QColor color(its->getColor());
		glColor3ub(color.red(), color.green(), color.blue());

		set<ValueEdge*>& edges = its->getValue()->toValueEdgeSet()->getEdges();
		assert(its->getValue()->toValueEdgeSet() != NULL);
		set<ValueEdge*>::iterator it;

		for(it = edges.begin(); it != edges.end(); ++it)
		{
			ValueEdge* edge = (*it)->toValueEdge();
			assert(edge != NULL);

			ValueVertex* begin = edge->getBeginVertex();
			ValueVertex* end = edge->getEndVertex();

//			ValueFloat* val_w = edge->getItem(id_w)->toValueFloat();
			ValueFloat* val_begin_x = begin->getItem(id_x)->toValueFloat();
			ValueFloat* val_begin_y = begin->getItem(id_y)->toValueFloat();
			ValueFloat* val_begin_z = begin->getItem(id_z)->toValueFloat();
			ValueFloat* val_end_x = end->getItem(id_x)->toValueFloat();
			ValueFloat* val_end_y = end->getItem(id_y)->toValueFloat();
			ValueFloat* val_end_z = end->getItem(id_z)->toValueFloat();

			if(val_begin_x != NULL && val_begin_y != NULL && val_begin_z != NULL
				&& val_end_x != NULL && val_end_y != NULL && val_end_z != NULL)
			{
//				if(val_w != NULL)
//					glLineWidth(val_w->getVal());

//				glBegin(GL_LINES);
				if(begin->getGraph()->isOriented())
					glColor3ub(0, 0, 0);
				glVertex3f(val_begin_x->getVal(), val_begin_y->getVal(), val_begin_z->getVal());

				if(begin->getGraph()->isOriented())
					glColor3ub(color.red(), color.green(), color.blue());
				glVertex3f(val_end_x->getVal(), val_end_y->getVal(), val_end_z->getVal());
//				glEnd();
			}
		}
	}
	glEnd();


/*	glTranslatef(-1.5f,0.0f,-10.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
	glEnd();

	glTranslatef(3.0f,0.0f,0.0f);
	glColor3f(0.5f,0.5f,1.0f);

	glBegin(GL_QUADS);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f, 1.0f, 0.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
	glEnd();
*/
}


/////////////////////////////////////////////////////////////////////////////
////

void Visualization::visRegister(CountPtr<Value> object)
{
	if(object->toValueVertexSet() != NULL)
		m_vertexSets.push_back(ITEM(object, QColor(255, 0, 0)));// TODO: color
	else if(object->toValueEdgeSet() != NULL)
		m_edgeSets.push_back(ITEM(object, QColor(0, 255, 0)));// TODO: color
}
