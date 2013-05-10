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

###############################################################################
#### Options, configuration

# Prefix for installation directory
# Default: /usr/local.
export INSTALL_PREFIX = /usr/local

# Build configuration, 'debug' or 'release'.
# Default: release
export CONF = release

# Regenerate generated C++ sources, 'yes' or 'no'.
# Default: yes.
export GEN_CODE = yes

# Allow load shared libraries from the same directory where executable is stored, 'yes' or 'no'.
# Default: no.
export RPATH_ORIGIN = no


###############################################################################
####

PROJECT_DIR = .
BUILD_DIR = $(PROJECT_DIR)/build
DIST_DIR = $(PROJECT_DIR)/build/dist


###############################################################################
#### Default

.PHONY: all
all: compile


.PHONY: extra
extra: doxygen sloccount


###############################################################################
####

.PHONY: compile
compile:
	make -C libgraphal all
	make -C graphal_cli all
	make -C graphal_gui all


###############################################################################
#### Install, uninstall

.PHONY: strip
strip:
	make -C libgraphal strip
	make -C graphal_cli strip
	make -C graphal_gui strip


.PHONY: dist
dist:
	make -C libgraphal dist
	make -C graphal_cli dist
	make -C graphal_gui dist
	cp -r graphs samples $(BUILD_DIR)


.PHONY: install
install:
	make -C libgraphal install
	make -C graphal_cli install
	make -C graphal_gui install


.PHONY: uninstall
uninstall:
	make -C libgraphal uninstall
	make -C graphal_cli uninstall
	make -C graphal_gui uninstall


###############################################################################
#### Number of lines

.PHONY: lines
lines:
	cat `find . -name '*.cpp' && find . -name '*.h'` | wc -l


.PHONY: sloccount
sloccount:
	sloccount --duplicates --wide --details libgraphal graphal_cli graphal_gui > $(BUILD_DIR)/sloccount.sc


###############################################################################
#### Documentation

.PHONY: doxygen
doxygen:
	mkdir -p $(BUILD_DIR)/doxygen
	doxygen Doxyfile


###############################################################################
#### Web

.PHONY: web
web:
	mkdir -p $(BUILD_DIR)/web/
	cp -rv web/*.css web/images/ $(BUILD_DIR)/web/
	bash utils/offline_web.sh


###############################################################################
#### Clean

.PHONY: clean
clean:
	# make -C libgraphal clean
	# make -C graphal_cli clean
	# make -C graphal_gui clean
	rm -rf $(BUILD_DIR)
