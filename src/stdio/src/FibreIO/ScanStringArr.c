/*
 *  Implementation of standard module FibreScan
 */

#include "FibreScan.h"
#include "FibreScan.tab.h"

#include "../../../structures/src/StringArray/StringArray.h"

/* I have no idea if this is correct */
SACarg *FibreScanStringArray(FILE *stream)
{
    sac_int size;
    sac_int i;
    array *res;
    
    start_token = PARSE_STRING_ARRAY;
    doScan(stream);
    
    size = 1;
    for (i = 0; i < dims; i++) {
      size *= shp[i];
    }
    
    res = SAC_StringArray_alloc(dims, size);
    
    for (i = 0; i < dims; i++) {
      res->shp[i] = shp[i];
    }
    
    /* stringarray is char ** */
    for (i = 0; i < size; i++) {
        res->elems[i] = SACARGcreateFromPointer(SACTYPE__String__string,
                                                stringarray[i], 0, NULL);
    }
    
    return SACARGcreateFromPointer(SACTYPE__StringArray__stringArray,
                                   res, dims, shp);
}

SACarg *FibreScanStringArrayStr(char *stream)
{
    sac_int size;
    sac_int i;
    array *res;
  
    start_token = PARSE_STRING_ARRAY;
    yy_scan_string(stream);
    FibreScanparse();
  
    size = 1;
    for (i = 0; i < dims; i++) {
      size *= shp[i];
    }
  
    for (i = 0; i < dims; i++) {
      res->shp[i] = shp[i];
    }
  
    for (i = 0; i < size; i++) {
        res->elems[i] = SACARGcreateFromPointer(SACTYPE__String__string,
                                                stringarray[i],
                                                0, NULL);
    }
  
    return SACARGcreateFromPointer(SACTYPE__StringArray__stringArray,
                                   res, dims, shp);
}
