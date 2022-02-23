#!/usr/bin/env bash

# the scipts reads from stdin/file the output of a build process (such as
# through CMake/Autotools) and looks for text indicate that warning has
# been issued. If it finds an instances of this, we return non-zero value.
# Exceptions can be set, meaning that we don't consider all warnings as
# a reason to return a non-zero value.

# array join, supports delimiter. Usage: join_by ',' ${array}
function join_by { local d=$1; shift; echo -n "$1"; shift; printf "%s" "${@/#/$d}"; }

# support stdin
FILE="${1:-/dev/stdin}"

# construct exclude array
EXCLUDES=('was built for newer macOS version')
TEXCLUDES="$(join_by '|' "${EXCLUDES[@]}")"

# general search
WARN_NUM=$(grep -i -F 'warning:' "$FILE" | grep -i -c -v -E "${TEXCLUDES}")
if [ "${WARN_NUM}" -gt 0 ]; then
  echo "+++ ${WARN_NUM} warnings detected +++";
  exit 1
fi
