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

<h2>Data Types</h2>

<p>The language specify no constructs for variable declaration and type specification. The interpreter uses following inner data types which can be dynamically changed with assign command.</p>

<ul>
<li>Null.</li>
<li>Bool, int, float.</li>
<li>String, array, struct, set.</li>
<li>Graph, vertex, edge.</li>
</ul>


<h2>Global Variables</h2>

<p>All variables are defined as local and are valid only it the scope of the current function (function not block). To define/use a global variable, use <em>global</em> keyword with the variable name.</p>

<pre class="code">
function setGlobal(val)
{
	<strong>global g_var;</strong>
	g_var = val;         // g_var is global
}

function main(argv)
{
	println(g_var);      // g_var is local
	setGlobal("test");
	println(g_var);      // g_var is local
	<strong>global g_var;</strong>
	println(g_var);      // g_var is global
}
</pre>

<pre class="screen">
NULL
NULL
test
</pre>


<h2>References</h2>

<p>Use special <em>&amp;=</em> operator to assign a reference to the variable and to create an alias.</p>

<pre class="code">
var = 1;
<strong>ref &amp;= var;</strong>               // ref is now alias of var
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
