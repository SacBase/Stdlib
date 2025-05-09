/******************************************************************************
 *
 * @file rtclock.c
 *
 * @brief This module implements the functionally sound integration of the
 * real time clock into the world of SAC.
 *
 ******************************************************************************/
#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void *SAC_RTClock_createTheRTClock(void)
{
    return((void*)0);
}

void SAC_RTClock_touch(void *rtclock)
{
    /* noop */
}

void SAC_RTClock_gettime(long *sec, long *nsec)
{
    struct timespec result;
    result.tv_sec = 0;
    result.tv_nsec = 0;

#ifdef __MACH__
    // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    result.tv_sec = mts.tv_sec;
    result.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &result);
#endif

    *sec = result.tv_sec;
    *nsec = result.tv_nsec;
}
