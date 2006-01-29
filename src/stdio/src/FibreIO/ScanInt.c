/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


int FibreScanInt()
{
  start_token = PARSE_INT;
  yyin = stdin;
  FibreScanparse();
  return( intval);
}



