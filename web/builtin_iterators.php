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


$g_title = 'Iterator functions';
include 'p_begin.php';
?>

<p>Arrays, structs, vertices, edges, vertex sets and edge sets data types are iterable. The <em>foreach</em> loop internally uses iterators.</p>

<p>Return the copy of the container and set its inner iterator to the begining.</p>

<pre class="spec">
iterator(object) : object
</pre>


<p>Check if the contatiner has the next object.</p>

<pre class="spec">
hasNext(object) : bool
</pre>


<p>Get the next object</p>

<pre class="spec">
next(object) : object
</pre>


<p>Reset the inner iterator to the begining.</p>

<pre class="spec">
resetIterator(object) : object
</pre>


<h3>Examples</h3>

<pre class="code">
st = struct();
st.number = 42;
st.pi = 3.14;
st.str = "bagr";

// Iterate using foreach loop
foreach(var; st)
	println(var);

// Iterate using iterators
it = st.iterator();
while(it.hasNext())
	println(it.next());
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
