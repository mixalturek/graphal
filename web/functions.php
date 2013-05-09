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
