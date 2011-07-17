/*
 * $Id$
 *
 * Description:
 *
 * This module implements the functionally sound integration of the real
 * time clock into the world of SAC.
 */


#include <time.h>


void *TheRTClock;

void *SAC_RTClock_createTheRTClock( void)
{
  return((void*)0);
}

void SAC_RTClock_touch( void *rtclock)
{
}

void SAC_RTClock_gettime( int *sec, int *nano)
{
  struct timespec result;

  clock_gettime( CLOCK_REALTIME, &result);

  *sec = (int) result.tv_sec;
  *nano = (int) result.tv_nsec;
}
                                                                   

