# libuimg

![CI](https://github.com/kokkonisd/libuimg/workflows/CI/badge.svg)

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

Libuimg currently supports conversions between any of the supported image formats.


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
Image_t * converted_to_rgb24 = convert_dynamic_image(my_yuv444_image, RGB24);
```

Which will of course allocate memory for the new `converted_to_rgb24` image.

If you prefer to manage the memory yourself statically, you can use:

```c
uint8_t result = convert_image(my_yuv444_image, converted_to_rgb24);
```

This is of course assuming that you have already allocated some space for the new image and that its `data` pointer is
pointing to it.

---


## Benchmarks

Here are some benchmarks of libuimg, running on an **STM32L452RE** MCU with a clock frequency of **80 MHz** while
performing operations on a **QQVGA (160x120)** image.

### Conversions

#### YUV444 to * conversions

| Operation                   | Time       |
| --------------------------- | ---------- |
| Create YUV444 image         | 5.053 ms   |
| Convert YUV444 to YUV444p   | 12.496 ms  |
| Convert YUV444 to YUV420p   | 9.755 ms   |
| Convert YUV444 to RGB24     | 20.180 ms  |
| Convert YUV444 to RGB565    | 23.301 ms  |
| Convert YUV444 to RGB8      | 17.538 ms  |
| Convert YUV444 to GRAYSCALE | 4.570 ms   |


#### YUV444p to * conversions

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Create YUV444p image         | 5.051 ms   |
| Convert YUV444p to YUV444    | 12.014 ms  |
| Convert YUV444p to YUV420p   | 9.515 ms   |
| Convert YUV444p to RGB24     | 22.821 ms  |
| Convert YUV444p to RGB565    | 24.501 ms  |
| Convert YUV444p to RGB8      | 19.940 ms  |
| Convert YUV444p to GRAYSCALE | 3.850 ms   |


#### YUV420p to * conversions

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Create YUV420p image         | 2.530 ms   |
| Convert YUV420p to YUV444    | 12.275 ms  |
| Convert YUV420p to YUV444p   | 13.004 ms  |
| Convert YUV420p to RGB24     | 18.778 ms  |
| Convert YUV420p to RGB565    | 25.263 ms  |
| Convert YUV420p to RGB8      | 21.656 ms  |
| Convert YUV420p to GRAYSCALE | 3.851 ms   |


#### RGB24 to * conversions

| Operation                  | Time       |
| -------------------------- | ---------- |
| Create RGB24 image         | 5.050 ms   |
| Convert RGB24 to YUV444    | 16.337 ms  |
| Convert RGB24 to YUV444p   | 17.057 ms  |
| Convert RGB24 to YUV420p   | 15.777 ms  |
| Convert RGB24 to RGB565    | 24.740 ms  |
| Convert RGB24 to RGB8      | 24.260 ms  |
| Convert RGB24 to GRAYSCALE | 7.212 ms   |


#### RGB565 to * conversions

| Operation                   | Time       |
| --------------------------- | ---------- |
| Create RGB565 image         | 3.369 ms   |
| Convert RGB565 to YUV444    | 16.818 ms  |
| Convert RGB565 to YUV444p   | 17.778 ms  |
| Convert RGB565 to YUV420p   | 16.498 ms  |
| Convert RGB565 to RGB24     | 11.534 ms  |
| Convert RGB565 to RGB8      | 14.176 ms  |
| Convert RGB565 to GRAYSCALE | 7.932 ms   |


#### RGB8 to * conversions

| Operation                 | Time       |
| ------------------------- | ---------- |
| Create RGB8 image         | 1.688 ms   |
| Convert RGB8 to YUV444    | 16.097 ms  |
| Convert RGB8 to YUV444p   | 17.057 ms  |
| Convert RGB8 to YUV420p   | 15.532 ms  |
| Convert RGB8 to RGB24     | 10.574 ms  |
| Convert RGB8 to RGB565    | 8.653 ms   |
| Convert RGB8 to GRAYSCALE | 6.732 ms   |


#### GRAYSCALE to * conversions
_Note: obviously, grayscale to * conversions will not be able to bring back color data that was never there. However,
they can be practical when interfacing with specific peripherals, for example displays that only accept RGB565 images._

| Operation                    | Time       |
| ---------------------------- | ---------- |
| Create GRAYSCALE image       | 1.689 ms   |
| Convert GRAYSCALE to YUV444  | 9.853 ms   |
| Convert GRAYSCALE to YUV444p | 9.853 ms   |
| Convert GRAYSCALE to YUV420p | 4.813 ms   |
| Convert GRAYSCALE to RGB24   | 14.415 ms  |
| Convert GRAYSCALE to RGB565  | 27.861 ms  |
| Convert GRAYSCALE to RGB8    | 26.180 ms  |


---


## Developer notes

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
- Implement basic operations (scaling, rotating)
- Implement PNG/JPEG decoding
