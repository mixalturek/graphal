<?php
$g_title = 'Preprocessor';
include 'p_begin.php';
?>

<p>Preprocesor can include files and define simple macros. All these constructs are processed at the scanner layer, the parser receives generated tokens instead of <em>include</em> or <em>define</em> command.</p>

<pre class="spec">
include("filename");
define("name", "value");
</pre>


<p>Position in the source files can be passed to the script using predefined constants.</p>

<pre class="spec">
__FILE__
__LINE__
__FUNCTION__
</pre>

<p>There are two possible versions of comments. Multiline comment couldn't contain another multiline comment.</p>

<pre class="spec">
// This is a single line comment

/*
This is a multiline comment
*/
</pre>


<h3>Examples</h3>

<p>Original source file contains a comment, defines new <em>tverify</em> macro and uses symbolic constant <em>__FUNCTION__</em>.</p>

<pre class="code">
<strong>// From samples/tests.txt</strong>
<strong>define("tverify", "result = result &amp;&amp; verify");</strong>

function testFactorial()
{
	result = true;

	<strong>tverify</strong>(factorial(1) == 1);
	<strong>tverify</strong>(factorial(2) == 2);
	<strong>tverify</strong>(factorial(3) == 6);

	return testResult(<strong>__FUNCTION__</strong>, result);
}
</pre>

<p>The constructs are processed inside of the scanner, parser receives tokens that are representing the following code.</p>

<pre class="code">
function testFactorial()
{
	result = true;

	<strong>result = result &amp;&amp; verify</strong>(factorial(1) == 1);
	<strong>result = result &amp;&amp; verify</strong>(factorial(2) == 2);
	<strong>result = result &amp;&amp; verify</strong>(factorial(3) == 6);

	return testResult(<strong>"testFactorial"</strong>, result);
}
</pre>


<?php
include 'p_end.php';
?>
