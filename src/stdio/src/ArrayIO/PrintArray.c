/* $Id$ */

/*
 *  Implementation of printing functions for Arrays as used in ArrayIO
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
int Index2Offset( int dim, int *shp, int *index)
{
  int i,n;
  int offset=0;
  int fact;

  for (i=0; i<dim; i++) {
    fact=1;
    for (n=i+1; n<dim; n++) {
      fact *= shp[n];
    }
    offset += index[i]*fact;
  }
  return(offset);
}


static
void PrintArr(FILE *stream, int typeflag, string format, int dim, int * shp, void *a)
{
  int i,n, element_count;
  char *space=" ";
  int *index;

  fprintf(stream, "Dimension: %2i\n", dim);
  fprintf(stream, "Shape    : <");
  element_count = 1;
  for (i=0;i<dim;) {
    fprintf(stream, " %2i", shp[i]);
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
      case BOOL:
        fprintf(stream, format , ((int *)a)[0]);
        break;
      case INT:
        fprintf(stream, format , ((int *)a)[0]);
        break;
      case FLOAT:
        fprintf(stream, format, ((float *)a)[0]);
        break;
      case DOUBLE:
        fprintf(stream, format, ((double *)a)[0]);
        break;
      case CHAR:
        fprintf(stream, format, ((char *)a)[0]);
        break;
      }
   fprintf(stream,"\n");

  } else {
    if (element_count == 0) {
      fprintf(stream, "<>\n");
    } else {

      index=(int *)SAC_MALLOC(sizeof(int)*dim);
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

        while (index[n]<shp[dim-1]) {
          switch(typeflag) {
          case BOOL:
            fprintf(stream, format , ((int *)a)[Index2Offset(dim,shp,index)]);
            break;
          case INT:
            fprintf(stream, format , ((int *)a)[Index2Offset(dim,shp,index)]);
            break;
          case FLOAT:
            fprintf(stream, format, ((float *)a)[Index2Offset(dim,shp,index)]);
            break;
          case DOUBLE:
            fprintf(stream, format, ((double *)a)[Index2Offset(dim,shp,index)]);
            break;
          case CHAR:
            fprintf(stream, format, ((char *)a)[Index2Offset(dim,shp,index)]);
            break;
          }
          index[n]++;
        }

        if (dim%2 ==1) {
          index[n]=0;
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
  }

}

void PrintBoolArray( FILE **stream, int dim, int * shp, bool * a)
{
  PrintArr(*stream, BOOL, "2%i ", dim, shp, a);
}

void PrintDoubleArray( FILE **stream, int dim, int * shp, double * a)
{
  PrintArr(*stream, DOUBLE, "%e ", dim, shp, a);
}

void PrintFloatArray( FILE **stream, int dim, int * shp, float * a)
{
  PrintArr(*stream, FLOAT, "%4f ", dim, shp, a);
}

void PrintIntArray( FILE **stream, int dim, int * shp, int * a)
{
  PrintArr(*stream, INT, "%2i ", dim, shp, a);
}

void PrintCharArray( FILE **stream, int dim, int * shp, char * a)
{
  PrintArr(*stream, CHAR, "%c", dim, shp, a);
}
