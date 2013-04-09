#!/bin/bash

for file in `find . -type f`
do
	echo $file
	sed -i 's%#include "\(.*\).hpp"%#include "\1.h"%' $file
done
