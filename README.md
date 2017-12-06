SaC standard library
====================

This repository consists of SaC modules with basic functionality like
arithmetic, stdio, etc; which together form a standard library of SaC
language.

Build instructions
==================

To build the system one requires an operational [CMake](https://cmake.org/) >= 3.3,
[Flex](http://flex.sourceforge.net/), and [Bison](https://www.gnu.org/software/bison/).

An example on how to build the library:
```bash
$ cd Stdlib
$ git submodule init
$ git submodule update
$ mkdir build
$ cd build
$ cmake ..
$ make -j4  #you should have roughly 2GB per thread :-)
```

If you like you can also install the stdlib into `/usr/local` with `make
install`, but this is unnessicary as `sac2c` will be able to find your stdlib
build automatically.

**NOTE:** *When pulling the latest commit, remember to run `git submodule
update` or you will be missing changes to the `cmake-common` repository.*

Variables that can be passed to CMake
=========================================

When running CMake it is possible to pass the following variables:
  * `-DTARGETS=x;y;z` --- build stdlib for targets x, y and z. (defaults are `seq; mt_pth`)
  * `-DSAC2C_EXEC=/path/to/sac2c` --- specify `sac2c` executable directly. Otherwise CMake will
    try to find `sac2c` on yout PATH.
  * `-DLINKSETSIZE=n` --- set `-linksetsize n` when calling `sac2c`.  This option is responsible
    for the number of C functions that are put in a single C file when compiling a SaC program.
    The rule of thumb:
    * value `0` is the fastest time-wise but potentially results in a large memory consumption
    * value `1` reduces the memory consumption to minimum, but significantly increases compilation time.
    
      *Default value: 500.*
  * `-DFULLTYPES=ON|OFF` --- add support for further types to the stdlib, such as `long` and
    `longlong` (Default is `OFF`).
  * `-DBUILD_EXT=ON|OFF` --- build extended stdlib (see
    `cmake/source-core-ext.txt` for details) (Default is `ON`)
