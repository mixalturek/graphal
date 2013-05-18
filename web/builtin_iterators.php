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


$g_title = 'Iterator Functions';
include 'p_begin.php';
?>

<p>Array, struct, set, vertex and edge data types are iterable. The <em>foreach</em> loop uses iterators internally.</p>

<p>Return a copy of a container and set its inner iterator to the beginning.</p>

<pre class="spec">
iterator(object) : object
</pre>


<p>Check if a container has a next item.</p>

<pre class="spec">
hasNext(object) : bool
</pre>


<p>Get the next item.</p>

<pre class="spec">
next(object) : object
</pre>


<p>Reset the inner iterator to the beginning.</p>

<pre class="spec">
resetIterator(object) : object
</pre>


<h2>Examples</h2>

<pre class="code">
function main(argv)
{
	// Define and fill an iterable object
	iterable = struct();
	iterable.number = 42;
	iterable.pi = 3.14;
	iterable.iterabler = "bagr";

	// Iterate using iterators
	it = iterable.iterator();
	while(it.hasNext())
		println(it.next());

	println("");

	// Iterate using foreach loop
	foreach(var; iterable)
		println(var);
}
</pre>

<pre class="screen">
42
3.14
bagr

42
3.14
bagr
</pre>


<?php
include 'p_end.php';
?>
