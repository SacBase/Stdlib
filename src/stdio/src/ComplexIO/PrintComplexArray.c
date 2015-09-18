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

#define COMPLEX     1

typedef char* string;
typedef double complex[2];

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
void PrintArrDSM(FILE *stream, int typeflag, string format, int dim, int * shp, void *a, bool is_distr, unsigned long arr_offset, unsigned long elems_first_nodes)
#else /* defined(SAC_BACKEND_DISTMEM) */
void PrintArr(FILE *stream, int typeflag, string format, int dim, int * shp, void *a)
#endif /* defined(SAC_BACKEND_DISTMEM) */
{
  int i,n, element_count;
  char *space=" ";
  int *index;

  #ifdef SAC_BACKEND_DISTMEM
    // TODO: Remove
    if (is_distr) {
      fprintf(stream, "DSM PrintArr from node %zd\n", SAC_DISTMEM_rank);
    } else {
      fprintf(stream, "Non-DSM PrintArr from node %zd\n", SAC_DISTMEM_rank);
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
      case COMPLEX:
        fprintf(stream, format, (*((complex *)a))[0], (*((complex *)a))[1]);
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

        while (index[n] < shp[dim-1]) {

          #ifdef SAC_BACKEND_DISTMEM
            if (is_distr) {
               fprintf(stream, format, 
                  *(SAC_DISTMEM_ELEM_POINTER(arr_offset, int, elems_first_nodes, Index2Offset(dim,shp,index))));
            } else {
          #endif /* defined(SAC_BACKEND_DISTMEM) */

          switch(typeflag) {
          case COMPLEX:
            fprintf(stream, format, 
	    	(((complex *)a)[Index2Offset(dim,shp,index)])[0], (((complex *)a)[Index2Offset(dim,shp,index)])[1]);
            break;
          }

          #ifdef SAC_BACKEND_DISTMEM
          } /* else */
          #endif /* defined(SAC_BACKEND_DISTMEM) */

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
  }

}

#ifdef SAC_BACKEND_DISTMEM
//FIXME: For now we only support dsm int arrays
static
void PrintArr(FILE *stream, int typeflag, string format, int dim, int * shp, void *a) {
  PrintArrDSM( stream, typeflag, format, dim, shp, a, FALSE, 0, 0);
}
#endif /* defined(SAC_BACKEND_DISTMEM) */

#ifdef SAC_BACKEND_DISTMEM
void COMPLEXIO__PrintComplexArray( FILE *stream, int dim, int * shp, complex * a, bool is_distr, unsigned long arr_offset, unsigned long elems_first_nodes)
#else /* defined(SAC_BACKEND_DISTMEM) */
void COMPLEXIO__PrintComplexArray( FILE *stream, int dim, int * shp, complex * a)
#endif /* defined(SAC_BACKEND_DISTMEM) */
{
  PrintArr(stream, COMPLEX, "(%.g, %.g) ", dim, shp, a);
}

#ifdef SAC_BACKEND_DISTMEM
void COMPLEXIO__PrintComplexArrayFormat( FILE *stream, string format, int dim, int * shp, complex * a, bool is_distr, unsigned long arr_offset, unsigned long elems_first_nodes)
#else /* defined(SAC_BACKEND_DISTMEM) */
void COMPLEXIO__PrintComplexArrayFormat( FILE *stream, string format, int dim, int * shp, complex * a)
#endif /* defined(SAC_BACKEND_DISTMEM) */
{
  PrintArr(stream, COMPLEX, format, dim, shp, a);
}
