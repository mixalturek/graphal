#
# Copyright 2013 Michal Turek
#
# This file is part of Graphal GUI.
# http://graphal.sourceforge.net/
#
# Graphal GUI is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# Graphal GUI is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Graphal GUI.  If not, see <http://www.gnu.org/licenses/>.
#


###############################################################################
#### Options, configuration

TARGET = graphal_gui

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/$(TARGET)
DIST_DIR = $(PROJECT_DIR)/build/dist

ifeq ($(RPATH_ORIGIN), yes)
ORIGIN_FLAG = QMAKE_LFLAGS+=-Wl,-rpath,'\\\$$\$$ORIGIN'
# Command line: QMAKE_LFLAGS+=-Wl,-rpath,'\\\$\$ORIGIN'
# Generated Makefile: LFLAGS = -Wl,-rpath,\$$ORIGIN
# Command line: g++ -Wl,-rpath,\$ORIGIN
# Ufff...
endif

###############################################################################
#### Default

.PHONY: all
all: $(BUILD_DIR)/Makefile
	make -C $(BUILD_DIR)


$(BUILD_DIR)/Makefile: $(TARGET).pro
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake -makefile -Wall CONFIG+=$(CONF) $(ORIGIN_FLAG) -o Makefile ../../$(TARGET)/$(TARGET).pro


###############################################################################
#### Install, uninstall

.PHONY: strip
strip: all $(BUILD_DIR)/$(TARGET).debug

$(BUILD_DIR)/$(TARGET).debug: $(BUILD_DIR)/$(TARGET)
	# Two part executable is generated
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)


.PHONY: dist
dist: all
	mkdir -p $(DIST_DIR)
	cp $(BUILD_DIR)/$(TARGET)* $(DIST_DIR)


.PHONY: install
install: all
	install -d $(INSTALL_PREFIX)/bin
	install -m 755 $(BUILD_DIR)/$(TARGET) $(INSTALL_PREFIX)/bin


.PHONY: uninstall
uninstall:
	rm -f $(INSTALL_PREFIX)/bin/$(TARGET)


###############################################################################
#### Clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)/$(TARGET)*
