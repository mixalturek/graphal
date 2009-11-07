#!/usr/bin/perl -w

use constant NUM => 10000000;
use constant DISP => 100000;

sub func
{
	my ($val) = @_;
	return $val * 2;
}

for($i = 0; $i < NUM; $i++)
{
	$tmp = func($i);
	$tmp++;
#	print "debug: $i\n" if($i % DISP == 0);
}

exit(0);
