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

<h3>Operating systems</h3>

<p>The development was in Debian Lenny GNU/Linux, the application was ported to MS Windows 2000 (VirtualBox) and MS Windows XP.</p>

<pre class="screen">
[woq@evm bbd]$ <strong>uname -a</strong>
Linux evm 2.6.26-1-686 #1 SMP Wed Nov 26 19:14:11 UTC 2008 i686 GNU/Linux
[woq@evm bbd]$
</pre>


<h3>Code::Blocks</h3>

<p><a href="http://www.codeblocks.org/">http://www.codeblocks.org/</a></p>

<pre class="screen">
[woq@evm bbd]$ <strong>apt-cache show codeblocks | grep Version</strong>
Version: 8.02
[woq@evm bbd]$
</pre>

<p>The version with integrated <em>GCC</em> and <em>GDB</em> (<em>codeblocks-8.02mingw-setup.exe</em>) was used under MS Windows.</p>


<h3>Qt, Qt Creator</h3>

<p><a href="http://www.qtsoftware.com/downloads">http://www.qtsoftware.com/downloads</a></p>

<pre class="screen">
[woq@evm ~]$ <strong>qtcreator -version 2>&amp;1 | grep Creator</strong>
Qt Creator 1.2.1 based on Qt 4.5.2
[woq@evm ~]$
</pre>

<p>The version <em>Qt libraries 4.5 for Windows (167 Mb)</em> (<em>qt-win-opensource-4.5.1-mingw.exe</em>) was used under MS Windows. The installer doesn't set the <em>PATH</em> variable, paths to <em>C:/Qt/4.5.1/bin</em> and <em>C:/MinGW/bin</em> directories have to be <a href="http://vlaurie.com/computers2/Articles/environment.htm">added manually</a>. The installer installs whole Qt including the documentation and the code samples, this parts can be deleted to save disk space.</p>


<h3>GNU Make</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>make -v | grep Make</strong>
GNU Make 3.81
[woq@evm bbd]$
</pre>


<h3>GCC</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>gcc -v | grep version</strong>
gcc version 4.3.2 (Debian 4.3.2-1.1)
[woq@evm bbd]$
</pre>


<h3>bison</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>bison -V | grep bison</strong>
bison (GNU Bison) 2.3
[woq@evm bbd]$
</pre>


<h3>makedepend</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>apt-cache show xutils-dev | grep Version</strong>
Version: 1:7.4+3
[woq@evm bbd]$
</pre>


<h3>Perl</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>perl -v | grep 'This is perl'</strong>
This is perl, v5.10.0 built for i486-linux-gnu-thread-multi
[woq@evm bbd]$
</pre>


<h3>Doxygen</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>doxygen --versionn</strong>
1.5.6
[woq@evm bbd]$ <strong>apt-cache show graphviz | grep Version</strong>
Version: 2.20.2-3
[woq@evm bbd]$
</pre>


<h3>SVN, StatSVN</h3>

<pre class="screen">
[woq@evm bbd]$ <strong>svn --version | grep version</strong>
svn, version 1.5.1 (r32289)
[woq@evm bbd]$ <strong>apt-cache show statsvn | grep Version</strong>
Version: 0.4.0.dfsg-1
[woq@evm bbd]$
</pre>


<?php
include 'p_end.php';
?>
