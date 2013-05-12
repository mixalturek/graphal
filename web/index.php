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


$g_title = 'Graph Algorithms Interpreter';
include 'p_begin.php';
?>

<p><em>Graphal project</em> is an interpreter of a programming language mainly oriented to graph algorithms. There is a command line interpreter and a graphical integrated development environtment. The IDE contains a text editor for programmers, compilation and script output, advanced debugger and vizualization window. The progress of the interpreted and debugged graph algorithm can be displayed in 3D scene.</p>


<h3>Main Features</h3>

<div id="screenshot"><?php Img('images/screenshots/graphal_gui_dfs_sm.png', 'Screenshot of Graphal GUI'); ?></div>

<ul>
<li>The script code looks very similar to C or Java language.</li>
<li>Shared library and CLI application is written in C++ with STL.</li>
<li>GUI application uses Qt library.</li>
<li>There is no other dependency to any external library.</li>
<li>CLI and GUI applications are separated.</li>
</ul>

<ul>
<li>Null, bool, int, float, string, array, struct, set, vertex, edge, graph and other data types.</li>
<li>Global and local variables.</li>
<li>C/C++ like evaluation of expressions.</li>
<li>If-else, for, while and foreach statements.</li>
<li>Built-in and user defined functions.</li>
<li>Return, break and continue structured jumps.</li>
<li>Preprocessor includes and defines.</li>
</ul>

<ul>
<li>File system view.</li>
<li>Text editor for programmers with syntax highlighting.</li>
<li>View with compilation and script output.</li>
<li>Vizualization view with graph in 3D space.</li>
<li>Advanced debugging of the scripts.</li>
</ul>

<?php
include 'p_end.php';
?>
