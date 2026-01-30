/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

SACarg *FibreScanFloatArray(FILE *stream)
{
    /**
     * Global variables created by the .y file:
     *      float  *floatarray
     *      sac_int *shp
     *      sac_int dims
     *      sac_int size
     **/
    sac_int i;
    start_token = PARSE_FLOAT_ARRAY;
    doScan(stream);
  
    return SACARGcreateFromPointer(SACTYPE__MAIN__float, floatarray, dims, shp);
}

SACarg *FibreScanFloatArrayStr(SACarg *stream_in)
{
    char *stream = SACARGgetUniqueData(SACARGgetType(stream_in), stream_in);
    sac_int i;
    start_token = PARSE_FLOAT_ARRAY;
    yy_scan_string(stream);
    FibreScanparse();

    return SACARGcreateFromPointer(SACTYPE__MAIN__float, floatarray, dims, shp);
}
