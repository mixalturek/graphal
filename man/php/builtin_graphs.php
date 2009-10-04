<?php
$g_title = 'Graph functions';
include 'p_begin.php';
?>

<p>Vertices and edges have the same behavior as structures, dot notation <em>object.value</em> can be used to access their properties.</p>


<p>Return a newly created graph.</p>

<pre class="spec">
graph() : graph
</pre>


<p>Load graph from the specified file.</p>

<pre class="spec">
loadFromFile(graph, string) : bool
</pre>


<p>Return a newly created vertex set.</p>

<pre class="spec">
vertexset(graph) : vertexset|null
</pre>


<p>Return a newly created edge set.</p>

<pre class="spec">
edgeset(graph) : edgeset|null
</pre>


<p>Check if the graph is directed.</p>

<pre class="spec">
isDirected(graph) : bool|null
</pre>


<p>Set the directed flag to the graph. Return the last value.</p>

<pre class="spec">
setDirected(graph, number) : bool|null
</pre>


<p>Invert the direction of the edges in the graph.</p>

<pre class="spec">
invertEdgesDirection(graph) : null
</pre>


<p>Create a new vertex in the graph.</p>

<pre class="spec">
generateVertex(graph) : vertex|null
</pre>


<p>Create a new edge in the graph.</p>

<pre class="spec">
generateEdge(graph, vertex, vertex) : edge|null
</pre>


<p>Delete the vertex from the graph or vertex set.</p>

<pre class="spec">
deleteVertex(graph|vertexset, vertex) : null
</pre>


<p>Delete the edge from the graph or edge set.</p>

<pre class="spec">
deleteEdge(graph|edgeset, edge) : null
</pre>


<p>Return number of vertices in the graph or vertex set.</p>

<pre class="spec">
getNumVertices(graph|vertexset) : int|null
</pre>


<p>Return number of edges in the graph or edge set.</p>

<pre class="spec">
getNumEdges(graph|edgeset) : int|null
</pre>


<p>Return graph's vertices as a vertex set object.</p>

<pre class="spec">
getVertices(graph) : vertexset|null
</pre>


<p>Return graph's edges as an edge set object.</p>

<pre class="spec">
getEdges(graph) : edgeset|null
</pre>


<p>Return the degree of the vertex.</p>

<pre class="spec">
getDegree(vertex) : int|null
</pre>


<p>Return the neighbors of the vertex as a vertex set object.</p>

<pre class="spec">
getNeighbors(vertex) : vertexset|null
</pre>


<p>Return begin vertex of the edge. If the graph is not directed, one of the edge's vertices will be returned.</p>

<pre class="spec">
getBeginVertex(edge) : vertex|null
</pre>


<p>Return end vertex of the edge. If the graph is not directed, one of the edge's vertices will be returned.</p>

<pre class="spec">
getEndVertex(edge) : vertex|null
</pre>


<p>Add the vertex to the vertex set or edge to the edge set.</p>

<pre class="spec">
add(vertexset|edgeset, vertex|edge) : null
</pre>


<p>Check if the graph, vertex set or edge set contain the vertex or edge.</p>

<pre class="spec">
contains(graph|vertexset|edgeset, vertex|edge) : bool|null
</pre>


<p>Create union from two vertex sets or two edge sets.</p>

<pre class="spec">
union(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
</pre>


<p>Create intersection from two vertex sets or two edge sets.</p>

<pre class="spec">
intersection(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
</pre>


<p>Create difference from two vertex sets or two edge sets.</p>

<pre class="spec">
difference(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
</pre>


<p>Create the adjacency matrix from the graph, 2D array (array containing arrays in all items) is returned. Note that position of the lines/rows may vary during several calls, but the linear combination is always the same.</p>

<pre class="spec">
getAdjacencyMatrix(graph) : array
</pre>


<p>Set property with name <em>string</em> and value <em>object</em> to all vertices of the graph or vertex set.</p>

<pre class="spec">
setPropertyToAllVertices(graph|vertexset, string, object) : null
</pre>


<p>Set property with name <em>string</em> and value <em>object</em> to all edges of the graph or edge set.</p>

<pre class="spec">
setPropertyToAllEdges(graph|edgeset, string, object) : null
</pre>


<h3>Examples</h3>

<p>Graph generation and recursive depth first search</p>

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

	// Run (any vertex first)
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
<p>Graph generation and recursive depth first search</p>

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

	// Run (any vertex first)
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


<p>Load graph from a file and display its adjacency matrix</p>

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
