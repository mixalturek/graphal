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


$g_title = 'Output Functions';
include 'p_begin.php';
?>

<p>Format the object to a string representation and send the result to the standard output.</p>

<pre class="spec">
echo(object) : object
</pre>

<pre class="spec">
print(object) : object
</pre>


<p>Format the object to a string representation and send the result to the standard output and append "\n" character.</p>

<pre class="spec">
println(object) : object
</pre>


<h2>Examples</h2>

<p>Print a value of a variable.</p>

<pre class="code">
a = 5;
println(a);
echo(a);
print(a);
</pre>

<pre class="screen">
5
55
</pre>


<?php
include 'p_end.php';
?>
