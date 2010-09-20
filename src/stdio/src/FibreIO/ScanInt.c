/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


int FibreScanInt( FILE *stream)
{
  start_token = PARSE_INT;
  doScan( stream);
  return( intval);
}



