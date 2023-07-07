#!/bin/sh

# This is a helper script to rebuild parts of Stdlib such that errors in there
# are easier to fix. Using gdb you will likely be able to find the module to
# problem occurs in. Build the library with environment variable VERBOSE=1
# and copy the command compiling the relevant module. Then add -dcccall to the
# compile command. This will create a .sac2c file in that directory. Call this
# script with that sac2c file as argument in that directory.
# This assumes the nuke_semi tool from sac2c utils is in your path, and
# clang-format is installed.

# We store our source files preinstead of in /tmp
mkdir -p source_files

# Copy the .c files from tmp to source_files
grep -E -oh "/tmp/[^/]*/[^.]*\.c" "$1" | xargs cp -t ./source_files

# Run the preprocessor, storing the output in source_files
sed -i -E "s/\/tmp\/[^/]*\/([^.]*\.i)/\.\/source_files\/\1/g" "$1"

# Make sure gdb uses the .i file and not .c
sed -i 's/\/usr\/bin\/cc/\/usr\/bin\/cc\ -no-integrated-cpp -P/g' "$1"
