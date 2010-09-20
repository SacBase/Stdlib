/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


char *FibreScanString( FILE *stream)
{
  start_token = PARSE_STRING;
  doScan( stream);
  return( stringval);
}



