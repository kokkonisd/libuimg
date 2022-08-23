# libuimg

![CI](https://github.com/kokkonisd/libuimg/workflows/CI/badge.svg)
![codecov](https://codecov.io/gh/kokkonisd/libuimg/branch/main/graph/badge.svg?token=I48WB1ZR1E)

A fast, lightweight image manipulation library for embedded applications.


## Contents

 - [Features](#features)
 - [How to install libuimg](#how-to-install-libuimg)
    - [Installation for Linux/macOS x86 targets](#installation-for-x86-targets)
    - [Installation for Linux ARM targets](#installation-for-linux-arm-targets)
        - [Compiling on the target machine](#compiling-on-the-target-machine)
        - [Cross-compiling on a host machine](#cross-compiling-on-a-host-machine)
    - [Installation for bare-metal ARM targets](#installation-for-bare-metal-arm-targets)
 - [How to use libuimg](#how-to-use-libuimg)
 - [Benchmarks](#benchmarks)
    - [Conversions](#conversions)
    - [Flips](#flips)
 - [Developer notes](#developer-notes)


---


## Features

Libuimg is an image manipulation library. Its goal is to be lightweight and fast, in order to be usable in embedded
systems, with or without an underlying OS.

Libuimg is currently supported on the following platforms:

| Platform                     | Has it been tested? |
| ---------------------------- | ------------------- |
| x86 Linux (Ubuntu 20.04)     | Yes                 |
| x86 macOS (Mojave 10.14.16)  | Yes                 |
| ARM Linux (Raspberry Pi 3B+) | No                  |
| ARM bare-metal (STM32F103RB) | Yes                 |
| ARM bare-metal (STM32L452RE) | Yes                 |


Libuimg currently supports the following image formats:

| Format name  | Packed or planar | Bits per pixel            | Example (4 pixels)          |
| ------------ | ---------------- | ------------------------- | --------------------------- |
| YUV444       | Packed           | 24                        | Y0U0V0 Y1U1V1 Y2U2V2 Y3U3V3 |
| YUV444p      | Planar           | 24                        | Y0Y1Y2Y3 U0U1U2U3 V0V1V2V3  |
| YUV420p      | Planar           | 12                        | Y0Y1Y2Y3 U0 V0              |
| RGB24        | Packed           | 24                        | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB565       | Packed           | 16 ([MSB] 5R 6G 5B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB8         | Packed           | 8  ([MSB] 3R 3G 2B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| GRAYSCALE    | Packed           | 8                         | Y0 Y1 Y2 Y3                 |
| ASCII        | Packed           | 8                         | A0 A1 A2 A3                 |

The ASCII format can be used for debugging; it transforms an image to ASCII characters with 12 different levels of
brightness. This format can be very useful when working with images on embedded targets with no OS or display, where
usually the only debugging interface is UART. The user can convert an image to ASCII and dump it via UART to quickly
evaluate it (as opposed to dumping the raw data and then converting it to a PNG/JPEG image on the host machine).

Libuimg currently supports:

- Conversions between any of the supported image formats, _except `ASCII_to_*`_
- Flipping an image along the X or Y axis (for all the supported formats)


---


## How to install libuimg

No matter the target of your choice, you must start by cloning this repo:

```text
$ git clone --recurse-submodules https://github.com/kokkonisd/libuimg
```

### Installation for x86 targets

The installation of the library for x86 targets is the easiest one. Here are the dependencies you'll need:

- [GNU Make](https://www.gnu.org/software/make/)
- [The GCC toolchain](https://gcc.gnu.org/) (you specifically need `gcc`, `ar` and `ranlib`)

In order to build the static version of the library (`libuimg.a`), you can simply run:

```text
$ make
```

This will produce `build/lib/libuimg.a`.

In order to build the dynamic version of the library, you will need to run different commands based on your OS. For
example, for a x86 machine running Linux, you should run:

```text
$ make linux
```

This will produce `build/lib/libuimg.so`.

For a x86 machine running macOS, you should run:

```text
$ make macos
```

This will produce `build/lib/libuimg.dylib`.

Once you have built the library of your choice, you can install it on your machine by running:

```text
$ make install
```

The installation directory is set by the `PREFIX` environment variable; the header files will be installed under the
`include/` subdirectory and the library files will be installed under the `lib/` subdirectory in the install directory.

If you wish to install the files in a different directory, you can run:

```text
$ make PREFIX=/path/to/install/dir install
```

### Installation for Linux ARM targets

_[Note: this library has not yet been tested on an ARM platform running Linux; this build process is under development
and has not been proved to work.]_

#### Compiling on the target machine

If you are compiling this library on the target itself (like a Raspberry Pi), you will need the following dependencies:

- [GNU Make](https://www.gnu.org/software/make/)
- [The GCC toolchain](https://gcc.gnu.org/) **for ARM-Linux** (you specifically need `gcc`, `ar` and `ranlib`)

If the `gcc` toolchain is in your `PATH`, you can simply build both the static (`libuimg.a`) and the dynamic
(`libuimg.so`) version of the library by running:

```text
$ make CROSS_PREFIX="" arm
```

This will simply use `gcc`, `ar` and `ranlib` without any prefix (by default the cross-compiler prefix is set to
`arm-linux-gnueabihf-`).

You can then install the library on your machine by running:

```text
$ make install
```

The installation directory is set by the `PREFIX` environment variable; the header files will be installed under the
`include/` subdirectory and the library files will be installed under the `lib/` subdirectory in the install directory.

If you wish to install the files in a different directory, you can run:

```text
$ make PREFIX=/path/to/install/dir install
```


#### Cross-compiling on a host machine

If you are compiling this library on a x86 "host" machine running Linux for the target itself (like a Raspberry Pi),
you will need the following dependencies:

- [GNU Make](https://www.gnu.org/software/make/)
- [The ARM cross-compiler toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)
  **for ARM-Linux** (you specifically need `gcc`, `ar` and `ranlib`)

If you are cross-compiling on a Linux host, you will need either `crossbuild-essential-armhf` for 32-bit ARM targets
or `crossbuild-essential-arm64` for 64-bit ARM targets. Both can be installed through `apt`.

You can build build both the static (`libuimg.a`) and the dynamic (`libuimg.so`) version of the library for the ARM
target by running:

```text
$ make arm
```

The cross-compiler prefix is set to `arm-linux-gnueabihf-` by default (32-bit targets). If you are building for a
64-bit target, you will need to run:

```text
$ make CROSS_PREFIX=aarch64-linux-gnu- arm
```

You can then find the built libraries in `build/lib/` and copy them on the target machine.


### Installation for bare-metal ARM targets

If you are compiling this library on a x86 "host" machine running Linux or macOS for the target itself (like an STM32
MCU), you will need the following dependencies:

- [GNU Make](https://www.gnu.org/software/make/)
- [The ARM cross-compiler toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  **for bare-metal ARM**

You can install the ARM bare-metal toolchain by running `brew install gcc-arm-embedded` on macOS or `apt-get install
gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi` on Linux.

You can then build both the static (`libuimg.a`) and the dynamic (`libuimg.so`) version of the library for the
bare-metal ARM target by running:

```text
$ make CROSS_BM_CPU=<target CPU architecture> arm-bm
```

For example, for a Cortex-M3-based MCU it would be:

```text
$ make CROSS_BM_CPU=cortex-m3 arm-bm
```

The cross-compiler prefix is set to `arm-none-eabi-` by default. If you wish to change it, you can run:

```text
$ make CROSS_PREFIX=<custom prefix> CROSS_BM_CPU=<target CPU architecture>
```

You can also specify other compilation flags (for example concerning hardware/software float implementations) via
`CROSS_BM_CFLAGS`:

```text
$ make CROSS_PREFIX=<custom prefix> CROSS_BM_CPU=<target CPU architecture> CROSS_BM_CFLAGS=<custom compiler flags>
```

You can then find the static bare-metal library in `build/lib/` and use it on the bare-metal target.

**Important note:** since libuimg uses calls to `malloc`/`free` you need to compile your final MCU code with the
following linker flags:

```text
-specs=nosys.specs -specs=nano.specs -lg -lc -lm -lnosys
```

---


## How to use libuimg

In order to get access to every element of `libuimg`'s API, all you need to do is include its main header file:

```c
#include "libuimg.h"
```

The basic building block of the API is the `Image_t` structure. It contains the image's width and height (in `uint16_t`
format) as well as the pixel format of the image, and a pointer to the raw data of the image.

The high-level API allows for both static and dynamic handling of images in terms of how the memory is handled; for
instance, in bare-metal applications often using something like `malloc` is discouraged, so the user can simply
statically allocate an image buffer and create the `Image_t` structure "by hand".

```c
// Dynamic allocation example
Image_t * dynamically_allocated_image = create_image(200, 200, RGB24);
// ... do stuff with image here ...
destroy_image(dynamically_allocated_image);

// Static allocation example
// RGB24 is 24bpp, or 3 bytes-per-pixel, so we need to allocate `width * height * 3` bytes
uint8_t img_buf[200 * 200 * 3];
Image_t statically_allocated_image = { .width = 200, .height = 200, .format = RGB24, .data = &img_buf };
// ... do stuff with image ...
```

Conversions are supported to and from any of the currently supported image formats.

For dynamically allocated images, you can use:

```c
Image_t * my_yuv444_image = create_image(200, 200, YUV444);
// ... fill in image ...
Image_t * converted_to_rgb24 = create_image(200, 200, RGB24);
uint8_t result = convert_image(my_yuv444_image, converted_to_rgb24);
if (!result) printf("Error during conversion\n");
```

Which will of course allocate memory for the new `converted_to_rgb24` image.

If you prefer to manage the memory yourself statically, you can use:

```c
// Create static buffers for both images
static uint8_t yuv444_buf[200 * 200 * 3];
static uint8_t rgb24_buf[200 * 200 * 3];

// Create both image structures
Image_t my_yuv444_image = { .width = 200, .height = 200, .format = YUV444, .data = &yuv444_buf };
Image_t converted_to_rgb24 = { .width = 200, .height = 200, .format = RGB24, .data = &rgb24_buf };

// Convert one format to the other
uint8_t result = convert_image(my_yuv444_image, converted_to_rgb24);
if (!result) printf("Error during conversion\n");
```

Flipping an image along the X or Y axis is simply a question of calling the appropriate function:

```c
// Assume we have an image called `my_img`, of any format

// Flipping along X axis (top to bottom)
uint8_t result_x = flipX_image(my_img);
// Flipping along Y axis (left to right)
uint8_t result_y = flipY_image(my_img);
```

---


## Benchmarks

Here are some benchmarks of libuimg, running on an **STM32L452RE** MCU with a clock frequency of **80 MHz** while
performing operations on a **QQVGA (160x120)** image.

### Conversions

All conversions have been performed _statically_, meaning that the image buffers are static and were pre-allocated by
the firmware, not libuimg.

#### YUV444 to * conversions

| Operation                   | Time       |
| --------------------------- | ---------- |
| Convert YUV444 to YUV444p   | 7.925 ms   |
| Convert YUV444 to YUV420p   | 7.227 ms   |
| Convert YUV444 to RGB24     | 15.849 ms  |
| Convert YUV444 to RGB565    | 20.412 ms  |
| Convert YUV444 to RGB8      | 15.609 ms  |
| Convert YUV444 to GRAYSCALE | 3.123 ms   |


#### YUV444p to * conversions

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Convert YUV444p to YUV444    | 7.445 ms   |
| Convert YUV444p to YUV420p   | 6.988 ms   |
| Convert YUV444p to RGB24     | 18.010 ms  |
| Convert YUV444p to RGB565    | 21.371 ms  |
| Convert YUV444p to RGB8      | 18.970 ms  |
| Convert YUV444p to GRAYSCALE | 1.443 ms   |


#### YUV420p to * conversions

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Convert YUV420p to YUV444    | 7.705 ms   |
| Convert YUV420p to YUV444p   | 8.198 ms   |
| Convert YUV420p to RGB24     | 13.965 ms  |
| Convert YUV420p to RGB565    | 22.133 ms  |
| Convert YUV420p to RGB8      | 19.488 ms  |
| Convert YUV420p to GRAYSCALE | 1.443 ms   |


#### RGB24 to * conversions

| Operation                  | Time       |
| -------------------------- | ---------- |
| Convert RGB24 to YUV444    | 11.287 ms  |
| Convert RGB24 to YUV444p   | 11.768 ms  |
| Convert RGB24 to YUV420p   | 13.248 ms  |
| Convert RGB24 to RGB565    | 21.850 ms  |
| Convert RGB24 to RGB8      | 20.889 ms  |
| Convert RGB24 to GRAYSCALE | 5.525 ms   |


#### RGB565 to * conversions

| Operation                   | Time       |
| --------------------------- | ---------- |
| Convert RGB565 to YUV444    | 11.767 ms  |
| Convert RGB565 to YUV444p   | 12.728 ms  |
| Convert RGB565 to YUV420p   | 13.968 ms  |
| Convert RGB565 to RGB24     | 6.485 ms   |
| Convert RGB565 to RGB8      | 12.488 ms  |
| Convert RGB565 to GRAYSCALE | 6.484 ms   |


#### RGB8 to * conversions

| Operation                 | Time       |
| ------------------------- | ---------- |
| Convert RGB8 to YUV444    | 11.047 ms  |
| Convert RGB8 to YUV444p   | 11.767 ms  |
| Convert RGB8 to YUV420p   | 13.003 ms  |
| Convert RGB8 to RGB24     | 5.524 ms   |
| Convert RGB8 to RGB565    | 5.525 ms   |
| Convert RGB8 to GRAYSCALE | 4.564 ms   |


#### GRAYSCALE to * conversions
_Note: obviously, grayscale to * conversions will not be able to bring back color data that was never there. However,
they can be practical when interfacing with specific peripherals, for example displays that only accept RGB565 images._

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Convert GRAYSCALE to YUV444  | 4.805 ms   |
| Convert GRAYSCALE to YUV444p | 4.805 ms   |
| Convert GRAYSCALE to YUV420p | 2.284 ms   |
| Convert GRAYSCALE to RGB24   | 9.846 ms   |
| Convert GRAYSCALE to RGB565  | 23.771 ms  |
| Convert GRAYSCALE to RGB8    | 22.329 ms  |


### Flips

#### X-axis flips

| Operation        | Time       |
| ---------------- | ---------- |
| YUV444 X flip    | 4.814 ms   |
| YUV444p X flip   | 4.819 ms   |
| YUV420p X flip   | 3.266 ms   |
| RGB24 X flip     | 4.814 ms   |
| RGB565 X flip    | 3.252 ms   |
| RGB8 X flip      | 1.808 ms   |
| GRAYSCALE X flip | 1.808 ms   |


#### Y-axis flips

| Operation        | Time       |
| ---------------- | ---------- |
| YUV444 Y flip    | 4.953 ms   |
| YUV444p Y flip   | 4.857 ms   |
| YUV420p Y flip   | 3.262 ms   |
| RGB24 Y flip     | 4.953 ms   |
| RGB565 Y flip    | 3.268 ms   |
| RGB8 Y flip      | 1.814 ms   |
| GRAYSCALE Y flip | 1.815 ms   |


---


## Developer notes

If you want to contribute, read the [contributing guide](CONTRIBUTING.md) first.

Testing is done via [cuts](https://github.com/sorjente/cuts). In order to run tests, simply run:

```text
$ make tests
```

You can also perform automatic memory checks. Be advised that you will need to have installed
[Valgrind](https://www.valgrind.org/) if you're on Linux or [macgrind](https://pypi.org/project/macgrind/) if you're on
macOS. Once that is done, you can run:

```text
$ make memchecks
```

---

Current TODO list:

- ~Implement basic image struct~ DONE
- ~Implement basic conversions~ DONE
- Implement basic operations (~flipping~, rotating, scaling)
- Implement PNG/JPEG decoding
