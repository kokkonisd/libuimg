# LIBUIMG FUZZING MAKEFILE

#----------------------------------------------------------------------------------------------------------------------
# Fuzzing setup customization.
# ---------------------------------------------------------------------------------------------------------------------

# Directories related to the AFL++ submodule and to the binaries used in fuzzing.
AFL_DIR = AFLplusplus
SOURCE_DIR = src
BUILD_DIR = build
IN_FUZZ_DIR = in
OUT_FUZZ_DIR = out
CRASHES_DIR = $(OUT_FUZZ_DIR)/default/crashes

# Definitions of binaries needed for fuzzing, as well as the libuimg library itself.
TARGET = libuimg_fuzz
GENERATE_IMAGES = generate_images
LIBUIMG = ../build/lib/libuimg.so


# ---------------------------------------------------------------------------------------------------------------------
# Library & compiler flag definitions.
# ---------------------------------------------------------------------------------------------------------------------

# AFL++ toolchain definitions.
FUZZ_CC = $(AFL_DIR)/afl-clang-fast
FUZZ_CFLAGS = -g -O0
FUZZ = $(AFL_DIR)/afl-fuzz
TMIN = $(AFL_DIR)/afl-tmin
AFL_TOOLS = $(FUZZ_CC) $(FUZZ) $(TMIN)

CRASH_FILES = $(wildcard $(CRASHES_DIR)/id*)
TARGET_BIN = $(BUILD_DIR)/$(TARGET)
GENERATE_IMAGES_BIN = $(BUILD_DIR)/$(GENERATE_IMAGES)
SRC_FILES = $(wildcard $(SOURCE_DIR)/*.c)
OBJ_FILES = $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(patsubst %.c,%.o,$(SRC_FILES)))


# ---------------------------------------------------------------------------------------------------------------------
# Makefile high-level targets (to be used directly by the user).
# ---------------------------------------------------------------------------------------------------------------------

# By default, generate random input files and start fuzzing.
all: inputs fuzz

# Run AFL++ on the entry point binary.
fuzz: $(LIBUIMG) $(TARGET_BIN) $(AFL_TOOLS)
	@rm -rf $(OUT_FUZZ_DIR)
	@mkdir $(OUT_FUZZ_DIR)
	$(FUZZ) -i $(IN_FUZZ_DIR)/ -o $(OUT_FUZZ_DIR)/ -- ./$(TARGET_BIN) @@

# Minify the crashes (should be run after running `make fuzz`).
tmin: $(TARGET_BIN) $(CRASHES_DIR)
	@for crash_file in $(CRASH_FILES) ; do \
		$(TMIN) -i $$crash_file -o $$crash_file\_min -- ./$(TARGET_BIN) ; \
	done

# Generate input files for AFL++ to use.
inputs: $(GENERATE_IMAGES_BIN)
	@rm -rf $(IN_FUZZ_DIR)
	@mkdir $(IN_FUZZ_DIR)
	./$<


# ---------------------------------------------------------------------------------------------------------------------
# Low-level build rules.
# ---------------------------------------------------------------------------------------------------------------------

# Build `libuimg.so`.
$(LIBUIMG): $(AFL_TOOLS)
	make -C ../ linux DEBUG=0 HOST_CC=fuzz/$(FUZZ_CC)

# Build the AFL++ toolchain.
$(AFL_TOOLS):
	make -C $(AFL_DIR) distrib

$(GENERATE_IMAGES_BIN): $(BUILD_DIR)/$(GENERATE_IMAGES).o $(LIBUIMG)
	$(FUZZ_CC) -o $@ $< -L../build/lib -Wl,-rpath=../build/lib/ -luimg

$(TARGET_BIN): $(BUILD_DIR)/$(TARGET).o $(LIBUIMG)
	$(FUZZ_CC) -o $@ $< -L../build/lib -Wl,-rpath=../build/lib/ -luimg

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(BUILD_DIR)
	$(FUZZ_CC) $(FUZZ_CFLAGS) -c $< -o $@ -I../inc/


# ---------------------------------------------------------------------------------------------------------------------
# Build & cleanup rules
# ---------------------------------------------------------------------------------------------------------------------

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)/
	make -C ../ clean

clean-afl:
	make -C $(AFL_DIR) clean


.PHONY: fuzz inputs clean clean-afl
