/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


char *FibreScanString( FILE *stream)
{
  yyin = stream;
  start_token = PARSE_STRING;
  FibreScanparse();
  return( stringval);
}



