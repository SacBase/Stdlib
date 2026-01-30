/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

SACarg *FibreScanDoubleArray(FILE *stream)
{
    /**
     * Global variables created by the .y file:
     *      double  *doublearray
     *      sac_int *shp
     *      sac_int dims
     *      sac_int size
     **/
    sac_int i;
    start_token = PARSE_DOUBLE_ARRAY;
    doScan(stream);
  
    return SACARGcreateFromPointer(SACTYPE__MAIN__double, doublearray, dims, shp);
}

SACarg *FibreScanDoubleArrayStr(SACarg *stream_in)
{
    char *stream = SACARGgetUniqueData(SACARGgetType(stream_in), stream_in);
    sac_int i;
    start_token = PARSE_DOUBLE_ARRAY;
    yy_scan_string(stream);
    FibreScanparse();

    return SACARGcreateFromPointer(SACTYPE__MAIN__double, doublearray, dims, shp);
}
