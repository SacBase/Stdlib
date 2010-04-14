#include <sys/time.h>
#include <stdio.h>

void timeStamp(){
  struct timeval time;
  if ( gettimeofday(&time, (struct timezone *)NULL) == 0){
    printf( "%09d.%06d\n", (int)(time.tv_sec), (int)(time.tv_usec));
  }
}
