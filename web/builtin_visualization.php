<?php
/*
 * Copyright 2013 Michal Turek
 *
 * This file is part of Graphal.
 * http://graphal.sourceforge.net/
 *
 * Graphal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Graphal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphal.  If not, see <http://www.gnu.org/licenses/>.
 */


$g_title = 'Visualization functions';
include 'p_begin.php';
?>

<p>The following functions does nothing in the command line interpreter.</p>

<p>The visualization painting expects that all registered vertices contatin <em>__x</em>, <em>__y</em> and <em>__z</em> properties for their positioning in 3D space. The center of the whole graph should be at (0, 0, 0) position to guarantee the proper rotations. Vertices and edges can contatin <em>__r</em>, <em>__g</em> and <em>__b</em> color specification, the values are from 0 to 255. Edges can also set theirs <em>__w</em> property, if <em>visUseWeightWhenPaintingEdges()</em> flag is set, the weight will be added to the <em>Z</em> position coordinate.</p>


<p>Register graph or set for painting. String parameter will be used in the application menu to enable/disable when painting. Three numbers are RGB color components, they can be redefined in the vertex or edge.</p>

<pre class="spec">
visRegister(graph|set, string, number, number, number) : null
</pre>


<p>Set the vertex position in 3D space. Actually set <em>__x</em>, <em>__y</em> and <em>__z</em> properties.</p>

<pre class="spec">
visSetPos(vertex, number, number, number) : null
</pre>


<p>Set vertex or edge color. Actually set <em>__r</em>, <em>__g</em> and <em>__b</em> properties.</p>

<pre class="spec">
visSetColor(vertex|edge, number, number, number) : null
</pre>


<p>Set the view to the scene using <em>X</em>, <em>Y</em> and <em>Z</em> coordinates together with <em>X</em> and <em>Y</em> rotations. The camera is initialized using the following OpenGL code.</p>

<pre class="spec">
visSetView(number, number, number, number, number) : null
</pre>

<pre class="code">
glLoadIdentity();
glTranslatef(m_currentView.getPosX(), m_currentView.getPosY(), m_currentView.getPosZ() - 10.0f);
glRotatef(m_currentView.getRotX(), 1.0f, 0.0f, 0.0f);
glRotatef(m_currentView.getRotY(), 0.0f, 1.0f, 0.0f);
</pre>


<p>If the flag is set, the edge weight (<em>__w</em> property) will be added to the <em>Z</em> position coordinate.</p>

<pre class="spec">
visUseWeightWhenPaintingEdges(bool) : null
</pre>


<p>Take a screenshot of the visualization window and save the image to the specified file.</p>

<pre class="spec">
visScreenshot(string) : null
</pre>


<p>Get the graph specified in the application. Always check the return value for <em>null</em>.</p>

<pre class="spec">
visGetGraph() : graph|null
</pre>


<h3>Examples</h3>

<p>Load graph from the file and register the vertices and edges to be painted using different colors.</p>

<pre class="code">
g = graph();
assert(g.loadFromFile("../graphs/01_house.txt"));
breakpoint(true);
visRegister(g.getVertices(), "vertices", 255, 0, 0);
visRegister(g.getEdges(), "edges", 0, 255, 0);
</pre>


<p>Paint the <em>house</em> edge by edge.</p>

<pre class="code">
define("ZPOS", "0.0");

g = graph();
g.setDirected(true);

v0 = g.generateVertex(); v0.visSetPos(-1,  1, ZPOS);
v1 = g.generateVertex(); v1.visSetPos( 1,  1, ZPOS);
v2 = g.generateVertex(); v2.visSetPos( 1, -1, ZPOS);
v3 = g.generateVertex(); v3.visSetPos(-1, -1, ZPOS);
v4 = g.generateVertex(); v4.visSetPos( 0,  2, ZPOS);

// Use "step over" debugging now
breakpoint(true);
visRegister(g, "graph", 0, 255, 0);
e0 = g.generateEdge(v3, v0);
e1 = g.generateEdge(v0, v1);
e2 = g.generateEdge(v1, v3);
e3 = g.generateEdge(v3, v2);
e4 = g.generateEdge(v2, v0);
e5 = g.generateEdge(v0, v4);
e6 = g.generateEdge(v4, v1);
e7 = g.generateEdge(v1, v2);
g.setDirected(false);
</pre>


<p>Load the graph specified in the application and fallback to default one if no was set.</p>

<pre class="code">
if((g = visGetGraph()) == null)
{
	echo("No graph was set in GUI, using predefined one in the script.\n");
	g = graph();
	assert(g.loadFromFile("../graphs/00_simple.txt"));
}
</pre>



<?php
include 'p_end.php';
?>
