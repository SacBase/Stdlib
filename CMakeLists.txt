CMAKE_MINIMUM_REQUIRED (VERSION 3.3)

PROJECT (sac-stdlib)
#FIXME(artem) we can create a definitoin for language "SAC" which will
#             automatically pull sac2c compiler.

# Where the compiled sac modules result
SET (DLL_BUILD_DIR  "${PROJECT_BINARY_DIR}/lib")

# For what targets we build modules
SET (TARGETS            seq   CACHE STRING "Build stdlib-jpeg for these targets")
SET (SAC2C_EXEC                     CACHE STRING "A path to sac2c compiler")
SET (LINKSETSIZE        "200"       CACHE STRING "Set a value for -linksetsize parameter of sac2c")
SET (SAC2C_EXTRA_INC
     -DHAVE_CONFIG_H 
     -I${PROJECT_BINARY_DIR}/include
     -I${PROJECT_SOURCE_DIR}/include)

SET (SAC2C_CPP_INC
     -DHAVE_CONFIG_H  
     -cppI${PROJECT_BINARY_DIR}/include
     -cppI${PROJECT_SOURCE_DIR}/include)
     

# Check whether sac2c is operational
INCLUDE ("cmake-common/check-sac2c.cmake")

INCLUDE ("cmake/config.cmake")

# For every target run CMakeLists.txt in src
FOREACH (TARGET IN ITEMS ${TARGETS})
    #MESSAGE ("t = ${TARGET}")
    ADD_SUBDIRECTORY (src   src-${TARGET})
ENDFOREACH ()
