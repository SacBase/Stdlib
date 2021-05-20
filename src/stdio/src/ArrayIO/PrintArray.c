/*
 *  Implementation of printing functions for Arrays as used in ArrayIO
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef SAC_BACKEND_DISTMEM
#define SAC_DO_DISTMEM 1
#else /* defined(SAC_BACKEND_DISTMEM) */
#define SAC_DO_DISTMEM 0
#endif /* defined(SAC_BACKEND_DISTMEM) */
#include "sac.h"
#undef SAC_DO_DISTMEM


#define INT        1
#define FLOAT      2
#define DOUBLE     3
#define CHAR       4
#define BOOL       5
#define BYTE       6
#define SHORT      7
#define LONG       8
#define LONGLONG   9
#define UBYTE      10
#define USHORT     11
#define UINT       12
#define ULONG      13
#define ULONGLONG  14

/*
 * Code generation macros
 */

#ifdef SAC_BACKEND_DISTMEM

#define PRINT_CASE( constant, ctype, ftype)                                       \
  case constant:                                                                  \
    if (is_distr) {                                                               \
      fprintf(stream, format,                                                     \
       (ftype)*(SAC_DISTMEM_ELEM_POINTER(arr_offset, ctype, elems_first_nodes,    \
                                         Index2Offset( dim, shp, index))));       \
    } else {                                                                      \
      fprintf(stream, format,                                                     \
        (ftype)((ctype *)a)[Index2Offset(dim,shp,index)]);                        \
    }                                                                             \
    break;

#define PRINT_FUNS( name_prefix, ctype, constant, default_format)                 \
void ARRAYIO__Print##name_prefix##Array( FILE *stream, int dim,                   \
                                         int * shp, ctype * a,                    \
                                         bool is_distr, unsigned long arr_offset, \
                                         unsigned long elems_first_nodes)         \
{                                                                                 \
  PrintArr(stream, constant, default_format, dim, shp, a,                         \
           is_distr, arr_offset, elems_first_nodes);                              \
}                                                                                 \
                                                                                  \
void ARRAYIO__Print##name_prefix##ArrayFormat( FILE *stream, string format, int dim,    \
                                         int * shp, ctype * a,                          \
                                         bool is_distr, unsigned long arr_offset,       \
                                         unsigned long elems_first_nodes)               \
{                                                                                       \
  PrintArr(stream, constant, format, dim, shp, a,                                       \
           is_distr, arr_offset, elems_first_nodes);                                    \
}

#else /* defined(SAC_BACKEND_DISTMEM) */

#define PRINT_CASE( constant, ctype, ftype)                  \
  case constant:                                             \
    fprintf(stream, format,                                  \
      (ftype)((ctype *)a)[Index2Offset( dim, shp, index)]);  \
    break;

#define PRINT_FUNS( name_prefix, ctype, constant, default_format)  \
void ARRAYIO__Print##name_prefix##Array( FILE *stream, int dim,    \
                                         int * shp, ctype * a)     \
{                                                                  \
  PrintArr(stream, constant, default_format, dim, shp, a);         \
}                                                                  \
                                                                   \
void ARRAYIO__Print##name_prefix##ArrayFormat( FILE *stream, string format, int dim,   \
                                               int * shp, ctype * a)                   \
{                                                                                      \
  PrintArr(stream, constant, format, dim, shp, a);                                     \
}

#endif /* defined(SAC_BACKEND_DISTMEM) */


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
#ifdef SAC_BACKEND_DISTMEM
void PrintArr(FILE *stream, int typeflag, string format, int dim, int * shp, void *a, bool is_distr, unsigned long arr_offset, unsigned long elems_first_nodes)
#else /* defined(SAC_BACKEND_DISTMEM) */
void PrintArr(FILE *stream, int typeflag, string format, int dim, int * shp, void *a)
#endif /* defined(SAC_BACKEND_DISTMEM) */
{
  int i,n, element_count;
  char *space=" ";
  int *index;

  #ifdef SAC_BACKEND_DISTMEM
    // TODO: Remove this when this module is verified to work.
    if (is_distr) {
      fprintf(stderr, "DSM PrintArr from node %zd\n", SAC_DISTMEM_rank);
    } else {
      fprintf(stderr, "Non-DSM PrintArr from node %zd\n", SAC_DISTMEM_rank);
    }
  #endif

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
        fprintf(stream, format , ((bool *)a)[0]);
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
        fprintf(stream, format, (double)((float *)a)[0]);
        break;
      case DOUBLE:
        fprintf(stream, format, ((double *)a)[0]);
        break;
      case CHAR:
        fprintf(stream, format, ((char *)a)[0]); /* TODO: Isn't CHAR compiled to unsigned char? */
        break;
      }
   fprintf(stream,"\n");

  } else if (dim > 0) {
    if (element_count == 0) {
      fprintf(stream, "<>\n");
    } else {

      index = SAC_MALLOC (dim * sizeof (int));
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
            PRINT_CASE( BOOL, bool, bool)
            PRINT_CASE( BYTE, char, char)
            PRINT_CASE( SHORT, short, short)
            PRINT_CASE( INT, int, int)
            PRINT_CASE( LONG, long, long)
            PRINT_CASE( LONGLONG, long long, long long)
            PRINT_CASE( UBYTE, unsigned char, unsigned char)
            PRINT_CASE( USHORT, unsigned short, unsigned short)
            PRINT_CASE( UINT, unsigned int, unsigned int)
            PRINT_CASE( ULONG, unsigned long, unsigned long)
            PRINT_CASE( ULONGLONG, unsigned long long, unsigned long long)
            PRINT_CASE( FLOAT, float, double)
            PRINT_CASE( DOUBLE, double, double)
            PRINT_CASE( CHAR, char, char)  /* TODO: Isn't CHAR compiled to unsigned char? */
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


PRINT_FUNS( Bool, bool, BOOL, "%2i ")

PRINT_FUNS( Double, double, DOUBLE, "%e ")

PRINT_FUNS( Float, float, FLOAT, "%4f ")

PRINT_FUNS( Byte, char, BYTE, "%2hd ")

PRINT_FUNS( Short, short, SHORT, "%2hd ")

PRINT_FUNS( Int, int, INT, "%2i ")

PRINT_FUNS( Long, long, LONG, "%2ld ")

PRINT_FUNS( Longlong, long long, LONGLONG, "%2lld ")

PRINT_FUNS( Ubyte, unsigned char, UBYTE, "%2hu ")

PRINT_FUNS( Ushort, unsigned short, USHORT, "%2hu ")

PRINT_FUNS( Uint, unsigned int, UINT, "%2u ")

PRINT_FUNS( Ulong, unsigned long, ULONG, "%2lu ")

PRINT_FUNS( Ulonglong, unsigned long long, ULONGLONG, "%2llu ")

PRINT_FUNS( Char, char, CHAR, "%c")

