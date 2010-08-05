/* $Id$ */

/*
 *  Implementation of printing functions for Arrays as used in ArrayIO
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#include "sac.h"


#define INT    		1
#define FLOAT  		2
#define DOUBLE 		3
#define CHAR   		4
#define BOOL   		5
#define BYTE    	6
#define SHORT    	7
#define LONG    	8
#define LONGLONG    	9
#define UBYTE    	10
#define USHORT    	11
#define UINT   		12
#define ULONG    	13
#define ULONGLONG    	14


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
      case BYTE:
        fprintf(stream, format , ((char *)a)[0]);
        break;
      case SHORT:
        fprintf(stream, format , ((short *)a)[0]);
        break;
      case INT:
        fprintf(stream, format , ((int *)a)[0]);
        break;
      case LONG:
        fprintf(stream, format , ((long *)a)[0]);
        break;
      case LONGLONG:
        fprintf(stream, format , ((long long *)a)[0]);
        break;
      case UBYTE:
        fprintf(stream, format , ((unsigned char *)a)[0]);
        break;
      case USHORT:
        fprintf(stream, format , ((unsigned short *)a)[0]);
        break;
      case UINT:
        fprintf(stream, format , ((unsigned int *)a)[0]);
        break;
      case ULONG:
        fprintf(stream, format , ((unsigned long *)a)[0]);
        break;
      case ULONGLONG:
        fprintf(stream, format , ((unsigned long long *)a)[0]);
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
            fprintf(stream, format , 
	    	((int *)a)[Index2Offset(dim,shp,index)]);
            break;
          case BYTE:
            fprintf(stream, format , 
	    	((char *)a)[Index2Offset(dim,shp,index)]);
            break;
          case SHORT:
            fprintf(stream, format , 
	    	((short *)a)[Index2Offset(dim,shp,index)]);
            break;
          case INT:
            fprintf(stream, format , 
	    	((int *)a)[Index2Offset(dim,shp,index)]);
            break;
          case LONG:
            fprintf(stream, format , 
	    	((long *)a)[Index2Offset(dim,shp,index)]);
            break;
          case LONGLONG:
            fprintf(stream, format , 
	    	((long long *)a)[Index2Offset(dim,shp,index)]);
            break;
          case UBYTE:
            fprintf(stream, format , 
	    	((unsigned char *)a)[Index2Offset(dim,shp,index)]);
            break;
          case USHORT:
            fprintf(stream, format , 
	    	((unsigned short *)a)[Index2Offset(dim,shp,index)]);
            break;
          case UINT:
            fprintf(stream, format , 
	    	((unsigned int *)a)[Index2Offset(dim,shp,index)]);
            break;
          case ULONG:
            fprintf(stream, format , 
	    	((unsigned long *)a)[Index2Offset(dim,shp,index)]);
            break;
          case ULONGLONG:
            fprintf(stream, format , 
	    	((unsigned long long *)a)[Index2Offset(dim,shp,index)]);
            break;
          case FLOAT:
            fprintf(stream, format, 
	    	((float *)a)[Index2Offset(dim,shp,index)]);
            break;
          case DOUBLE:
            fprintf(stream, format, 
	    	((double *)a)[Index2Offset(dim,shp,index)]);
            break;
          case CHAR:
            fprintf(stream, format, 
	    	((char *)a)[Index2Offset(dim,shp,index)]);
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

void ARRAYIO__PrintBoolArray( FILE *stream, int dim, int * shp,	bool * a)
{
  PrintArr(stream, BOOL, "%2i ", dim, shp, a);
}

void ARRAYIO__PrintDoubleArray( FILE *stream, int dim, int * shp, double * a)
{
  PrintArr(stream, DOUBLE, "%e ", dim, shp, a);
}

void ARRAYIO__PrintFloatArray( FILE *stream, int dim, int * shp, float * a)
{
  PrintArr(stream, FLOAT, "%4f ", dim, shp, a);
}

void ARRAYIO__PrintByteArray( FILE *stream, int dim, int * shp, char * a)
{
  PrintArr(stream, BYTE, "%2hd ", dim, shp, a);
}

void ARRAYIO__PrintShortArray( FILE *stream, int dim, int * shp, short * a)
{
  PrintArr(stream, SHORT, "%2hd ", dim, shp, a);
}

void ARRAYIO__PrintIntArray( FILE *stream, int dim, int * shp, int * a)
{
  PrintArr(stream, INT, "%2i ", dim, shp, a);
}

void ARRAYIO__PrintLongArray( FILE *stream, int dim, int * shp,	long * a)
{
  PrintArr(stream, LONG, "%2ld ", dim, shp, a);
}

void ARRAYIO__PrintLonglongArray( FILE *stream, int dim, int * shp, long long * a)
{
  PrintArr(stream, LONGLONG, "%2lld ", dim, shp, a);
}

void ARRAYIO__PrintUbyteArray( FILE *stream, int dim, int * shp, unsigned char * a)
{
  PrintArr(stream, UBYTE, "%2hu ", dim, shp, a);
}

void ARRAYIO__PrintUshortArray( FILE *stream, int dim, int * shp,	unsigned short * a)
{
  PrintArr(stream, USHORT, "%2hu ", dim, shp, a);
}

void ARRAYIO__PrintUintArray( FILE *stream, int dim, int * shp, unsigned int * a)
{
  PrintArr(stream, UINT, "%2u ", dim, shp, a);
}

void ARRAYIO__PrintUlongArray( FILE *stream, int dim, int * shp, unsigned long * a)
{
  PrintArr(stream, ULONG, "%2lu ", dim, shp, a);
}

void ARRAYIO__PrintUlonglongArray( FILE *stream, int dim, int * shp, unsigned long long * a)
{
  PrintArr(stream, ULONGLONG, "%2llu ", dim, shp, a);
}

void ARRAYIO__PrintCharArray( FILE *stream, int dim, int * shp,	char * a)
{
  PrintArr(stream, CHAR, "%c", dim, shp, a);
}

/* Functions which prints using user-defined format */
void ARRAYIO__PrintBoolArrayFormat( FILE *stream, string format, int dim, int * shp, bool * a)
{
  PrintArr(stream, BOOL, format, dim, shp, a);
}

void ARRAYIO__PrintDoubleArrayFormat( FILE *stream, string format, int dim, int * shp, double * a)
{
  PrintArr(stream, DOUBLE, format, dim, shp, a);
}

void ARRAYIO__PrintFloatArrayFormat( FILE *stream, string format, int dim, int * shp, float * a)
{
  PrintArr(stream, FLOAT, format, dim, shp, a);
}

void ARRAYIO__PrintByteArrayFormat( FILE *stream, string format, int dim, int * shp, char * a)
{
  PrintArr(stream, BYTE, format, dim, shp, a);
}

void ARRAYIO__PrintShortArrayFormat( FILE *stream, string format, int dim, int * shp, short * a)
{
  PrintArr(stream, SHORT, format, dim, shp, a);
}

void ARRAYIO__PrintIntArrayFormat( FILE *stream, string format, int dim, int * shp,	int * a)
{
  PrintArr(stream, INT, format, dim, shp, a);
}

void ARRAYIO__PrintLongArrayFormat( FILE *stream, string format, int dim, int * shp, long * a)
{
  PrintArr(stream, LONG, format, dim, shp, a);
}

void ARRAYIO__PrintLonglongArrayFormat( FILE *stream, string format, int dim, int * shp, long long * a)
{
  PrintArr(stream, LONGLONG, format, dim, shp, a);
}

void ARRAYIO__PrintUbyteArrayFormat( FILE *stream, string format, int dim, int * shp, unsigned char * a)
{
  PrintArr(stream, UBYTE, format, dim, shp, a);
}

void ARRAYIO__PrintUshortArrayFormat( FILE *stream, string format, int dim, int * shp, unsigned short * a)
{
  PrintArr(stream, USHORT, format, dim, shp, a);
}

void ARRAYIO__PrintUintArrayFormat( FILE *stream, string format, int dim, int * shp, unsigned int * a)
{
  PrintArr(stream, UINT, format, dim, shp, a);
}

void ARRAYIO__PrintUlongArrayFormat( FILE *stream, string format, int dim, int * shp, unsigned long * a)
{
  PrintArr(stream, ULONG, format, dim, shp, a);
}

void ARRAYIO__PrintUlonglongArrayFormat( FILE *stream, string format, int dim, int * shp, unsigned long long * a)
{
  PrintArr(stream, ULONGLONG, format, dim, shp, a);
}

void ARRAYIO__PrintCharArrayFormat( FILE *stream, string format, int dim, int * shp, char * a)
{
  PrintArr(stream, CHAR, format, dim, shp, a);
}
