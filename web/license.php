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


$g_title = 'License';
include 'p_begin.php';
?>


<h2>Graphal Parts</h2>


<h3>Graphal Library</h3>

<p>Graphal library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, version 3 of the License.</p>

<p>Graphal library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.</p>


<h3>Graphal CLI</h3>

<p>Graphal CLI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.</p>

<p>Graphal CLI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.</p>


<h3>Graphal GUI</h3>


<p>Graphal GUI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.</p>

<p>Graphal GUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.</p>


<h2>Text of Licenses</h2>

<h3>GNU General Public License</h3>

<pre>
<?php
safeReadFile('../COPYING');
?>
</pre>


<h3>GNU Lesser General Public License</h3>

<pre>
<?php
safeReadFile('../COPYING.LESSER');
?>
</pre>

<?php
include 'p_end.php';
?>
