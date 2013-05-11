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


$g_title = 'Compilation';
include 'p_begin.php';
?>


<h2>Command Line Build</h2>

<p>To build and install Graphal just run <em>./configure</em>, <em>make</em> and <em>make install</em> commands in the top level package directory. They expect <?php Web('dependencies', 'all neccessary tools'); ?> are installed. The configure script processes only very basic checks, please see content of the top level <em>Makefile</em> for possible build options - e.g. prefix of installation directory or disabling of optional tools and similar.</p>



<h2>Qt Creator IDE</h2>

<p>Open the project and click on <em>Build</em> - <em>Build All</em> menu item, you can choose between debug and release versions. The project in IDE is configured to use the same Makefiles as the command line build.</p>


<?php
include 'p_end.php';
?>
