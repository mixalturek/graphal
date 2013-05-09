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


$g_title = 'Variables';
include 'p_begin.php';
?>

<h3>Data types</h3>

<p>The language specify no constructs for variable declaration and type specification. The interpreter uses following inner data types which can be dynamically changed during assigning.</p>

<ul>
<li>null</li>
<li>bool, int, float</li>
<li>string, array, struct</li>
<li>graph, vertex, edge, vertex set, edge set</li>
</ul>


<h3>Global variables</h3>

<p>All variables are defined as local in the function scope. To define/use a global variable, use keyword <em>global</em> with the variable name.</p>

<pre class="code">
function setGlobal(val)
{
	global g_var;
	g_var = val;
}

function main(argv)
{
	setGlobal("test");
	println(g_var);
	global g_var;
	println(g_var);
}
</pre>

<pre class="screen">
NULL
test
</pre>


<h3>References</h3>

<p>Use special <em>&amp;=</em> operator to assign the reference to the variable.</p>

<pre class="code">
var = 1;
ref &amp;= var;
println("var = " + var);
println("ref = " + ref);
var = 2;
println("var = " + var);
println("ref = " + ref);
ref = 3;
println("var = " + var);
println("ref = " + ref);
</pre>

<pre class="screen">
var = 1
ref = 1
var = 2
ref = 2
var = 3
ref = 3
</pre>


<?php
include 'p_end.php';
?>
