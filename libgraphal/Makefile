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
VERSION_MAJOR = 1
VERSION_MINOR = 0

TARGET = $(LIBRARY).$(VERSION_MAJOR).$(VERSION_MINOR)

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/libgraphal
DIST_DIR = $(PROJECT_DIR)/build/dist

GENERATED_DIR = generated

CC = g++

OPERATOR_SOURCES = $(wildcard generated/nodeunary*.cpp generated/nodebinary*.cpp)
BUILTIN_SOURCES = $(wildcard generated/nodebuiltin*.cpp)
SOURCES = $(wildcard *.cpp) $(OPERATOR_SOURCES) $(BUILTIN_SOURCES) $(GENERATED_DIR)/parser.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = -MMD -std=c++98 -pedantic -Wall -fPIC
INCLUDE_DIRS = -I. -Igenerated
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
all: bison operators builtin $(BUILD_DIR)/$(TARGET)


###############################################################################
#### Bison

.PHONY: bison
bison: $(GENERATED_DIR)/parser.cpp

$(GENERATED_DIR)/parser.cpp: parser.y
	mkdir -p $(GENERATED_DIR)
	bison --defines=$(GENERATED_DIR)/parser.h -o $@ $<


###############################################################################
#### Operators

.PHONY: operators
operators: $(OPERATOR_SOURCES)

$(OPERATOR_SOURCES): gen_operators.pl
	mkdir -p $(GENERATED_DIR)
	perl gen_operators.pl


###############################################################################
#### Builtin functions

.PHONY: builtin
builtin: $(BUILTIN_SOURCES)

$(BUILTIN_SOURCES): gen_builtin.pl
	mkdir -p $(GENERATED_DIR)
	perl gen_builtin.pl


###############################################################################
#### Compile

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$(LIBRARY).$(VERSION_MAJOR) -o $@ $(OBJECTS) $(LIB_DIRS) $(LDLIBS)
	ln -sf $(TARGET) $(BUILD_DIR)/$(LIBRARY).$(VERSION_MAJOR)
	ln -sf $(TARGET) $(BUILD_DIR)/$(LIBRARY)
ifeq ($(CONF), release)
	# Two part executable is generated in release
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)
endif
	# Copy to result to the dist directory
	mkdir -p $(DIST_DIR)
	cp -d $(BUILD_DIR)/$(LIBRARY)* $(DIST_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Dependencies for recompilation
-include $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)


###############################################################################
#### Clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)/$(LIBRARY)*
