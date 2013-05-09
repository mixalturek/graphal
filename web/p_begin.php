<?php
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