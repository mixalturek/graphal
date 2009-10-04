<?php
$g_title = 'Graph algorithms interpreter';
include 'p_begin.php';
?>

<p>The core of this diploma thesis is design and implementation of a special language based on C, which will be used for the graph manipulations. Integrated development environment was developed, it consists of the text editor for programmers, debugger and visualization window, in which the progress of the interpreted algorithm and graph can be displayed using 3D graphics.</p>


<h3>Features</h3>

<div id="screenshot"><?php Img('images/screenshot/2009-09-09_23-35-04_sm.png', 'Screenshot'); ?></div>

<ul>
<li>The code is very similar to C language</li>
<li>CLI application was written in C++ with STL, clear OOP</li>
<li>GUI application uses <?php Blank('http://qt.nokia.com/', 'Qt library'); ?></li>
<li>No other external library dependencies, CLI and GUI code is separated</li>
<li>Null, bool, int, float, string, array, struct, graph and other data types</li>
<li>Global and local variables</li>
<li>C/C++ like evaluation of expressions</li>
<li>If-else, for, while, foreach statements</li>
<li>Built-in and user defined functions</li>
<li>Return, break and continue structured jumps</li>
<li>Preprocessor includes and defines</li>
</ul>

<?php
include 'p_end.php';
?>
