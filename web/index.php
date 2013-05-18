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

<p><em>Graphal</em> is an interpreter of a programming language that is mainly oriented to graph algorithms. There is a command line interpreter and a graphical integrated development environment. The IDE contains text editor for programmers, compilation and script output, advanced debugger and visualization window. The progress of the interpreted and debugged graph algorithm can be displayed in 3D scene.</p>


<h2>Main Features</h2>

<div id="screenshot"><?php Img('images/screenshots/graphal_gui_dfs_sm.png', 'Screenshot of Graphal GUI'); ?></div>

<ul>
<li>The script code looks very similar to C or Java language.</li>
<li>Shared library and CLI application is written in C++ with STL.</li>
<li>GUI application uses Qt library.</li>
<li>There is no other dependency to any external library.</li>
<li>Core library, CLI and GUI applications are separated.</li>
</ul>

<ul>
<li>Null, bool, int, float, string, array, struct, set, vertex, edge and graph data types.</li>
<li>Global and local variables.</li>
<li>C/C++ like evaluation of expressions.</li>
<li>If-else, for, while and foreach statements.</li>
<li>Return, break and continue structured jumps.</li>
<li>Built-in and user defined functions.</li>
<li>Preprocessor includes and defines.</li>
</ul>

<ul>
<li>Text editor for programmers with syntax highlighting.</li>
<li>Window with compilation and script output.</li>
<li>Interactive visualization Window with graph in 3D space.</li>
<li>Advanced debugging of the scripts.</li>
</ul>

<ul>
<li>Runnable on GNU/Linux and MS Windows, other operating systems are probably supported too.</li>
<li>Core library licensed under GNU LGPL, applications under GNU GPL.</li>
</ul>


<h2>News</h2>

<h3>2 April 2013</h3>
<ul>
<li>The project moved to <?php Blank('http://www.sourceforge.net/', 'SourceForge.net'); ?> site and renamed to <em>Graphal</em>.</li>
<li>Subversion repository replaced by GIT and cleaned.</li>
<li>The core of interpreter moved to a shared library and licensed under GNU LGPL.</li>
<li>Build scripts completely rewritten.</li>
<li>Various fixes and code updates.</li>
</ul>

<h3>12 December 2009</h3>
<ul>
<li>The first version released, final exam successfully passed.</li>
<li>No update for a long time.</li>
</ul>

<h3>27 October 2008</h3>
<ul>
<li>The project was founded as a diploma thesis at <?php Blank('http://www.fel.cvut.cz/', 'Faculty of Electrical Engineering'); ?> of <?php Blank('http://www.cvut.cz/', 'Czech Technical University in Prague'); ?>.</li>
<li>Most parts of Graphal was written during cold winter and student exchange stay at <?php Blank('http://www.sibsau.ru/', 'Siberian State Aerospace University'); ?>.</li>
<li><em>Graphal</em> was originally named <em>bbd</em> or <em>bbdgui</em> respectively. bbd was acronym for russian word бутерброд/buterbrod that can be translated as <em>bread and butter</em> or <em>sandwich</em>. I used three-letter names for my software at that time.</li>
</ul>


<?php
include 'p_end.php';
?>
