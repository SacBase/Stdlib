SaC standard library
====================

[![build status](https://github.com/SacBase/Stdlib/workflows/Build%20On%20Changes/badge.svg)](https://github.com/SacBase/Stdlib/actions?query=workflow%3A"Build+On+Changes") [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](https://github.com/SacBase/Stdlib/issues)

This repository consists of SaC modules with basic functionality like
arithmetic, stdio, etc; which together form the standard library of the SaC
language.

Build instructions
==================

To build the system one requires an operational [CMake](https://cmake.org/) >= 3.20,
[Flex](http://flex.sourceforge.net/), and [Bison](https://www.gnu.org/software/bison/).

The quick and dirty option is just

```
make
```

You can also use the `cmake` build system for more control

```
mkdir build
cd build
cmake <OPTIONS> ..
make -j4
```

**NOTE:** *When pulling the latest commit, remember to run `git submodule
update` or you will be missing changes to the `cmake-common` repository.*

Variables that can be passed to CMake
=========================================

When running CMake it is possible to pass the following variables:

* `-DTARGETS=x;y;z` --- build stdlib for targets x, y and z. (Defaults to `seq;mt_pth`)
* `-DBUILDGENERIC=ON|OFF` --- build stdlib without using architecture specific optimisations
   (useful when creating distributable packages). (Default is `OFF`)
* `-DSAC2C_EXEC=/path/to/sac2c` --- specify `sac2c` executable directly. Otherwise CMake will
  try to find `sac2c` on yout PATH.
* `-DLINKSETSIZE=n` --- set `-linksetsize n` when calling `sac2c`.  This option is responsible
  for the number of C functions that are put in a single C file when compiling a SaC program.
  The rule of thumb:
  * value `0` is the fastest time-wise but potentially results in a large memory consumption
  * value `1` reduces the memory consumption to minimum, but significantly increases compilation time.
  
    *Default value: 500.*
* `-DFULLTYPES=ON|OFF` --- add support for further types to the stdlib, such as `long` and
  `longlong` (Default is `ON`).
* `-DBUILD_EXT=ON|OFF` --- build extended stdlib (see
  `cmake/source-core-ext.txt` for details) (Default is `ON`)

Continuous Integration
=====================

We make use of Github Actions for our CI pipeline, building the standard library on different systems
anytime there is a pull request. Build will fail if there are any compile-time warnings.

Please look at `.github/workflows/` for more exact details on what we do.

Licensing
=========

This project is OSS, please have a look at [LICENSE.md][license] for more details. Contributions
are welcome!

[license]: https://github.com/SacBase/Stdlib/blob/master/LICENSE.md
