/*
 *  Implementation of printing functions for Arrays as used in ArrayIO
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "sacinterface.h"

#define COMPLEX     1

typedef char* string;
typedef double complex[2];

static
sac_int Index2Offset( sac_int dim, sac_int *shp, sac_int *index)
{
  sac_int i,n;
  sac_int offset=0;
  sac_int fact;

  for (i=0; i<dim; i++) {
    fact=1;
    for (n=i+1; n<dim; n++) {
      fact *= shp[n];
    }
    offset += index[i]*fact;
  }
  return(offset);
}

static void PrintArr(FILE *stream, int typeflag, string format, sac_int dim, sac_int * shp, void *a)
{
  sac_int i,n, element_count;
  char *space=" ";
  sac_int *index;

  fprintf(stream, "Dimension: " PRIisac "\n", dim);
  fprintf(stream, "Shape    : <");
  element_count = 1;
  for (i=0;i<dim;) {
    fprintf(stream, " " PRIisac, shp[i]);
    element_count = element_count * shp[i];
    i++;
    if (i<dim) {
      fprintf(stream, ",");
    }
  }
  fprintf(stream, ">\n");

  /*
   * Now, element_count carries the total number of elements
   * to be expected behind *a!
   */

  if( dim == 0) {
    switch(typeflag) {
      case COMPLEX:
        fprintf(stream, format, (*((complex *)a))[0], (*((complex *)a))[1]);
        break;
      default:
        break;
    }
   fprintf(stream,"\n");

  } else if (dim > 0) {
    if (element_count == 0) {
      fprintf(stream, "<>\n");
    } else {

      index = SAC_MALLOC(dim * sizeof(sac_int));
      for (i=0; i<dim; i++) {
        index[i]=0;
      }
      n=dim-1;

      /*
       * Now, we have:
       *     index == [0,...,0]
       *               0,...,n
       */
      do {
        if (dim%2 == 1) {
          fprintf(stream, "<");
        } else {
          fprintf(stream, "|");
        }

        while (index[n] < shp[dim-1]) {

          switch(typeflag) {
          case COMPLEX:
            fprintf(stream, format,
	    	            (((complex *)a)[Index2Offset(dim,shp,index)])[0],
                    (((complex *)a)[Index2Offset(dim,shp,index)])[1]);
            break;
          default:
            break;
          }

          index[n]++;
        }

        if (dim%2 == 1) {
          index[n] = 0;
          n--;
          fprintf(stream, "> ");
        }
        else {
          fprintf(stream, "| ");
        }

        while(( n>0) && (index[n]>=(shp[n]-1))) {
          index[n]=0;
          n -= 2;
          if(n<0) {
            space="\n";
            n=((dim-2)/2)*2;
          }
          fprintf(stream, "%s",space);
        }
        if(( n>=0) && (index[n]<(shp[n]-1))) {
          index[n]++;
          n=dim-1;
          space=" ";
        }
      } while( n>0);

      fprintf(stream, "\n");

      SAC_FREE(index);
    } /* if (element_count == 0) */
  } else {
    SAC_RuntimeError ("Dimension is less than 0, aborting!");
  }

}

void COMPLEXIO__PrintComplexArray( FILE *stream, sac_int dim, sac_int * shp, complex * a)
{
  PrintArr(stream, COMPLEX, "(%.g, %.g) ", dim, shp, a);
}

void COMPLEXIO__PrintComplexArrayFormat( FILE *stream, string format, sac_int dim, sac_int * shp, complex * a)
{
  PrintArr(stream, COMPLEX, format, dim, shp, a);
}
