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


$g_title = 'Built-in functions';
include 'p_begin.php';
?>


<p>The list of defined built-in functions, their parameters and return values can be displayed using <em>make listbuiltin</em> command.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>cd libgraphal/</strong>
[woq@evm libgraphal]$ <strong>make listbuiltin</strong>
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
isSet(object) : bool
isGraph(object) : bool
isVertex(object) : bool
isEdge(object) : bool
printStackTrace() : null
iterator(object) : object
hasNext(object) : bool
next(object) : object
resetIterator(object) : object
array(number) : array|null
set() : set
struct() : struct
size(array|struct|set|string) : int|null
pushFront(array, object) : null
pushBack(array, object) : null
popFront(array) : null
popBack(array) : null
back(array) : object|null
front(array) : object|null
graph() : graph
loadFromFile(graph, string) : bool
isDirected(graph) : bool|null
setDirected(graph, number) : bool|null
invertEdgesDirection(graph) : null
generateVertex(graph) : vertex|null
generateEdge(graph, vertex, vertex) : edge|null
deleteVertex(graph, vertex) : null
deleteEdge(graph, edge) : null
getNumVertices(graph) : int|null
getNumEdges(graph) : int|null
getVertices(graph) : set|null
getEdges(graph) : set|null
getDegree(vertex) : int|null
getNeighbors(vertex) : set|null
getBeginVertex(edge) : vertex|null
getEndVertex(edge) : vertex|null
insert(set, object) : null
remove(set, object) : null
contains(set, object) : bool|null
union(set, set) : set|null
intersection(set, set) : set|null
difference(set, set) : set|null
getAdjacencyMatrix(graph) : array
setPropertyToAllVertices(graph, string, object) : null
setPropertyToAllEdges(graph, string, object) : null
setPropertyToAllStructItems(array|struct|set, string, object) : null
visRegister(graph|set, string, number, number, number) : null
visSetPos(vertex, number, number, number) : null
visSetColor(vertex|edge, number, number, number) : null
visSetView(number, number, number, number, number) : null
visUseWeightWhenPaintingEdges(bool) : null
visScreenshot(string) : null
visGetGraph() : graph|null
[woq@evm libgraphal]$
</pre>


<?php
include 'p_end.php';
?>
