/*
 * $Id$
 *
 * Description:
 *
 * This module implements access to the system real time clock, more precisely
 * it provides functions to create, start, stop, reset and inquire real clock timers.
 *
 * As a special feature timers can be 'stacked', i.e. a timer can repeatedly be
 * started without effect, the timer just continues to run. It then requires the
 * same number of stops to effectively stop. This feature is meant as a preparatory
 * step towards automatically inserting timer calls into the code by the compiler,
 * where we need to take recursive functions into account.
 */



#include <time.h>
#include "sac.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_GETTIME_REALTIME
#include <sys/times.h>
#elif HAVE_MACH_CLOCK_GET_TIME
#include <mach/clock.h>
#include <mach/mach.h>
#endif


struct rtimer
{
  struct timespec elapsed;
  struct timespec started;
  int instance;
};


void current_utc_time(struct timespec *ts) {

    ts->tv_sec = 0;
    ts->tv_nsec = 0;

#ifdef HAVE_GETTIME_REALTIME

    clock_gettime( CLOCK_REALTIME, ts);

#elif HAVE_MACH_CLOCK_GET_TIME

    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;

#else
    SAC_RuntimeError( "When the stdlib was compiled for this architecture"
                      " neither clock_gettime( CLOCK_REALTIME, x) "
                      " nor host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, x)"
                      " were found");
#endif

}



void SAC_RTimer_createRTimer( struct rtimer **ts)
{
  *ts = (struct rtimer *) SAC_MALLOC( sizeof( struct rtimer));
  (*ts)->elapsed.tv_sec = 0;
  (*ts)->elapsed.tv_nsec = 0;
  (*ts)->started.tv_sec = 0;
  (*ts)->started.tv_nsec = 0;
  (*ts)->instance = 0;
}

void SAC_RTimer_destroyRTimer( struct rtimer *ts)
{
  SAC_FREE( ts);
}

void SAC_RTimer_startRTimer( struct rtimer *timer)
{
  if (timer->instance == 0) {
    current_utc_time(&(timer->started));
    timer->instance += 1;
  }
}

void SAC_RTimer_stopRTimer( struct rtimer *timer)
{
  struct timespec now;
  
  if (timer->instance == 1) {
    current_utc_time(&now);
    if (now.tv_nsec > timer->started.tv_nsec) {
      timer->elapsed.tv_sec += now.tv_sec - timer->started.tv_sec;
      timer->elapsed.tv_nsec += now.tv_nsec - timer->started.tv_nsec;
    }
    else {
      timer->elapsed.tv_sec += (now.tv_sec - timer->started.tv_sec) - 1;
      timer->elapsed.tv_nsec += 1000000000L - timer->started.tv_nsec + now.tv_nsec;
    }
    timer->instance = 0;
  }
  else if (timer->instance > 1) {
    timer->instance -= 1;
  }
}

void SAC_RTimer_resetRTimer( struct rtimer *timer)
{
  if (timer->instance == 0) {
    timer->elapsed.tv_sec = 0;
    timer->elapsed.tv_nsec = 0;
  }
}


void SAC_RTimer_getRTimerInts( struct rtimer *timer, int *sec, int *nsec)
{
  *sec = (int) (timer->elapsed.tv_sec);
  *nsec = (int) (timer->elapsed.tv_nsec);
}

double SAC_RTimer_getRTimerDbl( struct rtimer *timer)
{
  double res;
  
  res = ((double) timer->elapsed.tv_sec) + ((double) timer->elapsed.tv_nsec) / 1000000000.0;
  
  return res;
}


  
  
