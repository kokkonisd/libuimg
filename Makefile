DEBUG = 1

CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build
# TST_DIR = tests
INC_DIRS = -Isrc #-Itests


TARGET = $(BUILD_DIR)/libimg


SOURCES = $(wildcard $(SRC_DIR)/*.c)
TESTS = $(wildcard $(TST_DIR)/test_*.c)
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))


ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
# 	EXTRA_TASKS = unittest memcheck
	ERROREXIT = 0
else
	CFLAGS += -O3
	ERROREXIT = 1
endif


all: build $(TARGET) #$(EXTRA_TASKS)

$(TARGET): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(INC_DIRS) $(SRC_OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

$(SRC_DIR)/%.c: $(SRC_DIR)/%.h


# unittest: $(BUILD_DIR)/tests
# ifeq ($(ERROREXIT), 1)
# 	@./$(BUILD_DIR)/tests --reporter console 
# else
# 	@./$(BUILD_DIR)/tests --reporter console || \
# 		 (echo "\033[0;33m[Something went wrong during testing. Launching debugger.]\033[0m"; \
# 		 gdb --silent --args ./$(BUILD_DIR)/tests --reporter console -b)
# endif


# memcheck: $(BUILD_DIR)/tests
# ifeq ($(shell uname -s), Linux)
# 	@valgrind --leak-check=full --error-exitcode=1 ./$(BUILD_DIR)/tests -o /dev/null 2> $(BUILD_DIR)/valgrind.log \
# 				&& (echo "\033[0;32m[Valgrind PASS]\033[0m") \
# 				|| (echo "\033[0;31m[Valgrind FAIL]\033[0m"; exit $(ERROREXIT))
# else
# 	@pip3 install macgrind > /dev/null
# 	@macgrind . ./$(BUILD_DIR)/tests --run-before "make clean" > $(BUILD_DIR)/valgrind.log \
# 				&& (echo "\033[0;32m[Valgrind PASS]\033[0m") \
# 				|| (echo "\033[0;31m[Valgrind FAIL]\033[0m"; exit $(ERROREXIT))
# endif



build:
	@mkdir -p $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)/


.PHONY: all clean build #unittest memcheck
