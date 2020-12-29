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


Libuimg currently supports the following image formats:

| Format name  | Packed or planar | Bits per pixel            | Example (4 pixels)          |
| ------------ | ---------------- | ------------------------- | --------------------------- |
| YUV444       | Packed           | 24                        | Y0U0V0 Y1U1V1 Y2U2V2 Y3U3V3 |
| YUV444p      | Planar           | 24                        | Y0Y1Y2Y3 U0U1U2U3 V0V1V2V3  |
| YUV420p      | Planar           | 16                        | Y0Y1Y2Y3 U0 V0              |
| RGB24        | Packed           | 24                        | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB565       | Packed           | 16 ([MSB] 5R 6G 5B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB8         | Packed           | 8  ([MSB] 3R 3G 2B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| GRAYSCALE    | Packed           | 8                         | Y0 Y1 Y2 Y3                 |

Libuimg currently supports conversions between any of the supported image formats.


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

## How to use libuimg

In order to get access to every element of `libuimg`'s API, all you need to do is include its main header file:

```c
#include "libuimg.h"
```

The basic building block of the API is the `Image_t` structure; for example, in order to create a simple RGB24 image
of dimensions 200x200 (pixels) all you need to do is:

```c
Image_t * my_image = create_image(200, 200, RGB24);

// ... do stuff with image here ...

destroy_image(my_image);
```

Conversions are supported to and from any of the currently supported image formats, like so:

```c
// Conversion functions look like `convert_<base_format>_to_<new_format>()`
Image_t * yuv444p_image = convert_YUV444_to_YUV444p(yuv444_image);
Image_t * grayscale_image = convert_RGB24_to_GRAYSCALE(rgb24_image);
Image_t * yuv420p_image = convert_RGB565_to_YUV420p(rgb565_image);
// ... etc
```


## Benchmarks

TODO


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
