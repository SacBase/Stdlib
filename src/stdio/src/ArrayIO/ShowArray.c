/* $Id$ */

/*
 *  Implementation of printing functions for Arrays as used in ArrayIO,
 *  conforming with ISO Standard APL N8485.
 *  The show() functions print data only - no rank, shape, or decorators
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "sac.h"

#define INT    1
#define FLOAT  2
#define DOUBLE 3
#define CHAR   4
#define BOOL   5

typedef char* string;

static
void ShowArr(FILE *stream, int typeflag, string fmt, int dim, int * shp, char *a)
{
  // Introduce new lines at end of ultimate and penultimate dimensions
  int i, element_count;
  int rownum, colnum, planenum;
  int rownums, colnums, planenums; 
  int rowoffset = 0;

  planenums = 1;
  for (i=0;i<(dim-2);i++) {
    planenums = planenums * shp[i];
  }


  if( 0 == dim) {  // show scalar
        fprintf(stream, fmt, a[0]);
        fprintf(stream, "\n");  // End row with new line
  } else {
    colnums = shp[dim-1];
    if (dim >= 2) { // row count for matrix and tensor
      rownums = shp[dim-2];
    } else {
      rownums = 1; // vector row count
    }

    element_count = planenums * colnums * rownums;

    if (element_count != 0) {  // no output for empty array
      for ( planenum=0; planenum<planenums; planenum++) {
       for ( rownum=0; rownum<rownums; rownum++) {  
        for ( colnum=0; colnum<colnums; colnum++) { // format one row
            fprintf(stream, fmt, a[rowoffset + colnum]);
        }
        fprintf(stream, "\n");  // End row with new line

        if ((rownum == (rownums-1)) && (planenum != (planenums-1))) {
          fprintf(stream, "\n");  // End all but last plane with new line
        }
        rowoffset = rowoffset + colnums;
       }
      }
    }
  }
}


void ARRAYIO__ShowCharArray( FILE *stream, int dim, int * shp, char * a)
{
  ShowArr(stream, CHAR, "%c", dim, shp, a);
}
