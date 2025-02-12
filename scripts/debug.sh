#!/bin/sh

if [ "$#" -ne 1 ]; then
    printf "Usage: debug.sh SAC2C_FILE\n" >&2
    printf "\tSAC2C_FILE: .sac2c file created by sac2c option -dcccall\n\n" >&2
    printf "\tThis is for debugging parts of stdlib using gdb.\n" >&2
    printf "\tBuild stdlib with VERBOSE=1 in the environment, and copy\n" >&2
    printf "\tthe command compiling the relevant module.\n" >&2
    printf "\tThen add -dcccall to the compile command.\n" >&2
    printf "\tThis will create a sac2c file in that directory, which you.\n" >&2
    printf "\tpass as argument to this script.\n" >&2
    printf "\tgdb will then give line numbers for readable generated code.\n" >&2
    exit
fi

hash clang-format || exit

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

    grep -v "#" "$1" | clang-format > "$temp"
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
