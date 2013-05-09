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
