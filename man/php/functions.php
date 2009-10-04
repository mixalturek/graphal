<?php
$g_title = 'Function calling';
include 'p_begin.php';
?>

<p>The functions can be called using two possible, equivalent, methods. If the dot notation is used, the object is passed to the first parameter of the function.</p>

<pre class="code">
function func(par1, par2, par3)
{
	// Code
}

func(par1, par2, par3);
par1.func(par2, par3);
</pre>

<pre class="code">
g = graph();
v1 = generateVertex(g);
v2 = g.generateVertex();
</pre>

<?php
include 'p_end.php';
?>
