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


#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <set>
#include <QGLWidget>
#include "visualizationitemdata.h"
#include "visualizationview.h"


typedef vector<VisualizationItemData> VIS_DATA_CONTAINER;
typedef vector<VisualizationView> VIS_VIEW_CONTAINER;

class Visualization : public QGLWidget
{
	Q_OBJECT

public:
	Visualization(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags flags = 0);
	virtual ~Visualization(void);

	void clear(void);
	bool hasGraphs(void) const { return !m_graphs.empty(); }
	bool hasSets(void) const { return !m_sets.empty(); }
	const VIS_DATA_CONTAINER& getGraphs(void) const { return m_graphs; }
	const VIS_DATA_CONTAINER& getSets(void) const { return m_sets; }

	bool hasViews(void) const { return !m_views.empty(); }
	void setCurrentView(const VisualizationView& view) { m_currentView = view; }
	void saveCurrentView(const QString& name);
	const VIS_VIEW_CONTAINER& getViews(void) const { return m_views; }

signals:
	void containersChanged(void);

public slots:
	void visRegister(const VisualizationItemData& item);
	void resetView(void) { m_currentView.clear(); updateGL(); }
	void setView(float x, float y, float z, float rotx, float roty);
	void useWeightWhenPaintingEdges(bool enable);
	void screenshot(const QString& filename);

protected:
	void initializeGL(void);
	void resizeGL(int width, int height);
	void paintGL(void);
	void paintSet(ValueSet* vs, const QColor& color);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	VIS_DATA_CONTAINER m_graphs;
	VIS_DATA_CONTAINER m_sets;

	QPoint m_lastMousePos;
	VisualizationView m_currentView;
	VIS_VIEW_CONTAINER m_views;
	bool m_useWeightWhenPaintingEdges;
};

#endif // VISUALIZATION_H
