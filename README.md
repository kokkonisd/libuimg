# libuimg

![CI](https://github.com/kokkonisd/libuimg/workflows/CI/badge.svg)

A fast, lightweight image manipulation library for embedded applications.


## how to install

In order to install `libuimg`, you first have to clone this repo:

```text
$ git clone --recurse-submodules https://github.com/kokkonisd/libuimg
```

Assuming you have [GNU Make](https://www.gnu.org/software/make/) and [GCC](https://gcc.gnu.org/) installed, you can
then `make` it:

```text
$ make
```

This will build the library itself as well as some additional test programs; more about that on the
[developer notes](#developer-notes).

By default, **the library corresponding to your machine will be built**. The library only supports macOS and Linux; if
you build it on a Linux machine it will create `libuimg.a` and `libuimg.so` (compiled with the `-shared` flag), and if
you build it on a macOS machine it will create `libuimg.a` and `libuimg.dylib` (compiled with the `-dynamiclib` flag).

You can get the one or the other by running `make linux` and `make macos` respectively.

Once the library is built, you can install it on your machine by running `make install`:

```text
$ PREFIX=path/to/install/dir make install
```

By default, `PREFIX` is set to `/usr/local/`.


## how to use

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

The following pixel formats are currently supported:

| Format name  | Packed or planar | Bits per pixel            | Example (4 pixels)          |
| ------------ | ---------------- | ------------------------- | --------------------------- |
| YUV444       | Packed           | 24                        | Y0U0V0 Y1U1V1 Y2U2V2 Y3U3V3 |
| YUV444p      | Planar           | 24                        | Y0Y1Y2Y3 U0U1U2U3 V0V1V2V3  |
| YUV420p      | Planar           | 16                        | Y0Y1Y2Y3 U0 V0              |
| RGB24        | Packed           | 24                        | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB565       | Packed           | 16 ([MSB] 5R 6G 5B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| RGB8         | Packed           | 8  ([MSB] 3R 3G 2B [LSB]) | R0G0B0 R1G1B1 R2G2B2 R3G3B3 |
| GRAYSCALE    | Packed           | 8                         | Y0 Y1 Y2 Y3                 |

Conversions are supported to and from any of these formats, like so:

```c
// Conversion functions look like `convert_<base_format>_to_<new_format>()`
Image_t * yuv444p_image = convert_YUV444_to_YUV444p(yuv444_image);
Image_t * grayscale_image = convert_RGB24_to_GRAYSCALE(rgb24_image);
Image_t * yuv420p_image = convert_RGB565_to_YUV420p(rgb565_image);
// ... etc
```


## developer notes

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
