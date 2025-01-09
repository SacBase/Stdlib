CMAKE_MINIMUM_REQUIRED (VERSION 3.20)

PROJECT (sac-stdlib)
#FIXME(artem) we can create a definitoin for language "SAC" which will
#             automatically pull sac2c compiler.

# Where the compiled sac modules result
SET (DLL_BUILD_DIR  "${PROJECT_BINARY_DIR}/lib")

# For what targets we build modules
SET (TARGETS            seq seq_checks mt_pth mt_pth_checks CACHE STRING "Build stdlib for these targets")
SET (SAC2C_EXEC                     CACHE STRING "A path to sac2c compiler")
SET (LINKSETSIZE        "500"       CACHE STRING "Set a value for -linksetsize parameter of sac2c")
SET (IS_RELEASE         FALSE       CACHE BOOL "Indicate if we are building with release version of SAC2C")
OPTION (FULLTYPES "Include types such as long and longlong" OFF)
OPTION (BUILD_EXT "Build complete Stdlib with extra modules" ON)
OPTION (BUILDGENERIC "Do not use architecture specific optimisations (useful for package builds)" OFF)

SET (SAC2C_EXTRA_INC
     -DHAVE_CONFIG_H
     -I${PROJECT_BINARY_DIR}/include
     -I${PROJECT_SOURCE_DIR}/include)

SET (SAC2C_CPP_INC
     -DHAVE_CONFIG_H
     -cppI${PROJECT_BINARY_DIR}/include
     -cppI${PROJECT_SOURCE_DIR}/include)

IF (FULLTYPES)
    LIST (APPEND SAC2C_EXTRA_INC -DFULLTYPES)
    LIST (APPEND SAC2C_CPP_INC -DFULLTYPES)
ENDIF ()

IF (BUILD_EXT)
    LIST (APPEND SAC2C_EXTRA_INC -DEXT_STDLIB)
    LIST (APPEND SAC2C_CPP_INC -DEXT_STDLIB)
ENDIF ()

# Check whether sac2c is operational
INCLUDE ("cmake-common/check-sac2c.cmake") # get SAC2C_VERSION
INCLUDE ("cmake-common/misc-macros.cmake")
INCLUDE ("cmake-common/check-sac2c-feature-support.cmake")
INCLUDE ("cmake-common/generate-version-vars.cmake")

# if building generically, we need to make sure sac2c supports this
IF (BUILDGENERIC)
    CHECK_SAC2C_SUPPORT_FLAG ("generic" "-generic" "")
    IF (HAVE_FLAG_generic)
        LIST (APPEND SAC2C_CPP_INC "-generic")
    ELSE ()
        MESSAGE (STATUS "Generic-build disabled as sac2c does not support this!")
        SET (BUILDGENERIC OFF)
    ENDIF ()
ENDIF ()

# complete configuration now
INCLUDE ("cmake/config.cmake")

# For every target run CMakeLists.txt in src
SET (TARGET_COUNT 1)
FOREACH (TARGET IN ITEMS ${TARGETS})
    #MESSAGE ("target #${TARGET_COUNT} = ${TARGET}")
    ADD_SUBDIRECTORY (src   src-${TARGET})
    MATH (EXPR TARGET_COUNT "${TARGET_COUNT} + 1")
ENDFOREACH ()

# This build target is responsible for generating the package sac2crc file
CREATE_SAC2CRC_TARGET ("stdlib" "${DLL_BUILD_DIR}" "${DLL_BUILD_DIR}" "")

# lets create packages
SET (PROJECT_SHORT_VERSION)
SET (PROJECT_MAJOR_VERSION)
SET (PROJECT_MINOR_VERSION)
SET (PROJECT_PATCH_VERSION)
GET_PROJECT_VERSION (PROJECT_SHORT_VERSION PROJECT_MAJOR_VERSION PROJECT_MINOR_VERSION PROJECT_PATCH_VERSION)
INCLUDE ("${PROJECT_SOURCE_DIR}/cmake/cpack.cmake")
