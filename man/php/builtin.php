<?php
$g_title = 'Built-in functions';
include 'p_begin.php';
?>


<p>The list of defined built-in functions, their parameters and return values can be displayed using <em>make listbuiltin</em> command.</p>

<pre class="screen">
[woq@evm bbd]$ <strong>make listbuiltin</strong>
echo(object) : object
print(object) : object
println(object) : object
dump(object) : object
exit(object) : null
assert(object) : null
verify(object) : bool
breakpoint(object) : null
isNull(object) : bool
isBool(object) : bool
isInt(object) : bool
isFloat(object) : bool
isString(object) : bool
isStruct(object) : bool
isArray(object) : bool
isGraph(object) : bool
isVertex(object) : bool
isEdge(object) : bool
isVertexSet(object) : bool
isEdgeSet(object) : bool
printStackTrace() : null
iterator(object) : object
hasNext(object) : bool
next(object) : object
resetIterator(object) : object
array(number) : array|null
struct() : struct
size(array|string) : int|null
pushFront(array, object) : null
pushBack(array, object) : null
popFront(array) : null
popBack(array) : null
back(array) : object|null
front(array) : object|null
graph() : graph
loadFromFile(graph, string) : bool
vertexset(graph) : vertexset|null
edgeset(graph) : edgeset|null
isDirected(graph) : bool|null
setDirected(graph, number) : bool|null
invertEdgesDirection(graph) : null
generateVertex(graph) : vertex|null
generateEdge(graph, vertex, vertex) : edge|null
deleteVertex(graph|vertexset, vertex) : null
deleteEdge(graph|edgeset, edge) : null
getNumVertices(graph|vertexset) : int|null
getNumEdges(graph|edgeset) : int|null
getVertices(graph) : vertexset|null
getEdges(graph) : edgeset|null
getDegree(vertex) : int|null
getNeighbors(vertex) : vertexset|null
getBeginVertex(edge) : vertex|null
getEndVertex(edge) : vertex|null
add(vertexset|edgeset, vertex|edge) : null
contains(graph|vertexset|edgeset, vertex|edge) : bool|null
union(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
intersection(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
difference(vertexset|edgeset, vertexset|edgeset) : vertexset|edgeset|null
getAdjacencyMatrix(graph) : array
setPropertyToAllVertices(graph|vertexset, string, object) : null
setPropertyToAllEdges(graph|edgeset, string, object) : null
visRegister(graph|vertexset|edgeset, string, number, number, number) : null
visSetPos(vertex, number, number, number) : null
visSetColor(vertex|edge, number, number, number) : null
visSetView(number, number, number, number, number) : null
visUseWeightWhenPaintingEdges(bool) : null
visScreenshot(string) : null
visGetGraph() : graph|null
[woq@evm bbd]$
</pre>




<?php
include 'p_end.php';
?>
