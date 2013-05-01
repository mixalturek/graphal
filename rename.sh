#!/bin/bash

for file in `find . -type f`
do
	echo $file
	sed -i 's% \*      Copyright % * Copyright %' $file
done
