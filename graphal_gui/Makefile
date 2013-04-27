# Copyright 2013 Michal Turek <http://woq.nipax.cz/>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.


TARGET = graphal_gui

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/$(TARGET)
DIST_DIR = $(PROJECT_DIR)/build/dist

# Release is a default configuration
ifndef CONF
CONF = release
endif


###############################################################################
#### Default

.PHONY: all
all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=$(CONF) -o Makefile ../../$(TARGET)/$(TARGET).pro
	make -C $(BUILD_DIR)
ifeq ($(CONF), release)
	# Two part executable is generated in release
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)
endif
	# Copy the result to the dist directory
	mkdir -p $(DIST_DIR)
	cp $(BUILD_DIR)/$(TARGET)* $(DIST_DIR)


###############################################################################
#### Clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)/$(TARGET)*
