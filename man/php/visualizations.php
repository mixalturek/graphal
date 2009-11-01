<?php
$g_title = 'Visualizations tips and tricks';
include 'p_begin.php';
?>

<h3>Visualizations mouse control</h3>

<ul>
<li>Left button - X and Y position of the object</li>
<li>Mouse wheel - Z position of the object, zoom</li>
<li>Right button - rotations
	<ul>
	<li>Ctrl modifier - rotations only on the X axis</li>
	<li>Shift modifier - rotations only on the Y axis</li>
	</ul>
</li>
</ul>


<h3>How to display content of the item in a structured variable?</h3>

<p>The <em>variables dock</em> does not display values of the items saved in the structured data types. You can use <em>assign-reference</em> operator together with another variable.</p>

<pre class="code">
alias &amp;= structure.some_array[57];
structure.some_array[57] = "some new value";
// alias variable contaions the new value too
</pre>


<h3>Call stack dock</h3>

<p>The file name provides tool tip to display full path to the file. Use double click to open the file and roll to the specified line.</p>


<?php
include 'p_end.php';
?>
