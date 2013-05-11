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

<h2>Graphal GUI</h2>

<p>GUI application doesn't parse any parameters, it shows the main application window with integrated development environment for graph algorithms.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>make RPATH_ORIGIN=yes dist</strong>
...
[woq@evm graphal]$ <strong>cd build/dist/</strong>
[woq@evm dist]$ <strong>./graphal_gui</strong>
</pre>


<?php Img('images/screenshots/graphal_gui_dfs_sm.png', 'Graphal GUI'); ?>

<h2>Graphal CLI</h2>

<h3>Usage</h3>

<p>Application executed without parameters shows usage and exits.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>make RPATH_ORIGIN=yes dist</strong>
...
[woq@evm graphal]$ <strong>cd build/dist/</strong>
[woq@evm dist]$ <strong>./graphal_cli</strong>
Graph Algorithms Interpreter - Graphal

About:
	Version:     1.0.0
	Author:      Michal Turek
	Website:     http://graphal.sourceforge.net/

License:
	libGraphal:  GNU LGPL v3
	Graphal CLI: GNU  GPL v3
	Graphal GUI: GNU  GPL v3

Usage:
	./graphal_cli [-h | --help] [-I&lt;directory&gt;] [-u | --unit-tests] [-a | --ast-dump] [-b | --enable-breakpoints] &lt;filename&gt; [parameters]

	-h | --help
		Show this help and exit.

	-v | --version
		Show version and exit.

	-I&lt;directory&gt;
		Specify include directories (relative to the current working directory).
		-I&lt;directory_1&gt; -I&lt;directory_2&gt; ... -I&lt;directory_N&gt;

	-u | --unit-tests
		Run unit tests.

	-a | --ast-dump
		Dump abstract syntax tree of the script.

	-b | --breakpoints
		Enable breakpoints.

	filename
		File to be executed.

	parameters
		Script parameters.

[woq@evm dist]$
</pre>


<h3>Script execution</h3>

<p>Pass a path as the last parameter to execute the script.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>make RPATH_ORIGIN=yes dist</strong>
...
[woq@evm graphal]$ <strong>cd build/dist/</strong>
[woq@evm dist]$ <strong>./graphal_cli ../samples/01_factorial.txt</strong>
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
[i] *** EXITING MAIN, OK ***
[woq@evm dist]$
</pre>


<h3>Unit tests</h3>

<p>Unit tests mode is suitable to check that the application was compiled and works correctly.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>make RPATH_ORIGIN=yes dist</strong>
...
[woq@evm graphal]$ <strong>cd build/dist/</strong>
[woq@evm dist]$ <strong>valgrind ./graphal_cli --unit-tests ../samples/tests.txt</strong>
==13023== Memcheck, a memory error detector
==13023== Copyright (C) 2002-2010, and GNU GPL'd, by Julian Seward et al.
==13023== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==13023== Command: ./graphal_cli --unit-tests ../samples/tests.txt
==13023==
[i] [ OK ]     testDoubleDispatching
[i] [ OK ]     testValueStruct
[i] [ OK ]     testValueString
[i] [ OK ]     testValueReference
[i] [ OK ]     testValueIdentifier
[i] [ OK ]     testValueArray
[i] [ OK ]     testGraph
[i] [ OK ]     testGraphSet
[i] [ OK ]     testGraphInvertEdgesOrientation
[i] [ OK ]     testLexanTerminalSymbols
[i] [ OK ]     testLexanInt
[i] [ OK ]     testLexanFloat
[i] [ OK ]     testLexanString
[i] [ OK ]     testLexanComments
[i] [ OK ]     testLexanSourceCode
[i] [ OK ]     testNodeUnary
[i] [ OK ]     testNodeBinary
[i] [ OK ]     testNodeBlock
[i] [ OK ]     testNodeVariable
[i] [ OK ]     testStringTable
[i] [ OK ]     testCountPtr
[i] [ OK ]     testNodeFunction
[i] [ OK ]     testValueArrayIterator
[i] [ OK ]     testValueSet
[i] [ OK ]     testValueSetOperations
[i] [ OK ]     testValueSetRemove
[i] Number of failed tests: 0
[i] *** ENTERING SCRIPT MAIN ***
Executing unit tests...
[ OK ]     testFactorial
[ OK ]     testArray
[ OK ]     testStruct
[ OK ]     testGraph
[ OK ]     testMemberAccess
[ OK ]     testForeach
[ OK ]     testGlobal
[ OK ]     testUnionIntersectionDifference
[ OK ]     testTypeChecks
[ OK ]     testStackQueue
[ OK ]     testNotReferences
[ OK ]     testReferences
[ OK ]     testAdjacencyMatrix
[ OK ]     testSetPropertyToAll
Number of failed tests: 0
[i] *** EXITING SCRIPT MAIN, OK ***
[i] Return value: NULL
[i] *** EXITING MAIN, OK ***
==13023==
==13023== HEAP SUMMARY:
==13023==     in use at exit: 0 bytes in 0 blocks
==13023==   total heap usage: 20,768 allocs, 20,768 frees, 393,222 bytes allocated
==13023==
==13023== All heap blocks were freed -- no leaks are possible
==13023==
==13023== For counts of detected and suppressed errors, rerun with: -v
==13023== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 20 from 7)
[woq@evm dist]$
</pre>


<h3>Dump of AST</h3>

<p>Dump of AST (Abstract Syntax Tree) is mainly for debugging purposes to check that the script's source code was parsed and stored to the internal form correctly.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>make RPATH_ORIGIN=yes dist</strong>
...
[woq@evm graphal]$ <strong>cd build/dist/</strong>
[woq@evm dist]$ <strong>cat ../samples/01_factorial.txt</strong>
/*
 * Copyright 2008 Michal Turek
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
 * along with Graphal.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
 */


function factorial(number)
{
	if(number &lt; 2)
		return 1;
	else
		return number * factorial(number - 1);
}

// Enter to program
function main(argv)
{
	for(i = 0; i &lt; 10; i++)
		println("Factorial of " + i + " is " + factorial(i));

	return 0;
}

[woq@evm dist]$ <strong>./graphal_cli --ast-dump ../samples/01_factorial.txt</strong>
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
	&lt;Parameter name="argv" id="80" /&gt;
	&lt;Loop&gt;
	    &lt;Init&gt;
		&lt;NodeBinaryAss&gt;
		    &lt;ValueIdentifier name="i" id="81"&gt;
			&lt;NoValue /&gt;
		    &lt;/ValueIdentifier&gt;
		    &lt;ValueInt value="0" /&gt;
		&lt;/NodeBinaryAss&gt;
	    &lt;/Init&gt;
	    &lt;Condition&gt;
		&lt;NodeBinaryLt&gt;
		    &lt;ValueIdentifier name="i" id="81"&gt;
			&lt;NoValue /&gt;
		    &lt;/ValueIdentifier&gt;
		    &lt;ValueInt value="10" /&gt;
		&lt;/NodeBinaryLt&gt;
	    &lt;/Condition&gt;
	    &lt;Inc&gt;
		&lt;NodeUnaryIncPost&gt;
		    &lt;ValueIdentifier name="i" id="81"&gt;
			&lt;NoValue /&gt;
		    &lt;/ValueIdentifier&gt;
		&lt;/NodeUnaryIncPost&gt;
	    &lt;/Inc&gt;
	    &lt;Body&gt;
		&lt;FunctionCall name="println" id="9"&gt;
		    &lt;NodeBinaryAdd&gt;
			&lt;NodeBinaryAdd&gt;
			    &lt;NodeBinaryAdd&gt;
				&lt;ValueString value="Factorial of " /&gt;
				&lt;ValueIdentifier name="i" id="81"&gt;
				    &lt;NoValue /&gt;
				&lt;/ValueIdentifier&gt;
			    &lt;/NodeBinaryAdd&gt;
			    &lt;ValueString value=" is " /&gt;
			&lt;/NodeBinaryAdd&gt;
			&lt;FunctionCall name="factorial" id="77"&gt;
			    &lt;ValueIdentifier name="i" id="81"&gt;
				&lt;NoValue /&gt;
			    &lt;/ValueIdentifier&gt;
			&lt;/FunctionCall&gt;
		    &lt;/NodeBinaryAdd&gt;
		&lt;/FunctionCall&gt;
	    &lt;/Body&gt;
	&lt;/Loop&gt;
	&lt;NodeUnaryReturn&gt;
	    &lt;ValueInt value="0" /&gt;
	&lt;/NodeUnaryReturn&gt;
    &lt;/Function&gt;
    &lt;StringTable&gt;
	&lt;string id="0"&gt;built-in function&lt;/string&gt;
	&lt;string id="1"&gt;a&lt;/string&gt;
	&lt;string id="2"&gt;b&lt;/string&gt;
	&lt;string id="3"&gt;c&lt;/string&gt;
	&lt;string id="4"&gt;d&lt;/string&gt;
	&lt;string id="5"&gt;e&lt;/string&gt;
	&lt;string id="6"&gt;f&lt;/string&gt;
	&lt;string id="7"&gt;echo&lt;/string&gt;
	&lt;string id="8"&gt;print&lt;/string&gt;
	...
	&lt;string id="79"&gt;main&lt;/string&gt;
	&lt;string id="80"&gt;argv&lt;/string&gt;
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
[i] *** EXITING MAIN, OK ***
[woq@evm dist]$
</pre>

<?php
include 'p_end.php';
?>
