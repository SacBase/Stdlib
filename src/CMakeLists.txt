CMAKE_MINIMUM_REQUIRED (VERSION 3.3)
INCLUDE ("${CMAKE_SOURCE_DIR}/cmake-common/sac2c-variables.cmake")
INCLUDE ("${CMAKE_SOURCE_DIR}/cmake-common/resolve-sac2c-dependencies.cmake")

FLEX_TARGET (FibreScanLex
             "stdio/src/FibreIO/FibreScan.l"
             "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/lex.FibreScan.c"
             COMPILE_FLAGS -PFibreScan)


BISON_TARGET (FibreScanParser
              "stdio/src/FibreIO/FibreScan.y"
              "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.c"
              DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.h"
              COMPILE_FLAGS "--defines -b ${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan")

ADD_FLEX_BISON_DEPENDENCY (FibreScanLex FibreScanParser)

# C files relatively to thes CMakeLists.txt.
SET (C_DEPS_SRC
    system/src/World/World.c
    system/src/TimeStamp/TimeStamp.c
    system/src/Terminal/terminal.c
    system/src/SysErr/strerror.c
    system/src/SysErr/failsucc.c
    system/src/SysErr/errorcode.c
    system/src/RuntimeError/error.c
    system/src/RTimer/rtimer.c
    system/src/RTClock/rtclock.c
    system/src/Process/system.c
    system/src/Process/process.c
    system/src/MTClock/mtclock.c
    system/src/GetOpt/getopt.c
    system/src/FileSystem/tmpnam.c
    system/src/FileSystem/testfile.c
    system/src/FileSystem/tempnam.c
    system/src/FileSystem/symlink.c
    system/src/FileSystem/rename.c
    system/src/FileSystem/remove.c
    system/src/FileSystem/pltmp.c
    system/src/FileSystem/mktemp.c
    system/src/FileSystem/filesys.c
    system/src/FileSystem/dir.c
    system/src/FileSystem/access.c
    system/src/Environment/UnsetEnv.c
    system/src/Environment/SetEnv.c
    system/src/Environment/GetEnv.c
    system/src/Environment/ExistEnv.c
    system/src/Environment/Environ.c
    system/src/Environment/Env.c
    system/src/Dir/telldir.c
    system/src/Dir/seekdir.c
    system/src/Dir/rewinddir.c
    system/src/Dir/readdir.c
    system/src/Dir/opendir.c
    system/src/Dir/closedir.c
    system/src/CommandLine/CommandLine.c
    system/src/Clock/to_time.c
    system/src/Clock/strptime.c
    system/src/Clock/strftime.c
    system/src/Clock/sleep.c
    system/src/Clock/mktime.c
    system/src/Clock/isleap.c
    system/src/Clock/isdst.c
    system/src/Clock/gettime.c
    system/src/Clock/extracttime.c
    system/src/Clock/difftime.c
    system/src/Clock/date.c
    system/src/Clock/ctime.c
    system/src/Clock/copytime.c
    system/src/Clock/clock.c
    structures/src/StringArray/shape.c
    structures/src/StringArray/sel.c
    structures/src/StringArray/modarray.c
    structures/src/StringArray/index2offset.c
    structures/src/StringArray/genarray.c
    structures/src/StringArray/free.c
    structures/src/StringArray/dim.c
    structures/src/StringArray/copy.c
    structures/src/StringArray/alloc.c
    structures/src/String/trim.c
    structures/src/String/tostring.c
    structures/src/String/strtok.c
    structures/src/String/strtoi.c
    structures/src/String/strtof.c
    structures/src/String/strtod.c
    structures/src/String/strtake.c
    structures/src/String/strstr.c
    structures/src/String/strsel.c
    structures/src/String/strrchr.c
    structures/src/String/strovwt.c
    structures/src/String/strncat.c
    structures/src/String/strmod.c
    structures/src/String/strlen.c
    structures/src/String/strins.c
    structures/src/String/strext.c
    structures/src/String/strdrop.c
    structures/src/String/strcmp.c
    structures/src/String/strchr.c
    structures/src/String/strcat.c
    structures/src/String/sscanfstr.c
    structures/src/String/sprintf.c
    structures/src/String/itos.c
    structures/src/String/ftos.c
    structures/src/String/dtos.c
    structures/src/String/ctos.c
    structures/src/String/copystr.c
    structures/src/String/btos.c
    structures/src/List/tl.c
    structures/src/List/take.c
    structures/src/List/nth.c
    structures/src/List/nil.c
    structures/src/List/length.c
    structures/src/List/hd.c
    structures/src/List/free.c
    structures/src/List/empty.c
    structures/src/List/drop.c
    structures/src/List/cons.c
    structures/src/List/append.c
    structures/src/Format/wordsize.c
    structures/src/Constants/tinydouble.c
    structures/src/Constants/minmax.c
    structures/src/Constants/minint.c
    structures/src/Constants/minfloat.c
    structures/src/Constants/mindouble.c
    structures/src/Constants/maxint.c
    structures/src/Constants/maxfloat.c
    structures/src/Constants/maxdouble.c
    structures/src/Constants/epidouble.c
    structures/src/Char/ctype.c
    structures/src/Char/Char.c
    structures/src/Bits/BitXOR.c
    structures/src/Bits/BitTwosComplement.c
    structures/src/Bits/BitShiftRight.c
    structures/src/Bits/BitShiftLeft.c
    structures/src/Bits/BitRotateRight.c
    structures/src/Bits/BitRotateLeft.c
    structures/src/Bits/BitOnesComplement.c
    structures/src/Bits/BitOR.c
    structures/src/Bits/BitAND.c
    stdio/src/TermFile/stdstreams.c
    stdio/src/TermFile/printf.c
    stdio/src/TermFile/fscans.c
    stdio/src/TermFile/fscanl.c
    stdio/src/TermFile/fprintf.c
    stdio/src/PPM/ppm2array.c
    stdio/src/PPM/array2ppm.c
    stdio/src/PGM/pgm2array.c
    stdio/src/PGM/array2pgm.c
    stdio/src/File/rm.c
    stdio/src/File/mkstemp.c
    stdio/src/File/fscans.c
    stdio/src/File/fscanl.c
    stdio/src/File/fscanf.c
    stdio/src/File/fprintf.c
    stdio/src/File/fopen.c
    stdio/src/File/fclose.c
    stdio/src/FibreIO/ScanStringArr.c
    stdio/src/FibreIO/ScanString.c
    stdio/src/FibreIO/ScanOthersArr.c
    stdio/src/FibreIO/ScanOthers.c
    stdio/src/FibreIO/ScanIntArr.c
    stdio/src/FibreIO/ScanInt.c
    stdio/src/FibreIO/ScanFltArr.c
    stdio/src/FibreIO/ScanFlt.c
    stdio/src/FibreIO/ScanDblArr.c
    stdio/src/FibreIO/ScanDbl.c
    stdio/src/FibreIO/FibrePrint.c
    stdio/src/ComplexIO/PrintComplexArray.c
    stdio/src/BinFile/binfopen.c
    stdio/src/BinFile/binfflags.c
    stdio/src/BinFile/binfclose.c
    stdio/src/BinFile/binfWriteDblArr.c
    stdio/src/BinFile/binfReadDblArr.c
    stdio/src/ArrayIO/ShowArray.c
    stdio/src/ArrayIO/PrintArray.c
    numerical/src/Math/isnan.c
    numerical/src/Math/isinf.c
    numerical/src/Math/isfinite.c
    classes/random/src/Random/Random.c
    classes/random/src/Rand48/Rand48.c
    classes/random/src/Rand/Rand.c
    auxiliary/src/C99Benchmarking/bench.c
)

# Relative to BINARY_DIR
SET (FLEX_BISON_SRC
    stdio/src/FibreIO/lex.FibreScan.c
    stdio/src/FibreIO/FibreScan.tab.c
)

ADD_CUSTOM_COMMAND (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/lex.FibreScan.o"
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/lex.FibreScan.c"
        "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.h"
    COMMAND
        ${SAC2C} -Xc -I${CMAKE_CURRENT_SOURCE_DIR}/stdio/src/FibreIO
                 -Xc -I${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO
                 -v0 -noprelude -cc ccmod
                 -o "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/lex.FibreScan.o"
                 "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/lex.FibreScan.c"
    COMMENT "Generating FibreIO Lexer")

ADD_CUSTOM_COMMAND (
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.o"
    DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.c"
        "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.h"
    COMMAND
        ${SAC2C} -Xc -I${CMAKE_CURRENT_SOURCE_DIR}/stdio/src/FibreIO
                 -Xc -I${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO
                 -v0 -noprelude -cc ccmod
                 -o "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.o"
                 "${CMAKE_CURRENT_BINARY_DIR}/stdio/src/FibreIO/FibreScan.tab.c"
    COMMENT "Generating FibreIO Parser")


# SaC files relatively to this CMakeLists.txt.
SET (SAC_SRC
    utrace/UTrace.sac
    utrace/Indent.sac
    system/World.sac
    system/TimeStamp.sac
    system/Terminal.sac
    system/System.sac
    system/SysErr.sac
    system/RuntimeError.sac
    system/RTimer.sac
    system/RTClock.sac
    system/Process.sac
    system/MTClock.sac
    system/GetOpt.sac
    system/FileSystem.sac
    system/Environment.sac
    system/Dir.sac
    system/CommandLine.sac
    system/Clock.sac
    structures/Structures.sac
    structures/StringArray.sac
    structures/String.sac
    structures/List.sac
    structures/Grey.sac
    structures/Constants.sac
    structures/ComplexScalarArith.sac
    structures/ComplexBasics.sac
    structures/Complex.sac
    structures/Color8.sac
    structures/Char.sac
    structures/Bool.sac
    structures/Bits.sac
    structures/Array.sac
    stdio/TermFile.sac
    stdio/StdIO.sac
    stdio/ScalarIO.sac
    stdio/PPM.sac
    stdio/PGM.sac
    stdio/ListIO.sac
    stdio/IOresources.sac
    stdio/GreyIO.sac
    stdio/File.sac
    stdio/FibreIO.sac
    stdio/ComplexIO.sac
    stdio/Color8IO.sac
    stdio/BinFile.sac
    numerical/SaCMath.sac
    numerical/Numerical.sac
    numerical/MathArray.sac
    numerical/Math.sac
    numerical/FixedPoint.sac
    numerical/ComplexMath.sac
    classes/random/Random.sac
    classes/random/RandLC.sac
    classes/random/Rand48.sac
    classes/random/Rand.sac
    classes/auxiliary/Counter.sac
    auxiliary/Interval.sac
    auxiliary/Hiding.sac
    auxiliary/C99Benchmarking.sac
    auxiliary/Benchmarking.sac
)

SET (XSAC_SRC
    structures/ScalarArith.xsac
    structures/ComplexArrayTransform.xsac
    structures/ComplexArrayBasics.xsac
    structures/ComplexArrayArith.xsac
    structures/ArrayTransform.xsac
    structures/ArrayFormat.xsac
    structures/ArrayBasics.xsac
    structures/ArrayArith.xsac
    stdio/ArrayIO.xsac
)

# TODO(artem) We may want to introduce a mechanism of generating depenencies
#             on a given sac2c versoin.  That is, recompiler all modules if
#             sac2c version changes.


# For every C source, compile an object file maintaining the right location
# in the binary dir so that sac files can pick it up.
# XXX do we ever pass some extra flags, etc to C files?
FOREACH(name ${C_DEPS_SRC})
  SET (src "${CMAKE_CURRENT_SOURCE_DIR}/${name}")

  GET_FILENAME_COMPONENT (dir ${name} DIRECTORY)

  GET_FILENAME_COMPONENT (dst ${name} NAME_WE)
  SET (dst "${CMAKE_CURRENT_BINARY_DIR}/${dir}/${dst}${OBJEXT}")

  # Make sure that we put the object file in the same location where
  # the source file was.
  FILE (MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${dir}")

  ADD_CUSTOM_COMMAND (
    OUTPUT "${dst}"
    DEPENDS "${src}"
    COMMAND
        ${SAC2C} -Xc -I${CMAKE_CURRENT_SOURCE_DIR}/${dir}
                 -Xc -I${CMAKE_CURRENT_BINARY_DIR}/${dir}
                 -v0 -noprelude -cc ccmod -o "${dst}" "${src}"
    COMMENT "Generating ${dst}"
  )
ENDFOREACH(name)



# Make a directory for sac2c output
FILE (MAKE_DIRECTORY "${DLL_BUILD_DIR}/${TARGET_ENV}/${SBI}")

# For every sac file, compile Tree and Mod files.
FOREACH (name ${SAC_SRC})
    SET (src "${CMAKE_CURRENT_SOURCE_DIR}/${name}")
    # sac2c requires computes objectfiles relatively to the working directory
    # of the call to sac2c.
    GET_FILENAME_COMPONENT (dir "${CMAKE_CURRENT_BINARY_DIR}/${name}" DIRECTORY)
    GET_FILENAME_COMPONENT (dst ${name} NAME_WE)
    SET (mod
        "${DLL_BUILD_DIR}/${TARGET_ENV}/${SBI}/lib${dst}Mod${MODEXT}")
    SET (tree
        "${DLL_BUILD_DIR}/tree/${TARGET_ENV}/lib${dst}Tree${TREE_DLLEXT}")

    SET (ALL_SAC_SRC ${SAC_SRC})
    LIST (APPEND ALL_SAC_SRC ${XSAC_SRC})

    RESOLVE_SAC_DEPENDENCIES ("${name}" "${ALL_SAC_SRC}" moddep_list)

    MESSAGE ("dependencies of ${name} => `${moddep_list}'")

    ADD_CUSTOM_COMMAND (
        OUTPUT ${mod} ${tree}
        COMMAND
            ${SAC2C} -v0 -linksetsize ${LINKSETSIZE} -o ${DLL_BUILD_DIR} ${src}
        WORKING_DIRECTORY
            ${dir}
        DEPENDS ${moddep_list}
        COMMENT "Building ${name} module for target `${TARGET}'")

    # Install compiled Tree/Mod parts of the compiled module
    # to the corresponding locations.
    INSTALL (
        FILES ${mod}
        DESTINATION ${INSTALL_MOD_DIR}/${TARGET_ENV}/${SBI})
    INSTALL (
        FILES ${tree}
        DESTINATION ${INSTALL_TREE_DIR}/tree/${TARGET_ENV})

    # Make a call to the command that compiles the module a part
    # of the default build process.
    ADD_CUSTOM_TARGET (${TARGET}-module-${dst} ALL DEPENDS ${mod} ${tree})
ENDFOREACH (name)

# For every xsac file, compile Tree and Mod files.
FOREACH (name ${XSAC_SRC})
    SET (src "${CMAKE_CURRENT_SOURCE_DIR}/${name}")
    # sac2c requires computes objectfiles relatively to the working directory
    # of the call to sac2c.
    GET_FILENAME_COMPONENT (dir "${CMAKE_CURRENT_BINARY_DIR}/${name}" DIRECTORY)
    GET_FILENAME_COMPONENT (dst ${name} NAME_WE)
    SET (mod
        "${DLL_BUILD_DIR}/${TARGET_ENV}/${SBI}/lib${dst}Mod${MODEXT}")
    SET (tree
        "${DLL_BUILD_DIR}/tree/${TARGET_ENV}/lib${dst}Tree${TREE_DLLEXT}")

    SET (ALL_SAC_SRC ${SAC_SRC})
    LIST (APPEND ALL_SAC_SRC ${XSAC_SRC})

    RESOLVE_SAC_DEPENDENCIES ("${name}" "${ALL_SAC_SRC}" moddep_list)

    MESSAGE ("dependencies of ${name} => `${moddep_list}'")

    ADD_CUSTOM_COMMAND (
        OUTPUT ${mod} ${tree}
        # FIXME it would be better to call saccc like it is done currently
        #       $(SACCC) $(SAC2C) prog seq -E "-x c" -I. $(DEFS)
        COMMAND
            ${SAC2C} -cc ccprog -Xc -E -Xc -xc -noprelude -o /dev/stdout ${src} > ${dir}/${dst}.sac
        COMMAND
            ${SAC2C} -v0 -linksetsize ${LINKSETSIZE} -o ${DLL_BUILD_DIR} ${dir}/${dst}.sac
        WORKING_DIRECTORY
            ${dir}
        DEPENDS ${moddep_list}
        COMMENT "Building ${name} module for target `${TARGET}'")

    # Install compiled Tree/Mod parts of the compiled module
    # to the corresponding locations.
    INSTALL (
        FILES ${mod}
        DESTINATION ${INSTALL_MOD_DIR}/${TARGET_ENV}/${SBI})
    INSTALL (
        FILES ${tree}
        DESTINATION ${INSTALL_TREE_DIR}/tree/${TARGET_ENV})

    # Make a call to the command that compiles the module a part
    # of the default build process.
    ADD_CUSTOM_TARGET (${TARGET}-module-${dst} ALL DEPENDS ${mod} ${tree})
ENDFOREACH (name)


