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


LIBRARY = libgraphal.so
VERSION_MAJOR = 0
VERSION_MINOR = 0

TARGET = $(LIBRARY).$(VERSION_MAJOR).$(VERSION_MINOR)
BUILD_DIR = ../build/$(TARGET)

CC = g++

SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = -MMD -std=c++98 -pedantic -Wall
INCLUDE_DIRS =
LDFLAGS =
LDLIBS =
LIB_DIRS =

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


###############################################################################
#### Default

.PHONY: all
all: bison $(BUILD_DIR)/$(TARGET)


###############################################################################
#### Bison

bison: parser.cpp

parser.cpp: parser.y
	bison --defines=parser.h -o parser.cpp parser.y


###############################################################################
#### Compile

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) $(LIB_DIRS) -o $@
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$(LIBRARY).$(VERSION_MAJOR) -o $(TARGET) $(OBJECTS) $(LIB_DIRS) $(LDLIBS)
	ln -sf $(TARGET) $(LIBRARY).$(VERSION_MAJOR)
	ln -sf $(TARGET) $(LIBRARY)
ifeq ($(CONF), release)
	# Two part executable is generated in release
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)
	objdump -s -j .gnu_debuglink $(BUILD_DIR)/$(TARGET)
endif


$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Dependencies for recompilation
-include $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)


###############################################################################
#### Clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
