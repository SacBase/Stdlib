/*
 * $Id$
 *
 * Description:
 *
 * This module implements the functionally sound integration of the monotonic
 * time clock into the world of SAC.
 */


#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void *TheMTClock;

void *SAC_MTClock_createTheMTClock( void)
{
  return((void*)0);
}

void SAC_MTClock_touch( void *mtclock)
{
    /* noop */
}

void SAC_MTClock_gettime( long *sec, long *nano)
{
  struct timespec result;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  result.tv_sec = mts.tv_sec;
  result.tv_nsec = mts.tv_nsec;
#else
  // Using the raw monotonic clock because the
  // latter is NOT influenced by changes to system time (be it via an admin
  // changing the time of the system or NTP updating the time)
  //
  // If however the raw monotonic clock is not available, we default to using
  // the regular monotonic clock - which can be influenced by NTP and the like.
  #ifndef CLOCK_MONOTONIC_RAW
  clock_gettime( CLOCK_MONOTONIC, &result);
  #else
  clock_gettime( CLOCK_MONOTONIC_RAW, &result);
  #endif
#endif

  *sec = result.tv_sec;
  *nano = result.tv_nsec;
}
                                                                   

