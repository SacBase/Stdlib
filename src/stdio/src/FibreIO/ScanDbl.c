/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


double FibreScanDouble()
{
  yyin = stdin;
  start_token = PARSE_DOUBLE;
  FibreScanparse();
  return( doubleval);
}



