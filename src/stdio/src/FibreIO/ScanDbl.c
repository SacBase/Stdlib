/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


double FibreScanDouble( FILE *stream)
{
  yyin = stream;
  start_token = PARSE_DOUBLE;
  FibreScanparse();
  return( doubleval);
}



