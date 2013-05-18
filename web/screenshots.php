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


$g_title = 'Screenshots';
include 'p_begin.php';
?>

<div class="screenshots">
<?php
Img('images/screenshots/graphal_cli_scripts_sm.png', 'Graphal CLI');
Img('images/screenshots/graphal_gui_dfs_sm.png', 'Depth first search');
Img('images/screenshots/graphal_gui_house_sm.png', 'Debugging and visualizations');
Img('images/screenshots/graphal_gui_docks_sm.png', 'Dock windows');
?>
</div>

<?php
include 'p_end.php';
?>
