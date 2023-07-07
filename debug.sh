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

# Create the command to run the preprocessor storing the output in source_files
sed -i -E 's/\/tmp\/[^/]*\/([^.]*\.i)/\.\/source_files\/\1/g' "$1"

# Run the preprocessor command
grep "\-E" "$1" | sh

# Format the .i files
format_in_place()
{
    temp=$(mktemp)

    grep -v "#" "$1" | nuke_semi | clang-format > "$temp"
    mv "$temp" "$1"
}

for file in ./source_files/*
do
    format_in_place "$file"
done

# Delete the preprocessing commands from the .sac2c-file
sed -i '/-E/d' "$1"

# Create the command to make sure gdb uses the .i file and not .c
sed -i 's/\/usr\/bin\/cc/\/usr\/bin\/cc\ -no-integrated-cpp -P/g' "$1"

# Compile the objects files
grep "\-c" "$1" | sh

# Delete those commands from the .sac2c-file
sed -i '/-c\ /d' "$1"

# Run the remaining commands (making directories and linking)
sh < "$1"
