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
?>


<div id="sidebar">

<div class="label">Graphal</div>

<ul>
<li><?php MenuItem('index', 'Home'); ?></li>
<li><?php MenuItem('license', 'License'); ?></li>
<li><?php MenuItem('download', 'Download'); ?></li>
<li><?php Blank('http://sourceforge.net/projects/graphal/files/', 'Download');?></li>
<li><?php Blank('http://sourceforge.net/projects/graphal/support', 'Support');?></li>
</ul>


<div class="label">Documentation</div>

<ul>
<li><?php MenuItem('dependencies', 'Dependencies'); ?></li>
<li><?php MenuItem('compilation', 'Compilation'); ?></li>
<li><?php MenuItem('execution', 'Execution'); ?></li>
<li><?php MenuItem('language', 'Language'); ?>
	<ul>
	<li><?php MenuItem('preprocessor', 'Preprocessor'); ?></li>
	<li><?php MenuItem('grammar', 'Grammar'); ?></li>
	<li><?php MenuItem('variables', 'Variables'); ?></li>
	<li><?php MenuItem('functions', 'Functions'); ?></li>
	<li><?php MenuItem('builtin', 'Built-in functions'); ?>
		<ul>
		<li><?php MenuItem('builtin_output', 'Output'); ?></li>
		<li><?php MenuItem('builtin_containers', 'Containers'); ?></li>
		<li><?php MenuItem('builtin_iterators', 'Iterators'); ?></li>
		<li><?php MenuItem('builtin_graphs', 'Graphs'); ?></li>
		<li><?php MenuItem('builtin_visualization', 'Visualizations'); ?></li>
		<li><?php MenuItem('builtin_istype', 'isType'); ?></li>
		<li><?php MenuItem('builtin_debug', 'Debug'); ?></li>
		</ul>
	</li>
	</ul>
</li>
<li><?php MenuItem('visualizations', 'Vizualizations'); ?></li>
<li><?php MenuItem('graphs_format', 'Graphs file format'); ?></li>
</ul>


<div class="label">Development</div>

<ul>
<li><?php MenuItem('devel_contribute', 'Contribute');?></li>
<li><?php MenuItem('devel_new_builtin', 'Add built-in function'); ?></li>
<li><?php Blank('http://sourceforge.net/projects/graphal/', 'Project');?></li>
<li><?php Blank('http://sourceforge.net/p/graphal/code/', 'Repository');?></li>
<li><?php Blank('http://sourceforge.net/p/graphal/code/commit_browser', 'Commits');?></li>
<li><?php Blank('http://sourceforge.net/p/graphal/tickets/', 'Tickets');?></li>
</ul>

<div id="sf_logo"><a href="http://sourceforge.net/">
<img src="http://sflogo.sourceforge.net/sflogo.php?group_id=1461989&amp;type=2" alt="SourceForge.net" />
</a></div>

</div><!-- div id="sidebar" -->
