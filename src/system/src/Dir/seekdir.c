/*
 *  implementation of directory functions.
 */



#include "Dir.h"



/*****************************************************************/

void SACseekdir( DIR* stream, long pos)
{
  seekdir( stream, pos);
}


/*****************************************************************/
