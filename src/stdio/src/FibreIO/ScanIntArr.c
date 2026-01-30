/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

SACarg *FibreScanIntArray(FILE *stream)
{
    /**
     * Global variables created by the .y file:
     *      sac_int  *intarray
     *      sac_int *shp
     *      sac_int dims
     *      sac_int size
     **/
    sac_int i;
    start_token = PARSE_INT_ARRAY;
    doScan(stream);
  
    return SACARGcreateFromPointer(SACTYPE__MAIN__int, intarray, dims, shp);
}

SACarg *FibreScanIntArrayStr(SACarg *stream_in)
{
    char *stream = SACARGgetUniqueData(SACARGgetType(stream_in), stream_in);
    sac_int i;
    start_token = PARSE_INT_ARRAY;
    yy_scan_string(stream);
    FibreScanparse();

    return SACARGcreateFromPointer(SACTYPE__MAIN__int, intarray, dims, shp);
}
