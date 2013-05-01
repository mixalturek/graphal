#
# Copyright 2013 Michal Turek
#
# This file is part of Graphal library.
# http://graphal.sourceforge.net/
#
# Graphal library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# Graphal library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Graphal library.  If not, see <http://www.gnu.org/licenses/>.
#


LIBRARY = libgraphal.so

# See graphal_version.h
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_RELEASE = 0

TARGET = $(LIBRARY).$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_RELEASE)

PROJECT_DIR = ..
BUILD_DIR = $(PROJECT_DIR)/build/libgraphal
DIST_DIR = $(PROJECT_DIR)/build/dist

GENERATED_DIR = generated

CC = g++

OPERATOR_SOURCES = $(wildcard generated/nodeunary*.cpp generated/nodebinary*.cpp)
BUILTIN_SOURCES = $(wildcard generated/nodebuiltin*.cpp)
SOURCES = $(wildcard *.cpp) $(OPERATOR_SOURCES) $(BUILTIN_SOURCES) $(GENERATED_DIR)/parser.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

CFLAGS = -MMD -std=c++98 -pedantic -Wall -Wextra -Werror -fPIC
INCLUDE_DIRS = -I. -Igenerated
LDFLAGS = -Wl,--no-undefined
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
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$(LIBRARY).$(VERSION_MAJOR).$(VERSION_MINOR) -o $@ $(OBJECTS) $(LIB_DIRS) $(LDLIBS)
	ln -sf $(TARGET) $(BUILD_DIR)/$(LIBRARY).$(VERSION_MAJOR).$(VERSION_MINOR)
	ln -sf $(TARGET) $(BUILD_DIR)/$(LIBRARY).$(VERSION_MAJOR)
	ln -sf $(TARGET) $(BUILD_DIR)/$(LIBRARY)
ifeq ($(CONF), release)
	# Two part executable is generated in release
	objcopy --only-keep-debug $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(TARGET).debug
	objcopy --strip-unneeded $(BUILD_DIR)/$(TARGET)
	objcopy --add-gnu-debuglink=$(BUILD_DIR)/$(TARGET).debug $(BUILD_DIR)/$(TARGET)
endif
	# Copy the result to the dist directory
	mkdir -p $(DIST_DIR)
	cp -d $(BUILD_DIR)/$(LIBRARY)* $(DIST_DIR)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@


# Dependencies for recompilation
-include $(SOURCES:%.cpp=$(BUILD_DIR)/%.d)


###############################################################################
#### Install, uninstall

.PHONY: install
install: all
	install -d $(INSTALL_PREFIX)/lib
	install -m 755 $(DIST_DIR)/$(TARGET) $(INSTALL_PREFIX)/lib
	/sbin/ldconfig -v -n $(INSTALL_PREFIX)/lib
	# TODO: header files of the shared library


.PHONY: uninstall
uninstall:
	rm -f $(INSTALL_PREFIX)/lib/libgraphal.so*
	/sbin/ldconfig -v -n $(INSTALL_PREFIX)/lib
	# TODO: header files of the shared library


###############################################################################
#### Clean

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)/$(LIBRARY)*


###############################################################################
#### List the builtin functions

.PHONY: listbuiltin
listbuiltin:
	grep '\$funcdecl =' gen_builtin.pl | sed "s/.*'\(.*\)'.*/\1/"
