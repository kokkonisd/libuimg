DEBUG ?= 1
ERROREXIT ?= 1
PREFIX ?= /usr/local

TARGET = $(BUILD_DIR)/libuimg
TARGET_STATIC = $(patsubst %, %.a, $(TARGET))
TARGET_DYNAMIC = $(patsubst %, %.so, $(TARGET))

CC = gcc
AR = ar
CFLAGS = -Wall -Wextra
SOURCE_DIR = src
BUILD_DIR = build
TEST_DIR = tests
INCLUDES = -Isrc -I$(TEST_DIR)/cuts/src


HEADERS = $(wildcard $(SOURCE_DIR)/*.h)
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))
TEST_TARGETS = $(patsubst %.o, %, $(TEST_OBJECTS))
SOURCE_OBJECTS = $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))


ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif


ifeq ($(shell uname -s), Linux)
	DYNAMIC_LIB_FLAG = -shared
	TARGET_DYNAMIC = $(patsubst %, %.so, $(TARGET))
else
	DYNAMIC_LIB_FLAG = -dynamiclib
	TARGET_DYNAMIC = $(patsubst %, %.dylib, $(TARGET))
endif


all: build $(TARGET_STATIC) $(TARGET_DYNAMIC) $(TEST_TARGETS)


tests: build $(TEST_TARGETS)
	@for test in $(TEST_TARGETS) ; do \
		./$$test || exit $(ERROREXIT); \
		echo "" ; \
	done


memchecks: build $(TEST_TARGETS)
ifeq ($(shell uname -s), Linux)
	@for test in $(TEST_TARGETS) ; do \
		valgrind --leak-check=full --error-exitcode=1 $$test || exit $(ERROREXIT); \
		echo "" ; \
	done
else
	@for test in $(TEST_TARGETS) ; do \
		macgrind . $$test --run-before "make clean" || exit $(ERROREXIT); \
		echo "" ; \
	done
endif


install: build $(TARGET_STATIC) $(TARGET_DYNAMIC)
	install $(TARGET_STATIC) $(PREFIX)/lib/
	install $(TARGET_DYNAMIC) $(PREFIX)/lib/
	install $(HEADERS) $(PREFIX)/include/


$(TARGET_STATIC): $(SOURCE_OBJECTS)
	$(AR) rcs $@ $^


$(TARGET_DYNAMIC): $(SOURCE_OBJECTS)
	$(CC) $(DYNAMIC_LIB_FLAG) -o $@ $^


$(SOURCE_DIR)/%.c: $(SOURCE_DIR)/%.h


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@


$(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%.o $(TARGET_DYNAMIC)
	$(CC) $(CFLAGS) $(INCLUDES) -L$(BUILD_DIR) -Wl,-rpath,$(BUILD_DIR) $< -o $@ -luimg


build:
	@mkdir -p $(BUILD_DIR)/


clean:
	rm -rf $(BUILD_DIR)/


.SECONDARY: $(TEST_OBJECTS)

.PHONY: all clean build unittest memcheck
