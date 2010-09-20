/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


float FibreScanFloat( FILE *stream)
{
  start_token = PARSE_FLOAT;
  doScan( stream);
  return( floatval);
}



