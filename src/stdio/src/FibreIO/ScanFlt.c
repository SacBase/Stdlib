/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


float FibreScanFloat()
{
  yyin = stdin;
  start_token = PARSE_FLOAT;
  FibreScanparse();
  return( floatval);
}



