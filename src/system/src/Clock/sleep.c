/*
 *  Implementation of standard module Time
 */



#include <unistd.h>

/******************************************************************/

void SACsleep(int sec)
{
  if (sec > 0) {
    sleep( (unsigned) sec);
  }
}



/******************************************************************/
