SaC Standard Library
====================

[![build status](https://github.com/SacBase/Stdlib/workflows/Build%20On%20Changes/badge.svg)](https://github.com/SacBase/Stdlib/actions?query=workflow%3A"Build+On+Changes")
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](https://github.com/SacBase/Stdlib/issues)

This repository consists of SaC modules with basic functionality like
arithmetic, I/O, etc; which together form the standard library of the
SaC language.

Build instructions
==================

To build the system one requires an operational
[CMake](https://cmake.org/) >= 3.20,
[Flex](http://flex.sourceforge.net/),
and [Bison](https://www.gnu.org/software/bison/).

An example on how to build the library:

```sh
cd Stdlib
git submodule init
git submodule update
cmake -B build
cmake --build build -- -j4 # You should have roughly 2GB per thread
```

If you like you can also install the StdLib into `/usr/local` with `make
install`, but this is _unnecessary_ as `sac2c` will be able to find your StdLib
build automatically.
This is achieved through a file named `sac2crc.package.stdlib` which is being
placed in `~/.sac2crc/` and which contains the path to the place where you build
your StdLib.

**NOTE:** *When pulling the latest commit, remember to run `git submodule
update` or you will be missing changes to the `cmake-common` repository.*

Variables that can be passed to CMake
=====================================

When running CMake it is possible to pass the following variables:

* `-DTARGETS=x;y;z`
  Build StdLib for targets x, y and z.
  (Default is `seq;seq_checks;mt_pth`)
* `-DBUILDGENERIC=ON|OFF`
  Build StdLib without using architecture specific optimizations.
  (Useful when creating distributable packages).
  (Default is `OFF`)
* `-DSAC2C_EXEC=/path/to/sac2c`
  Specify `sac2c` executable directly.
  Otherwise, CMake will try to find `sac2c` on your PATH.
* `-DLINKSETSIZE=n`
  Set `-linksetsize n` when calling `sac2c`. This option is responsible for the
  number of C functions that are put in a single C file when compiling a SaC
  program.
  The rule of thumb:
  * `0` is the fastest time-wise but potentially
    results in a large memory consumption
  * `1` reduces the memory consumption to minimum,
    but significantly increases compilation time. <br/>
  (Default is `500`)
* `-DFULLTYPES=ON|OFF`
  Add support for further types to the StdLib, such as `long` and `longlong`.
  (Default is `OFF`)
* `-DBUILD_EXT=ON|OFF`
  Build extended StdLib (see `cmake/source-core-ext.txt` for details).
  (Default is `ON`)

Continuous Integration
=====================

We make use of GitHub Actions for our CI pipeline, building the standard library
on different systems anytime there is a pull request. Build will fail if there
are any compile-time warnings.

Currently, we build on the following systems: `ubuntu-22.04` and `macos-13`.

Please look at `.github/workflows/` for more exact details on what we do.

Licensing
=========

This project is OSS, please have a look at [LICENSE.md][license] for more
details. Contributions are welcome!

[license]: https://github.com/SacBase/Stdlib/blob/master/LICENSE.md
