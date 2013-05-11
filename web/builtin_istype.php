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


$g_title = 'isType functions';
include 'p_begin.php';
?>

<p>Check the type of the passed parameter.</p>

<pre class="spec">isNull(object) : bool</pre>
<pre class="spec">isBool(object) : bool</pre>
<pre class="spec">isInt(object) : bool</pre>
<pre class="spec">isFloat(object) : bool</pre>
<pre class="spec">isString(object) : bool</pre>
<pre class="spec">isStruct(object) : bool</pre>
<pre class="spec">isArray(object) : bool</pre>
<pre class="spec">isSet(object) : bool</pre>
<pre class="spec">isGraph(object) : bool</pre>
<pre class="spec">isVertex(object) : bool</pre>
<pre class="spec">isEdge(object) : bool</pre>

<?php
include 'p_end.php';
?>
