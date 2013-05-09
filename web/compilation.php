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


<h3>Global makefile</h3>

<p>Just run <em>make</em>, <em>make install</em> or <em>make clean</em> in the top level package directory. These operations expect all tools (including <?php Web('dependencies', 'compiler tools'); ?>, latex etc.) are installed. See the content of <em>Makefile</em> for details.</p>


<h3>Makefile (CLI version, bbd)</h3>

<p>Run <em>make</em> with no parameters to compile the command line application.</p>

<p>Complete rebuild, including the sources code regeneration (<em>bison</em>, <em>gen_operators.pl</em>, <em>gen_builtin.pl</em>) and the settings of header files dependencies (<em>makedepend</em>), can be done using <em>make rebuild</em> command. Make sure that <?php Web('dependencies', 'all necessary tools'); ?> are installed.</p>

<p>You may execute particular parts of the compilation separately (<em>make bison</em>, <em>make operators</em>, <em>make builtin</em>, <em>make build</em> etc.). See the content of <em>Makefile</em> for details.</p>

<pre class="screen">
[woq@evm diplomka]$ <strong>cd bbd/</strong>
[woq@evm bbd]$ <strong>make rebuild</strong>
rm -f bbd *.o core
bison -d -o parser.cpp parser.y
perl gen_operators.pl
Generating NodeUnarySub
Generating NodeUnaryNot
...
perl gen_builtin.pl
Generating NodeBuiltinEcho
Generating NodeBuiltinDump
...
makedepend -Y -m baseobject.cpp context.cpp ...
g++ -c baseobject.cpp -std=c++98 -pedantic -Wall
g++ -c context.cpp -std=c++98 -pedantic -Wall
...
g++ -o bbd baseobject.o context.o ...
[woq@evm bbd]$
</pre>


<h3>Code::Blocks (CLI version, bbd)</h3>

<p>Open the project, click on <em>Build</em> - <em>Build</em> menu item.</p>

<p>The environment is not set to call scripts for the source code generation, the files have to already exist. Run <em>make rebuild</em> and then build the application in Code::Blocks.</p>


<h3>Makefile (GUI version, bbdgui)</h3>

<pre class="screen">
[woq@evm diplomka]$ <strong>cd bbdgui/</strong>
[woq@evm bbdgui]$ <strong>qmake</strong>
[woq@evm bbdgui]$ <strong>make</strong>
g++ -c -pipe -g -Wall -W -D_REENTRANT -DQTGUI -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I../bbd -I. -I. -o main.o main.cpp
g++ -c -pipe -g -Wall -W -D_REENTRANT -DQTGUI -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I../bbd -I. -I. -o mainwindow.o mainwindow.cpp
...
g++  -o bbdgui main.o mainwindow.o ... -L/usr/lib -lpthread -lQtGui -lQtCore
[woq@evm bbdgui]$
</pre>

<p>The environment is not set to call scripts for the source code generation, the files have to already exist. Run <em>make rebuild</em> and then build the application.</p>


<h3>Qt Creator (GUI version, bbdgui)</h3>

<p>Open the project, click on <em>Build</em> - <em>Build All</em> menu item.</p>

<p>The environment is not set to call scripts for the source code generation, the files have to already exist. Run <em>make rebuild</em> and then build the application in Qt Creator.</p>


<?php
include 'p_end.php';
?>
