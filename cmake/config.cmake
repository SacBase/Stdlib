INCLUDE (CheckFunctionExists)
INCLUDE (CheckCSourceCompiles)
INCLUDE (CheckLibraryExists)
INCLUDE (CheckIncludeFiles)
INCLUDE ("cmake/options.cmake")

# Additional config checks regarding feature support
INCLUDE ("cmake-common/check-sac2c-feature-support.cmake")

# Check for flex/bison
FIND_PACKAGE (BISON  REQUIRED)
FIND_PACKAGE (FLEX  REQUIRED)

# Check mkdtemp exists
CHECK_FUNCTION_EXISTS (mkdtemp HAVE_MKDTEMP)

# Check if we support SAC2C header pragma
CHECK_SAC2C_SUPPORT_HEADER_PRAGMA ()

CONFIGURE_FILE ("${PROJECT_SOURCE_DIR}/cmake/config.h.in"
                "${PROJECT_BINARY_DIR}/include/config.h")

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
