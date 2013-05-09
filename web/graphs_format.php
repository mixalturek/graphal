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


$g_title = 'Graphs file format';
include 'p_begin.php';
?>

<p>The graphs can be loaded from the text files with the following format. You can use whatever white character (space, tabulator, new line) for the delimiters.</p>

<pre class="spec">
is_directed

number_of_vertices   number_of_edges

number_of_properties_for_vertices   names_of_properties_for_vertices
number_of_properties_for_edges      names_of_properties_for_edges

vertex_id   values_of_properties
vertex_id   values_of_properties
vertex_id   values_of_properties
...

vertex_id   vertex_id   values_of_properties
vertex_id   vertex_id   values_of_properties
vertex_id   vertex_id   values_of_properties
...
</pre>


<h3>Examples</h3>

<p>An <em>one line house</em> graph.</p>

<pre class="code">
1

5 8

3	__x __y __z
1	__w

0	-1  1 0
1	 1  1 0
2	 1 -1 0
3	-1 -1 0
4	 0  2 0

3 0	1.0
0 1	1.3
1 3	1.6
3 2	1.9
2 0	2.2
0 4	2.5
4 1	2.8
1 2	3.1
</pre>

<pre class="screen">
  4
 /\
0--1
|\/|
|/\|
3--2
</pre>

<?php
include 'p_end.php';
?>
