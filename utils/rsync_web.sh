#!/bin/bash -ex
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
# One purpose script to upload website.

# http://sourceforge.net/apps/trac/sourceforge/wiki/Project%20web
# https://sourceforge.net/apps/trac/sourceforge/wiki/Rsync%20over%20SSH

# mkdir mnt
# sshfs mixalturek@web.sourceforge.net:/home/project-web/graphal mnt
# fusermount -u mnt

rsync -aP -e ssh build/web/ mixalturek@web.sourceforge.net:/home/project-web/graphal/htdocs/
