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


$g_title = 'Dependencies';
include 'p_begin.php';
?>

<p>Graphal was designed to have as less dependencies as possible. Graphal library and Graphal CLI requires only C++ compiler and standard C++ library STL. Source code generation using GNU Bison and Perl can be disabled during build, the repository contains pregenerated source codes. Graphal GUI adds only Qt library and relevant Qt tools to the dependencies.</p>

<pre class="screen">
[woq@evm graphal]$ <strong>./configure</strong>
Checking build tools for libGraphal and Graphal CLI...
    make: yes
    g++: yes
    mkdir: yes
    cp: yes
    rm: yes
    ln: yes
    bison: yes
    perl: yes

Checking additional build tools for Graphal GUI...
    qmake: yes

Checking install tools...
    install: yes
    /sbin/ldconfig: yes

Checking optional tools...
    objcopy: yes
    doxygen: yes
    sloccount: yes
    cat: yes
    find: yes
    wc: yes
    grep: yes
    valgrind: yes

It seems all mandatory tools are available, build and optionally install the software using:
make
make install
[woq@evm graphal]$
</pre>


<h2>Operating Systems</h2>

<p>Graphal was implemented under Debian Lenny GNU/Linux (2008, 2009) and then Debian Squeeze GNU/Linux (2013) operating systems. The application was successfully ported to MS Windows 2000 and MS Windows XP.</p>


<h2>GNU Make</h2>

<pre class="screen">
[woq@evm graphal]$ <strong>make -v | grep Make</strong>
GNU Make 3.81
[woq@evm graphal]$
</pre>


<h2>GNU gcc</h2>

<pre class="screen">
[woq@evm graphal]$ <strong>gcc -v | grep version</strong>
gcc version 4.3.2 (Debian 4.3.2-1.1)
[woq@evm graphal]$
</pre>


<h2>GNU Bison</h2>

<pre class="screen">
[woq@evm graphal]$ <strong>bison -V | grep bison</strong>
bison (GNU Bison) 2.3
[woq@evm graphal]$
</pre>


<h2>Perl</h2>

<pre class="screen">
[woq@evm graphal]$ <strong>perl -v | grep 'This is perl'</strong>
This is perl, v5.10.0 built for i486-linux-gnu-thread-multi
[woq@evm graphal]$
</pre>


<h2>Qt, Qt Creator</h2>

<pre class="screen">
[woq@evm ~]$ <strong>qtcreator -version 2>&amp;1 | grep Creator</strong>
Qt Creator 1.2.1 based on Qt 4.5.2
[woq@evm ~]$
</pre>


<p>The version <em>Qt libraries 4.5 for Windows (167 Mb)</em> (<em>qt-win-opensource-4.5.1-mingw.exe</em>) was used under MS Windows. The installer doesn't set the <em>PATH</em> variable, paths to <em>C:/Qt/4.5.1/bin</em> and <em>C:/MinGW/bin</em> directories have to be <a href="http://vlaurie.com/computers2/Articles/environment.htm">added manually</a>. The installer installs whole Qt including the documentation and the code samples, this parts can be deleted to save disk space.</p>


<?php
include 'p_end.php';
?>
