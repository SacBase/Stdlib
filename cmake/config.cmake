INCLUDE (CheckFunctionExists)
INCLUDE (CheckCSourceCompiles)
INCLUDE (CheckLibraryExists)
INCLUDE (CheckIncludeFiles)
INCLUDE ("cmake/options.cmake")

# Check for flex/bison
FIND_PACKAGE (BISON REQUIRED)
FIND_PACKAGE (FLEX REQUIRED)

MESSAGE ("
 * Stdlib configuration done.
 *
 * sac2c executable:       ${SAC2C_EXEC}
 * local builddir:         ${DLL_BUILD_DIR}
 * targets:                ${TARGETS}
 * sac2c CPP flags:        ${SAC2C_CPP_INC}
 * sac2c extra flags:      ${SAC2C_EXTRA_INC}
 *
 * Configuration state:
 * - full types:           ${FULLTYPES}
 * - build generic         ${BUILDGENERIC}
 * - build extended:       ${BUILD_EXT}
 *
 * Packaging state:
 * - is release:           ${IS_RELEASE}
")
