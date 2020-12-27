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
