#!/bin/bash

for file in `find . -name '*.hpp'`
do
	#echo $file
	name=`echo $file | cut -f 1-2 -d.`
	echo $name
	mv $file $name.h
done
