<?php
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
