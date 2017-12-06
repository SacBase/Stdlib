/*
 * $Id$
 *
 * Description:
 *
 * This module implements the functionally sound integration of the real
 * time clock into the world of SAC.
 */

#include <time.h>
#include "libsac/essentials/message.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_GETTIME_REALTIME
#include <sys/times.h>
#elif HAVE_MACH_CLOCK_GET_TIME
#include <mach/clock.h>
#include <mach/mach.h>
#endif


void *SAC_RTClock_createTheRTClock( void)
{
  return((void*)0);
}

void SAC_RTClock_touch( void *rtclock)
{
}

void SAC_RTClock_gettime( long *sec, long *nano)
{
  struct timespec result;

  result.tv_sec = 0;
  result.tv_nsec = 0;

#ifdef HAVE_GETTIME_REALTIME

  clock_gettime( CLOCK_REALTIME, &result);

#elif HAVE_MACH_CLOCK_GET_TIME
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  result.tv_sec = mts.tv_sec;
  result.tv_nsec = mts.tv_nsec;

#else
  SAC_RuntimeError( "When the stdlib was compiled for this architecture"
                      " neither clock_gettime( CLOCK_REALTIME, x) "
                      " nor host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, x)"
                      " were found");
#endif

  *sec = result.tv_sec;
  *nano = result.tv_nsec;
}
