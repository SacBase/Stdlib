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

# Check whether we have/need -lm
SET (NEED_LIBM)
SET (LIB_M_SRC "
#include <math.h>

int main(void) {
    return pow (3, 1.4);
}
")

CHECK_C_SOURCE_COMPILES ("${LIB_M_SRC}"   POW_WORKS)
IF (NOT POW_WORKS)
    UNSET (POW_WORKS)
    SET (OLD_FLAGS ${CMAKE_REQUIRED_LIBRARIES})
    LIST (APPEND CMAKE_REQUIRED_LIBRARIES m)
    CHECK_C_SOURCE_COMPILES ("${LIB_M_SRC}" POW_WORKS)
    SET (CMAKE_REQUIRED_LIBRARIES ${OLD_FLAGS})
    IF (POW_WORKS)
        SET (NEED_LIBM 1)
    ELSE ()
        MESSAGE (FATAL_ERROR
                 "Failed to compile math function `pow', "
                 "both with and without -lm")
    ENDIF ()
ENDIF ()

SET (NEED_LIBRT)
SET (HAVE_GETTIME_REALTIME 1)
SET (LIBRT_TEST_PROG "
#include <time.h>
#include <sys/times.h>
int main (void) {
 struct timespec ts;
 clock_gettime (CLOCK_REALTIME, &ts);
 return 0;
}
")

CHECK_C_SOURCE_COMPILES ("${LIBRT_TEST_PROG}"   RT_WORKS)
IF (NOT RT_WORKS)
    UNSET (RT_WORKS)
    SET (OLD_FLAGS ${CMAKE_REQUIRED_LIBRARIES})
    LIST (APPEND CMAKE_REQUIRED_LIBRARIES rt)
    CHECK_C_SOURCE_COMPILES ("${LIBRT_TEST_PROG}"   RT_WORKS)
    SET (CMAKE_REQUIRED_LIBRARIES ${OLD_FLAGS})
    IF (RT_WORKS)
        SET (NEED_LIBRT 1)
    ELSE ()
        SET (HAVE_GETTIME_REALTIME 0)
    ENDIF ()
ENDIF ()


CHECK_C_SOURCE_COMPILES ("
#include <time.h>
#include <mach/clock.h>
#include <mach/mach.h>
int main (void) {
  struct timespec ts;
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service (mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time (cclock, &mts);
  mach_port_deallocate (mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;
"
HAVE_MACH_CLOCK_GET_TIME)

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
 * - realtime clock:       ${HAVE_GETTIME_REALTIME}
 * - mach clock:           ${HAVE_MACH_CLOCK_GET_TIME}
 * - full types:           ${FULLTYPES}
 * - build generic         ${BUILDGENERIC}
 * - build extended:       ${BUILD_EXT}
 *
 * Packaging state:
 * - is release:           ${IS_RELEASE}
")
