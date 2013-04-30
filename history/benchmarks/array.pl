#!/usr/bin/perl -w

use constant NUM => 10000000;
use constant DISP => 100000;
use constant SIZE => 5;

for($i = 0; $i < NUM; $i++)
{
	$a[$i % SIZE] = $i * 2;
	$a[$i % SIZE]++;
#	print "debug: $i\n" if($i % DISP == 0);
}

exit(0);
