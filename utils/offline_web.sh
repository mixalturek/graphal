#!/bin/bash
#
# Copyright 2013 Michal Turek
#
# This file is part of Graphal.
# http://graphal.sourceforge.net/
#
# Graphal is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# Graphal is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Graphal.  If not, see <http://www.gnu.org/licenses/>.
#
# One purpose script to generate offline website.

SERVER_PATH=http://localhost/~woq/graphal

for file in `ls -1 web/*.php | grep -v 'p_.*php'`
do
	newFile=`echo "$file" | cut -f2 -d/ | cut -f1 -d.`.html
	echo "$SERVER_PATH/$file?offline -> build/web/$newFile"
	wget "$SERVER_PATH/$file?offline" --output-document "build/web/$newFile" -o /dev/null
done
