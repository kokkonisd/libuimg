# How to contribute to libuimg

Libuimg is, of course, an open-source project, and everybody is invited to contribute. Before doing so, however, you
should read this document, to make sure you are aligned with the project's goals.


## High-level goals

Here are some key high-level goals to keep in mind when developing libuimg:

- **Embedded is king.** We optimize first and foremost for embedded targets. In fact the priority is: bare-metal ARM >
  Linux ARM > macOS/Linux x86.
- **Master is always building.** The master branch should always _at least_ build and pass all tests and memory checks.
  All of the development is done in the `dev` branch, which is merged into `master` once it is deemed stable.
- **Coverage should be ~100%.** We aim for 100% coverage; of course there are exceptions (such as safeguards for corner
  cases that are not easily reproducible) but we should always take care to cover as much as we can through tests.
- **Minimalism FTW.** Libuimg isn't meant to be some huge conglomeration of every image manipulation function known to
  mankind; at the end of the day, it's supposed to be a small C library to be used in embedded application, where
  footprint matters.


## Ask first

Before forking the repo and hacking away, **create an issue**. Working on something before notifying the other project
maintainers is rude; also, issues help us keep track of who does what, so as to not end up with duplicate work.


## Getting started

Before you even start writing anything, you should fork this repo. The dev dependencies you should install are the
following:

- [GNU Make](https://www.gnu.org/software/make/)
- [The GCC toolchain](https://gcc.gnu.org/)
- The ARM cross-compiler toolchain for
  [Linux](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)
  and
  [bare-metal](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  targets
- gcov, for code coverage
- [Valgrind](https://www.valgrind.org/) on Linux or [macgrind](https://pypi.org/project/macgrind/) on macOS, for memory
  checks

I am developing this library on a x86 macOS 10.14.6 machine and a x86 Ubuntu 20.04 machine, so I can confirm that they
both work development-wise (and use-wise). CI runs on both a macOS and an Ubuntu machine as well. Native Windows is not
supported and I highly doubt it will ever be (there are plenty of ways to get a Linux terminal and install the 
dependencies of this project in Windows either way).


## Sanity check

Libuimg's `master` branch should work on your machine; if not, you have configured something incorrectly. Right after
forking the repo and _before_ modifying anything, run a simple sanity check: tests and memory checks should build fine.

```text
$ make clean all tests memchecks
```


## Development

You should **always** develop on the `dev` branch. Any commits applied directly on `master` will simply not be
accepted. The correct workflow is: `PR you/libuimg:dev -> kokkonisd/libuimg:dev`.

_Of course_, you should always run tests and memchecks before opening a PR; nothing breaking CI will pass a PR.

As mentioned in the goals at the start of this document, _we aim for 100% coverage_; when you add some code, you also
need to add tests to cover it.

Files should be prefixed by `libuimg_` for source files and `test_` for test files.

In terms of targets, an STM32 MCU is considered a typical bare-metal ARM target, and a Raspberry Pi is considered a
typical Linux ARM target.


## Memory management

Dynamic memory allocations **should not exist anywhere outside of `libuimg_img.c`.** If the user wishes to dynamically
allocate memory, they should do it through the `create_image` function, and then pass the image pointer to the other
functions of libuimg. The user should **always** be able to choose to work with static memory only.


## Code style

Lines shouldn't be longer than 120 columns (including the newline character, so set your editor's limit to 119).

Functions are written with their brackets on a new line, like this:

```c
void myfunc (void)
{
    // Code goes here
}
```

This is not the case for loops or if-statements:

```c
if (1 == 1) {
    while (2 < 3) {
        // Do stuff
    }
}
```

As you noticed, in both examples there are spaces pretty much everywhere; don't do neither of `if(1==1)` or
`if ( 1 == 1 )`. No need to over/under-do it.

Variable declarations always happen at the beginning of the function, and never in the body. Also, the variables are
**always** initialized to something:

```c
void myfunc (void)
{
    uint8_t var1 = 0;
    uint16_t var2 = 1;
    int32_t var3 = -10;
    char * c = NULL;
}
```

Specific int sizes should be used; `int` should not exist in the source code, though you can use it in the tests
because it doesn't matter. We are targeting embedded platforms and type sizes need to be specific.

In general, try to imitate the style of the existing code.
