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


$g_title = 'Functions';
include 'p_begin.php';
?>

<h2>Function Calls</h2>

<p>Functions can be called using two possible and equivalent approaches. If a dot notation is used, the object will be passed as the first parameter to the function. This approach is very similar to self parameter in Python.</p>

<pre class="code">
function func(<strong>par1</strong>, par2, par3)
{
	// Code
}

func(<strong>par1</strong>, par2, par3);
<strong>par1</strong>.func(par2, par3);
</pre>

<pre class="code">
<strong>g</strong> = graph();
v1 = generateVertex(<strong>g</strong>);
v2 = <strong>g</strong>.generateVertex();
</pre>


<h2>Built-in Functions</h2>

<p>Built-in functions behave the same as the functions defined in the script code.</p>


<?php
include 'p_end.php';
?>
