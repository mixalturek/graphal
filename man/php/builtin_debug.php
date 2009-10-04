<?php
$g_title = 'Debug functions';
include 'p_begin.php';
?>

<p>Test the object's value. If it is <em>false</em>, the script execution will be stopped with and error message.</p>

<pre class="spec">
assert(object) : null
</pre>


<p>Test the object's value. If it is <em>false</em>, the script will display an error message.</p>

<pre class="spec">
verify(object) : bool
</pre>


<p>Test the object's value. If it is <em>true</em>, the script will wait the user interaction.</p>

<pre class="spec">
breakpoint(object) : null
</pre>


<p>Print the current stack trace to the standard output.</p>

<pre class="spec">
printStackTrace() : null
</pre>


<p>Immediately end the script execution. The call is equivalent to the return from the <em>main()</em> function.</p>

<pre class="spec">
exit(object) : null
</pre>


<p>Dump the content of the passed object and its subobjects in the XML format.</p>

<pre class="spec">
dump(object) : object
</pre>


<h3>Examples</h3>

<p>Check if the operation was successful or not. <em>Verify()</em> only displays an error message, <em>assert()</em> ends the script.</p>

<pre class="code">
test = false;
verify(test);
assert(test);
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
