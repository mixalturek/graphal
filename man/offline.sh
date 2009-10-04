#!/bin/bash
#
# Copyright (C) 2007 Michal Turek
# License: GNU GPL v2
#
# Generate HTML version of web pages in PHP

rm -rf ./html
mkdir ./html

cp -r php/images php/style.css php/print.css html

for filename in php/*.php ;
do
	name=`echo ${filename} | cut -f1 -d. | cut -f2 -d/`
	echo "$name"

	wget -O html/${name}.html "http://localhost/~woq/dip/${filename}?offline"
done

rm html/download.html html/p_*.html
rm -rf html/images/.svn/ html/images/website/.svn/ html/images/screenshot/.svn/
