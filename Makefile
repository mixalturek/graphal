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


PROJECT_DIR = .
BUILD_DIR = $(PROJECT_DIR)/build
DIST_DIR = $(PROJECT_DIR)/build/dist

INSTALL_PREFIX = /usr/local


###############################################################################
#### Default

.PHONY: all
all: build doxygen sloccount


###############################################################################
####

.PHONY: build
build:
	make -C libgraphal all
	make -C graphal_cli all
	make -C graphal_gui all

	# TODO:
	# make -C ./benchmarks/
	# make -C ./graphs_generator/
	# make -C ./man/
	# make -C ./presentation/
	# make -C ./text/


###############################################################################
#### Install

.PHONY: install
install: build
	install -d $(INSTALL_PREFIX)/lib
	cp -d $(DIST_DIR)/libgraphal.so* $(INSTALL_PREFIX)/lib
	install -d $(INSTALL_PREFIX)/bin
	install -m 755 $(DIST_DIR)/graphal_cli $(INSTALL_PREFIX)/bin
	install -m 755 $(DIST_DIR)/graphal_gui $(INSTALL_PREFIX)/bin
	# TODO: header files of the shared library


###############################################################################
#### Uninstall

uninstall:
	rm -f $(INSTALL_PREFIX)/lib/libgraphal.so*
	rm -f $(INSTALL_PREFIX)/bin/graphal_cli
	rm -f $(INSTALL_PREFIX)/bin/graphal_gui
	# TODO: header files of the shared library


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
#### Clean

.PHONY: clean
clean:
	# make -C libgraphal clean
	# make -C graphal_cli clean
	# make -C graphal_gui clean
	rm -rf $(BUILD_DIR)

	# TODO:
	# make -C ./benchmarks/ clean
	# make -C ./graphs_generator/ clean
	# make -C ./man/ clean
	# make -C ./presentation/ clean
	# rm -rf ./doc/
	# make -C ./text/ clean
