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


$g_title = 'TODO &amp; Plans';
include 'p_begin.php';
?>

<p>There is no active development on Graphal at the moment. If you like idea of this software and if you want something to be fixed or added, <?php Web('devel_contribute', 'please contact me'); ?>. Graphal has no active users at the moment and I don't simply want to spend my free time to fix the bugs for nobody ;-)</p>

<pre>
<?php
safeReadFile('../TODO');
?>
</pre>


<?php
include 'p_end.php';
?>
