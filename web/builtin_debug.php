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


$g_title = 'Debug Functions';
include 'p_begin.php';
?>

<p>Test the object's value. If it is <em>false</em>, the script execution will be stopped with an error message.</p>

<pre class="spec">
assert(object) : null
</pre>


<p>Test the object's value. If it is <em>false</em>, the script will display an error message but it will continue.</p>

<pre class="spec">
verify(object) : bool
</pre>


<p>Test the object's value. If it is <em>true</em>, the script will wait user interaction.</p>

<pre class="spec">
breakpoint(object) : null
</pre>


<p>Print the current stack trace.</p>

<pre class="spec">
printStackTrace() : null
</pre>


<p>Immediately end the script execution. The call is equivalent to return from <em>main()</em> function.</p>

<pre class="spec">
exit(object) : null
</pre>


<p>Dump a content of a passed object and its subobjects in pseudo XML format.</p>

<pre class="spec">
dump(object) : object
</pre>


<h2>Examples</h2>

<p>Check if the operation was successful or not. <em>Verify()</em> only displays an error message, <em>assert()</em> ends the script.</p>

<pre class="code">
test = false;
verify(test);
assert(test);
println("This will be never executed.");
</pre>

<pre class="screen">
script.txt:4: Verify: Operation was not successful
script.txt:5: Assert: Operation was not successful
*** EXITING SCRIPT MAIN, OK ***
Exit value: false
</pre>


<p>Dump content of a variable.</p>

<pre class="code">
a = array(3);
a[0] = "some string";
a[1] = 5;
dump(a);
</pre>

<pre class="screen">
&lt;ValueReference&gt;
    &lt;ValueArray&gt;
        &lt;ValueReference&gt;
            &lt;ValueString value="some string" /&gt;
        &lt;/ValueReference&gt;
        &lt;ValueReference&gt;
            &lt;ValueInt value="5" /&gt;
        &lt;/ValueReference&gt;
        &lt;ValueReference&gt;
            &lt;ValueNull /&gt;
        &lt;/ValueReference&gt;
    &lt;/ValueArray&gt;
&lt;/ValueReference&gt;
</pre>

<?php
include 'p_end.php';
?>
