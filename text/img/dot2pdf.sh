#!/bin/bash
#
# Copyright (C) 2009 Michal Turek
# License: GNU GPL v2
#
# Converts Doxygen/dot diagrams to PDF format,
# that can be used in pdflatex as vector images
#
# Doxyfile
# DOT_CLEANUP            = NO

for file in *.dot
do
	name=`echo ${file} | cut -f1 -d.`
	echo "${name}.dot -> ${name}.pdf"
	dot -Tsvg -o ${name}.svg ${name}.dot
	rsvg-convert -f pdf -o ${name}.pdf ${name}.svg
	rm ${name}.svg
done
