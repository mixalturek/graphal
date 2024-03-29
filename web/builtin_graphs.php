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


$g_title = 'Graph Functions';
include 'p_begin.php';
?>

<p>Vertices and edges have the same behavior as structures. Dot notation <em>object.value</em> can be used to access their properties.</p>


<p>Return a newly created graph.</p>

<pre class="spec">
graph() : graph
</pre>


<p>Load a graph from a file (<?php Web('graphs_format', 'file format'); ?>).</p>

<pre class="spec">
loadFromFile(graph, string) : bool
</pre>


<p>Check if a graph is directed.</p>

<pre class="spec">
isDirected(graph) : bool|null
</pre>


<p>Set a new value of directed flag and return the previous value.</p>

<pre class="spec">
setDirected(graph, number) : bool|null
</pre>


<p>Invert the direction of edges in a graph.</p>

<pre class="spec">
invertEdgesDirection(graph) : null
</pre>


<p>Create a new vertex in a graph.</p>

<pre class="spec">
generateVertex(graph) : vertex|null
</pre>


<p>Create a new edge in a graph.</p>

<pre class="spec">
generateEdge(graph, vertex, vertex) : edge|null
</pre>


<p>Delete a vertex from a graph.</p>

<pre class="spec">
deleteVertex(graph, vertex) : null
</pre>


<p>Delete an edge from a graph.</p>

<pre class="spec">
deleteEdge(graph, edge) : null
</pre>


<p>Get count of vertices in a graph.</p>

<pre class="spec">
getNumVertices(graph) : int|null
</pre>


<p>Get count of edges in a graph.</p>

<pre class="spec">
getNumEdges(graph) : int|null
</pre>


<p>Get graph's vertices as a set object.</p>

<pre class="spec">
getVertices(graph) : set|null
</pre>


<p>Get graph's edges as a set object.</p>

<pre class="spec">
getEdges(graph) : set|null
</pre>


<p>Get degree of a vertex.</p>

<pre class="spec">
getDegree(vertex) : int|null
</pre>


<p>Get all neighbors of a vertex as a set object.</p>

<pre class="spec">
getNeighbors(vertex) : set|null
</pre>


<p>Get the begin vertex of an edge. If the graph is not directed, one of the edge's vertices will be returned.</p>

<pre class="spec">
getBeginVertex(edge) : vertex|null
</pre>


<p>Get the end vertex of an edge. If the graph is not directed, one of the edge's vertices will be returned.</p>

<pre class="spec">
getEndVertex(edge) : vertex|null
</pre>


<p>Create adjacency matrix from a graph. 2D array (array containing arrays in all items) will be returned.</p>

<pre class="spec">
getAdjacencyMatrix(graph) : array
</pre>


<p>Set property with name <em>string</em> and value <em>object</em> to all vertices of a graph.</p>

<pre class="spec">
setPropertyToAllVertices(graph, string, object) : null
</pre>


<p>Set property with name <em>string</em> and value <em>object</em> to all edges of a graph.</p>

<pre class="spec">
setPropertyToAllEdges(graph, string, object) : null
</pre>


<h2>Examples</h2>

<p>Manual graph generation and recursive depth first search.</p>

<pre class="code">
define("NUM_VERTICES", "10"); // In one layer
define("NEW", "0");
define("CLOSED", "1");

// Recursive depth first search
function dfs(v)
{
	if(v.state == CLOSED)
		return;

	echo("Closing vertex: " + v.num + "\n");
	v.state = CLOSED;

	foreach(neighbor; v.getNeighbors())
		dfs(neighbor);
}

// Generate testing graph and run DFS
function main(argv)
{
//	o ----- o ----- o ----- ...
//	|       |       |
//	|       |       |
//	o       o       o

	g = graph();
	v1 = g.generateVertex();
	v1.num = 0;
	first = v1;

	// Generate first layer
	for(i = 1; i &lt; NUM_VERTICES; i++)
	{
		v2 = g.generateVertex();
		v2.num = i;

		g.generateEdge(v1, v2);
		v1 = v2;
	}

	// Generate second layer
	foreach(v1; g.getVertices())
	{
		v2 = g.generateVertex();
		v2.num = i++;
		g.generateEdge(v1, v2);
	}

	// Initialize states
	foreach(v; g.getVertices())
		v.state = NEW;

	// Run dfs algorithm (pass any vertex)
	dfs(first);
}
</pre>

<pre class="screen">
Closing vertex: 0
Closing vertex: 1
Closing vertex: 2
Closing vertex: 3
Closing vertex: 11
Closing vertex: 4
Closing vertex: 5
Closing vertex: 6
Closing vertex: 7
Closing vertex: 17
Closing vertex: 8
Closing vertex: 9
Closing vertex: 18
Closing vertex: 16
Closing vertex: 12
Closing vertex: 15
Closing vertex: 19
Closing vertex: 10
Closing vertex: 14
Closing vertex: 13
</pre>


<p>Load a graph from a file and print its adjacency matrix.</p>

<pre class="code">
function displayAdjacencyMatrix(matrix, vertices)
{
	echo("  |");
	foreach(vertex; vertices.iterator())
		echo("" + vertex.__id + " ");

	echo("\n--+-------\n");

	it = vertices.iterator();

	foreach(line; matrix.iterator())
	{
		if(it.hasNext())
			vertex = it.next();

		echo("" + vertex.__id + " |");
		foreach(item; line.iterator())
			echo("" + item + " ");

		echo("\n");
	}
}

function main(argv)
{
	g = graph();
	assert(g.loadFromFile("../graphs/00_simple.txt"));
	displayAdjacencyMatrix(g.getAdjacencyMatrix(), g.getVertices());
}
</pre>

<pre class="screen">
  |1 3 0 2
--+-------
1 |0 1 1 1
3 |1 0 1 1
0 |1 1 0 1
2 |1 1 1 0
</pre>


<?php
include 'p_end.php';
?>
