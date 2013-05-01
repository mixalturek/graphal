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


TARGET = graphal_cli

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/$(TARGET)
DIST_DIR = $(PROJECT_DIR)/build/dist

CC = g++

SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = -MMD -std=c++98 -pedantic -Wall -Wextra -Werror
INCLUDE_DIRS = -I. -I$(PROJECT_DIR)/libgraphal/ -I$(PROJECT_DIR)/libgraphal/generated/
LDFLAGS =
LDLIBS = -lgraphal
LIB_DIRS = -L$(DIST_DIR)

# Release is a default configuration
ifndef CONF
CONF = release
endif

ifeq ($(CONF), release)
# Two part executable is generated in release
CFLAGS += -DNDEBUG -O2 -g
else
CFLAGS += -g
endif

# Allow load libgraphal.so from the same directory where the binary is stored
LDFLAGS += -Wl,-rpath,'$$ORIGIN'


###############################################################################
#### Default

.PHONY: all
all: $(BUILD_DIR)/$(TARGET)


###############################################################################
#### Compile

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB_DIRS) $(LDLIBS)
ifeq ($(CONF), release)
	# Two part executable is generated in release
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)
endif
	# Copy the result to the dist directory
	mkdir -p $(DIST_DIR)
	cp $(BUILD_DIR)/$(TARGET)* $(DIST_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Dependencies for recompilation
-include $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)


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
