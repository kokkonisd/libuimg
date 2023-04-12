# LIBUIMG CENTRAL MAKEFILE

# ---------------------------------------------------------------------------------------------------------------------
# Compiler & build customization
# ---------------------------------------------------------------------------------------------------------------------

# Builds for production by default; set to 1 to enable debug flags and turn off optimization
DEBUG ?= 0
# Do not use address sanitizer by default; set to 1 to enable it. Note that DEBUG must be enabled in order for this to
# have any effect.
ADDRSAN ?= 0
# Returns an exit code of 1 if anything goes wrong, set to 0 if you don't want failing tests tests/memory checks
# crashing the make process
ERROREXIT ?= 1
# Prefix to where the library should be installed
PREFIX ?= /usr/local

# Host compiler
HOST_CC ?= gcc
# Host ar
HOST_AR ?= ar
# Host ranlib
HOST_RANLIB ?= ranlib

# Compiler suite prefix for cross-compiled ARM builds with an underlying OS (such as the Raspberry Pi)
CROSS_PREFIX ?= arm-linux-gnueabihf-
# Compiler suite prefix for cross-compiled ARM builds for bare-metal targets (such as STM32 MCUs)
CROSS_BM_PREFIX ?= arm-none-eabi-

# Cross-compiler suite tools (with OS)
CROSS_CC := $(CROSS_PREFIX)gcc
CROSS_AR := $(CROSS_PREFIX)ar
CROSS_RANLIB := $(CROSS_PREFIX)ranlib

# Bare-metal cross-compiler suite tools
CROSS_BM_CC := $(CROSS_BM_PREFIX)gcc
CROSS_BM_AR := $(CROSS_BM_PREFIX)ar
CROSS_BM_RANLIB := $(CROSS_BM_PREFIX)ranlib

# Flags for bare-metal cross compiler (to be set by the user before compilation)
CROSS_BM_CPU ?=
CROSS_BM_CFLAGS ?=


# ---------------------------------------------------------------------------------------------------------------------
# Library & compiler flag definitions
# ---------------------------------------------------------------------------------------------------------------------

# Source code directory
SOURCE_DIR = src
# Header directory
INCLUDE_DIR = inc
# Build directory
BUILD_DIR = build
# Test directory
TEST_DIR = tests

# Basic compiler flags
CFLAGS = -Wall -Wextra
# Include dirs (for building & testing)
INCLUDES = -I$(INCLUDE_DIR) -I$(TEST_DIR)/cuts/src


# Static & shared library definitions
TARGET = $(BUILD_DIR)/lib/libuimg

# Static lib for x86
TARGET_STATIC_HOST = $(patsubst %, %.a, $(TARGET))
# Static lib for ARM
TARGET_STATIC_ARM = $(patsubst %, %-arm.a, $(TARGET))
# Bare-metal static lib for ARM
TARGET_STATIC_ARM_BM = $(patsubst %, %-arm-bm.a, $(TARGET))

# Dynamic lib for Linux (compiled for host)
TARGET_DYNAMIC_HOST_LINUX = $(patsubst %, %.so, $(TARGET))
# Dynamic lib for macOS (compiled for host)
TARGET_DYNAMIC_HOST_MACOS = $(patsubst %, %.dylib, $(TARGET))
# Dynamic lib for ARM
TARGET_DYNAMIC_ARM = $(patsubst %, %-arm.so, $(TARGET))

# Flags for the dynamic host Linux library (.so)
DLIB_FLAGS_HOST_LINUX = -shared
# Flags for the dynamic host macOS library (.dylib)
DLIB_FLAGS_HOST_MACOS = -dynamiclib
# Flags for the dynamic cross ARM library (with OS) (.so)
DLIB_FLAGS_ARM = -shared -fPIC
# Linked libraries for the dynamic cross ARM library (with OS)
LIBS_ARM = -lgcc -lc -lm


# Header files (to be installed)
MAIN_HEADER = $(INCLUDE_DIR)/libuimg.h
HEADERS = $(wildcard $(INCLUDE_DIR)/libuimg/*.h)
# Source files
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
# Source files for tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.c)

# Source object files for the host
SOURCE_OBJECTS_HOST = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
# Source object files for an ARM target (with an OS)
SOURCE_OBJECTS_ARM = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%-arm.o, $(SOURCES))
# Source object files for a bare-metal ARM target
SOURCE_OBJECTS_ARM_BM = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%-arm-bm.o, $(SOURCES))
# Test object files (for the host only)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))
# Test binary files (for the host only)
TEST_TARGETS = $(patsubst %.o, %, $(TEST_OBJECTS))


# Set optimization/debug flags based on the global DEBUG flag
ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0 -coverage

	# Optionally enable the address sanitizer
	ifeq ($(ADDRSAN), 1)
		CFLAGS += -fsanitize=address -static-libasan
	endif
else
	CFLAGS += -O3
endif


# ---------------------------------------------------------------------------------------------------------------------
# Makefile high-level targets (to be used directly by the user)
# ---------------------------------------------------------------------------------------------------------------------

# By default, only build the static library for the host
all: build $(TARGET_STATIC_HOST)


# Build only the static & macOS dynamic library for the host
macos: build $(TARGET_STATIC_HOST) $(TARGET_DYNAMIC_HOST_MACOS)


# Build only the static & Linux dynamic library for the host
linux: build $(TARGET_STATIC_HOST) $(TARGET_DYNAMIC_HOST_LINUX)


# Build only the static & dynamic library for an ARM target (with an OS)
arm: build $(TARGET_STATIC_ARM) $(TARGET_DYNAMIC_ARM)


# Build only the static library for a bare-metal ARM target
arm-bm: build $(TARGET_STATIC_ARM_BM)


# Build & run tests (for the host only)
tests: build $(TEST_TARGETS)
	@for test in $(TEST_TARGETS) ; do \
		./$$test || exit $(ERROREXIT); \
		echo "" ; \
	done


# Build & run memory checks (for the host only)
# If host is running macOS, macgrind should be installed (see README.md)
memchecks: build $(TEST_TARGETS)
ifeq ($(shell uname -s), Darwin)
	@for test in $(TEST_TARGETS) ; do \
		macgrind . $$test --custom-command "make tests" --run-before "make clean" || exit $(ERROREXIT); \
		echo "" ; \
	done
else
	@for test in $(TEST_TARGETS) ; do \
		valgrind --leak-check=full --error-exitcode=1 $$test || exit $(ERROREXIT); \
		echo "" ; \
	done
endif


# Run tests and get code coverage
coverage: build tests
ifeq ($(DEBUG), 0)
	$(error Coverage not available in production mode, set DEBUG to 1)
endif
	gcov -o $(BUILD_DIR) $(SOURCES)


# Install built libraries and header files
install: build
	@mkdir -p $(PREFIX)/lib/
	@mkdir -p $(PREFIX)/include/libuimg/
#   Install headers (with rw-rw-r-- permissions)
	install -t $(PREFIX)/include/ -m=664 $(MAIN_HEADER)
	install -t $(PREFIX)/include/libuimg/ -m=664 $(HEADERS)
#   Install libraries
	install -t $(PREFIX)/lib/ $(shell ls -d $(BUILD_DIR)/lib/*)
#   Run ldconfig to configure installed libraries (and make them usable)
#   Note that we do not run `ldconfig -n $(PREFIX)/lib/` because the user might not want the install to go into the
#   "global" cache (e.g. when installing in a local "test" directory to test out the library without polluting the
#   system)
	ldconfig


# Uninstall libraries & headers (assuming a normal install)
uninstall:
	rm $(PREFIX)/lib/libuimg.*
	rm $(PREFIX)/include/libuimg.h
	rm -rf $(PREFIX)/include/libuimg/

# ---------------------------------------------------------------------------------------------------------------------
# Low-level build rules
# ---------------------------------------------------------------------------------------------------------------------


# Build the static library for the host
$(TARGET_STATIC_HOST): $(SOURCE_OBJECTS_HOST)
	$(HOST_AR) rcs $@ $^
	$(HOST_RANLIB) $@


# Build the static library for an ARM target (with an OS)
$(TARGET_STATIC_ARM): $(SOURCE_OBJECTS_ARM)
	$(CROSS_AR) rcs $@ $^
	$(CROSS_RANLIB) $@


# Build the static library for a bare-metal ARM target
$(TARGET_STATIC_ARM_BM): $(SOURCE_OBJECTS_ARM_BM)
	$(CROSS_BM_AR) rcs $@ $^
	$(CROSS_BM_RANLIB) $@


# Build the dynamic library for Linux on host
$(TARGET_DYNAMIC_HOST_LINUX): $(SOURCE_OBJECTS_HOST)
	$(HOST_CC) $(DLIB_FLAGS_HOST_LINUX) -o $@ $^


# Build the dynamic library for macOS on host
$(TARGET_DYNAMIC_HOST_MACOS): $(SOURCE_OBJECTS_HOST)
	$(HOST_CC) $(DLIB_FLAGS_HOST_MACOS) -o $@ $^


# Build the dynamic library for an ARM target (with an OS)
$(TARGET_DYNAMIC_ARM): $(SOURCE_OBJECTS_ARM)
	$(CROSS_CC) $(DLIB_FLAGS_ARM) -o $@ $^ $(LIBS_ARM)


$(SOURCE_DIR)/%.c: $(SOURCE_DIR)/%.h


# Build objects for host architecture (usually x86)
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(HOST_CC) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@


# Build objects for ARM architecture
$(BUILD_DIR)/%-arm.o: $(SOURCE_DIR)/%.c
	$(CROSS_CC) $(CFLAGS) $(INCLUDES) -marm -c $< -o $@


# Build objects for ARM bare-metal architecture
# It is mandatory for the user to set at least the CROSS_BM_CPU variable
$(BUILD_DIR)/%-arm-bm.o: $(SOURCE_DIR)/%.c
ifndef CROSS_BM_CPU
	$(error Please specify bare-metal CPU (and possibly flags) by setting CROSS_BM_CPU and CROSS_BM_CFLAGS)
endif
	$(CROSS_BM_CC) $(CFLAGS) $(INCLUDES) -mcpu=$(CROSS_BM_CPU) -mthumb $(CROSS_BM_CFLAGS) -c $< -o $@


# Build test objects (for host only)
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.c
	$(HOST_CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# Build test binaries (for host only)
$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(TARGET_STATIC_HOST) $(SOURCE_OBJECTS_HOST)
	$(HOST_CC) $(CFLAGS) $(INCLUDES) -L$(BUILD_DIR)/lib -Wl,-rpath,$(BUILD_DIR)/lib $< -o $@ -luimg


# ---------------------------------------------------------------------------------------------------------------------
# Build & cleanup rules
# ---------------------------------------------------------------------------------------------------------------------

# Create the build directory
build:
	@mkdir -p $(BUILD_DIR)/lib


# Remove the build directory, cleaning up everything
clean:
	rm -rf $(BUILD_DIR)/ *.gcov


# Keep test .o files
.SECONDARY: $(TEST_OBJECTS)


.PHONY: all macos linux arm arm-bm tests memchecks install uninstall clean
