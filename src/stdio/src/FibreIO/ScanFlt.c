/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


float FibreScanFloat( FILE *stream)
{
  yyin = stream;
  start_token = PARSE_FLOAT;
  FibreScanparse();
  return( floatval);
}



