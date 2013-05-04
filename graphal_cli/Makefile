#
# Copyright 2013 Michal Turek
#
# This file is part of Graphal CLI.
# http://graphal.sourceforge.net/
#
# Graphal CLI is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# Graphal CLI is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Graphal CLI.  If not, see <http://www.gnu.org/licenses/>.
#


###############################################################################
#### Options, configuration

TARGET = graphal_cli

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/$(TARGET)
DIST_DIR = $(PROJECT_DIR)/build/dist

CC = g++

SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = -MMD -std=c++98 -pedantic -Wall -Wextra -Werror -g
INCLUDE_DIRS = -I. -I$(PROJECT_DIR)/libgraphal/ -I$(PROJECT_DIR)/libgraphal/generated/
LDFLAGS =
LDLIBS = -lgraphal
LIB_DIRS = -L$(PROJECT_DIR)/build/libgraphal/


ifeq ($(CONF), release)
CFLAGS += -DNDEBUG -O2
endif


ifeq ($(RPATH_ORIGIN), yes)
LDFLAGS += -Wl,-rpath,'$$ORIGIN'
endif


###############################################################################
#### Default

.PHONY: all
all: $(BUILD_DIR)/$(TARGET)


###############################################################################
#### Compile

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB_DIRS) $(LDLIBS)


$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Dependencies for recompilation
-include $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)


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
	rm -rf $(BUILD_DIR) $(DIST_DIR)/$(TARGET)


###############################################################################
#### Basic memory leaks check

.PHONY: tests
tests:
	valgrind --leak-check=full --show-reachable=yes $(DIST_DIR)/$(TARGET) --unit-tests $(PROJECT_DIR)/samples/tests.txt
