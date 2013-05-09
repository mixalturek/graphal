<?php
$g_title = 'Output functions';
include 'p_begin.php';
?>

<p>Send the string representation of the object to the standard output.</p>

<pre class="spec">
echo(object) : object
</pre>

<pre class="spec">
print(object) : object
</pre>


<p>Send the string representation of the object to the standard output and append "\n" character.</p>

<pre class="spec">
println(object) : object
</pre>


<h3>Examples</h3>

<p>Print the value of a variable.</p>

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
