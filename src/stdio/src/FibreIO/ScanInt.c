/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


int FibreScanInt( FILE *stream)
{
  start_token = PARSE_INT;
  yyin = stream;
  FibreScanparse();
  return( intval);
}



