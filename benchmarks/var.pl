#!/usr/bin/perl -w

use constant NUM => 10000000;
use constant DISP => 100000;

for($i = 0; $i < NUM; $i++)
{
	$tmp = $i * 2;
	$tmp++;
#	print "debug: $i\n" if($i % DISP == 0);
}

exit(0);
