/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


double FibreScanDouble( FILE *stream)
{
  start_token = PARSE_DOUBLE;
  doScan( stream);
  return( doubleval);
}



