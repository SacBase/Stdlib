# You can choose to build less or more of the compiler to decrease compilation
# time.
OPTION (FULLTYPES    "Compile for all supported types."                     ON)
OPTION (BUILD_EXT    "Build extended standard library."                     ON)
OPTION (BUILDGENERIC "Do not use -march=native -mtune=native"               OFF)
