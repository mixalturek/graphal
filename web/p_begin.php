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


Header('Content-Type: text/html; charset=utf-8');
include_once 'p_func.php';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="cs">

<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />

<title><?php echo $g_title; ?></title>

<meta name="webmaster" content="Michal Turek; http://woq.nipax.cz/" />
<meta name="robots" content="all, follow" />
<meta name="resource-type" content="document" />

<style type="text/css" media="all">@import "style.css";</style>
<style type="text/css" media="print">@import "print.css";</style>
<link href="images/website/web_ico.png" rel="shortcut icon" type="image/x-icon" />
</head>

<body>

<div id="header"><a href="http://woq.nipax.cz/dip/">Graph algorithms interpreter</a></div>

<?php
include_once 'p_sidebar.php';
?>


<div id="page">

<h1><?php echo $g_title; ?></h1>
