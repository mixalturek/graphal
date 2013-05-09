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


$g_title = 'Execution';
include 'p_begin.php';
?>

<h3>IDE, graphic user interface</h3>

<pre class="screen">
[woq@evm diplomka]$ <strong>cd bbdgui/</strong>
[woq@evm bbdgui]$ <strong>./bbdgui</strong>
</pre>


<h3>Command line interpreter parameters</h3>

<pre class="screen">
[woq@evm diplomka]$ <strong>cd bbd/</strong>
[woq@evm bbd]$ <strong>./bbd</strong>
bbd [svn version 218]
Usage: ./bbd [-I&lt;directory&gt;] [-u | --unit-tests] [-a | --ast-dump] [-b | --enable-breakpoints] &lt;filename&gt; [parameters]

        -I&lt;directory&gt;
                Specify include directories (relative to the current working directory)
                -I&lt;directory_1&gt; -I&lt;directory_2&gt; ... -I&lt;directory_N&gt;

        -u | --unit-tests
                Run unit tests

        -a | --ast-dump
                Dump abstract syntax tree of the script

        -b | --breakpoints
                Enable breakpoints

        filename
                File to be executed

        parameters
                Script parameters

[woq@evm bbd]$
</pre>


<h3>Script execution</h3>

<pre class="screen">
[woq@woq bbd]$ <strong>./bbd ../samples/01_factorial.txtt</strong>
bbd [svn version 218]
[i] *** ENTERING SCRIPT MAIN ***
Factorial of 0 is 1
Factorial of 1 is 1
Factorial of 2 is 2
Factorial of 3 is 6
Factorial of 4 is 24
Factorial of 5 is 120
Factorial of 6 is 720
Factorial of 7 is 5040
Factorial of 8 is 40320
Factorial of 9 is 362880
[i] *** EXITING SCRIPT MAIN, OK ***
[i] Return value: 0
[i] Number of memory leaks: 0
[i] *** EXITING MAIN, OK ***
[woq@woq bbd]$
</pre>


<h3>Unit tests</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>valgrind ./bbd --unit-tests ../samples/tests.txt</strong>
==8029== Memcheck, a memory error detector.
==8029== Copyright (C) 2002-2007, and GNU GPL'd, by Julian Seward et al.
==8029== Using LibVEX rev 1854, a library for dynamic binary translation.
==8029== Copyright (C) 2004-2007, and GNU GPL'd, by OpenWorks LLP.
==8029== Using valgrind-3.3.1-Debian, a dynamic binary instrumentation framework.
==8029== Copyright (C) 2000-2007, and GNU GPL'd, by Julian Seward et al.
==8029== For more details, rerun with: -v
==8029==
bbd [svn version 218]
[i] [ OK ]     testMemoryLeaks
[i] [ OK ]     testDoubleDispatching
...
[i] [ OK ]     testValueArrayIterator
[i] Number of failed tests: 0
[i] *** ENTERING SCRIPT MAIN ***
Executing unit tests...
[ OK ]     testFactorial
[ OK ]     testArray
...
[ OK ]     testSetPropertyToAll
Number of failed tests: 0
[i] *** EXITING SCRIPT MAIN, OK ***
[i] Return value: NULL
[i] Number of memory leaks: 0
[i] *** EXITING MAIN, OK ***
==8029==
==8029== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 19 from 1)
==8029== malloc/free: in use at exit: 0 bytes in 0 blocks.
==8029== malloc/free: 31,054 allocs, 31,054 frees, 557,871 bytes allocated.
==8029== For counts of detected errors, rerun with: -v
==8029== All heap blocks were freed -- no leaks are possible.
[woq@woq bbd]$
</pre>


<h3>Dump of script abstract syntax tree</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>./bbd --ast-dump ../samples/01_factorial.txt</strong>
bbd [svn version 218]
bbd [svn version 218]
&lt;Context&gt;
    &lt;BuiltinFunction name="echo" id="7" /&gt;
    &lt;BuiltinFunction name="print" id="8" /&gt;
...
    &lt;BuiltinFunction name="visGetGraph" id="74" /&gt;
    &lt;Function name="factorial" id="77"&gt;
        &lt;Parameter name="number" id="78" /&gt;
        &lt;If&gt;
            &lt;Condition&gt;
                &lt;NodeBinaryLt&gt;
                    &lt;ValueIdentifier name="number" id="78"&gt;
                        &lt;NoValue /&gt;
                    &lt;/ValueIdentifier&gt;
                    &lt;ValueInt value="2" /&gt;
                &lt;/NodeBinaryLt&gt;
            &lt;/Condition&gt;
            &lt;IfSection&gt;
                &lt;NodeUnaryReturn&gt;
                    &lt;ValueInt value="1" /&gt;
                &lt;/NodeUnaryReturn&gt;
            &lt;/IfSection&gt;
            &lt;ElseSection&gt;
                &lt;NodeUnaryReturn&gt;
                    &lt;NodeBinaryMult&gt;
                        &lt;ValueIdentifier name="number" id="78"&gt;
                            &lt;NoValue /&gt;
                        &lt;/ValueIdentifier&gt;
                        &lt;FunctionCall name="factorial" id="77"&gt;
                            &lt;NodeBinarySub&gt;
                                &lt;ValueIdentifier name="number" id="78"&gt;
                                    &lt;NoValue /&gt;
                                &lt;/ValueIdentifier&gt;
                                &lt;ValueInt value="1" /&gt;
                            &lt;/NodeBinarySub&gt;
                        &lt;/FunctionCall&gt;
                    &lt;/NodeBinaryMult&gt;
                &lt;/NodeUnaryReturn&gt;
            &lt;/ElseSection&gt;
        &lt;/If&gt;
    &lt;/Function&gt;
    &lt;Function name="main" id="79"&gt;
...
    &lt;/Function&gt;
    &lt;StringTable&gt;
        &lt;string id="0"&gt;built-in function&lt;/string&gt;
        &lt;string id="1"&gt;a&lt;/string&gt;
...
        &lt;string id="81"&gt;i&lt;/string&gt;
    &lt;/StringTable&gt;
&lt;/Context&gt;
[i] *** ENTERING SCRIPT MAIN ***
Factorial of 0 is 1
Factorial of 1 is 1
Factorial of 2 is 2
Factorial of 3 is 6
Factorial of 4 is 24
Factorial of 5 is 120
Factorial of 6 is 720
Factorial of 7 is 5040
Factorial of 8 is 40320
Factorial of 9 is 362880
[i] *** EXITING SCRIPT MAIN, OK ***
[i] Return value: 0
[i] Number of memory leaks: 0
[i] *** EXITING MAIN, OK ***
</pre>

<?php
include 'p_end.php';
?>
