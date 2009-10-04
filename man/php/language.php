<?php
$g_title = 'Language';
include 'p_begin.php';
?>

<p>The syntax of the language looks like simplified C programming language, it is case-insensitive. The script enters <em>main(argv)</em> function at start.</p>


<h3>Examples</h3>

<p>List the script parameters.</p>

<pre class="code">
function main(argv)
{
	num = argv.size();
	for(i = 0; i &lt; num; i++)
		echo("argv[" + i + "]: " + argv[i] + "\n");
}
</pre>

<pre class="screen">
[woq@woq bbd]$ <strong>./bbd ../samples/12_script_parameters.txt test parameters</strong>
argv[0]: ../samples/12_script_parameters.txt
argv[1]: test
argv[2]: parameters
</pre>

<?php
include 'p_end.php';
?>
