/*
 *  Implementation of standard module FibrePrint.
 */


#include <stdio.h>
#include <string.h>



#define INT    1
#define FLOAT  2
#define DOUBLE 3


#define INDENT(stream, ind)                     \
{                                               \
   int q;                                       \
   for (q=0; q<ind; q++) fprintf(stream, " ");  \
 }




int FibreWriteAll(FILE *stream, int dim, int *shp, void *arr, 
                  int typeflag, int indent, int done)
{
  int i;
  
  INDENT(stream, indent);
  fprintf(stream, "[ 0,%d:\n", (*shp) - 1);
    
  if (dim==1)
  {
    for (i=0; i<*shp; i++)
    {
      switch (typeflag)
      {
      case INT:
        INDENT(stream, indent+1);
        fprintf(stream, "%i\n", ((int*)arr)[done + i]);
        break;
      case FLOAT:
         if((((float*)arr)[done + i]) >= 0) {
          INDENT(stream, indent+4);
        } else {
          INDENT(stream, indent+3);
        }
        fprintf(stream, "%e\n", ((float*)arr)[done + i]);
        break;
      case DOUBLE:
        if((((double*)arr)[done + i]) >= 0) {
          INDENT(stream, indent+4);
        } else {
          INDENT(stream, indent+3);
        }
        fprintf(stream, "%e\n", ((double*)arr)[done + i]);
        break;
      }    
    }
    done+=*shp;
  }
  else
  {
    for (i=0; i<*shp; i++)
    {
      switch (typeflag)
      {
      case INT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((int*)arr),
                             typeflag, indent+1, done);
        break;
      case FLOAT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((float*)arr),
                             typeflag, indent+1, done);
        break;
      case DOUBLE:
        done = FibreWriteAll(stream, dim-1, shp+1, ((double*)arr),
                             typeflag, indent+1, done);
        break;
      }    
    }
  }
    
  INDENT(stream, indent);
  fprintf(stream, "]\n");
  
  return( done);
}






void FibrePrintIntArray( FILE *stream, int dim, int *shape, int *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, INT, 0, 0);
}


void FibrePrintFloatArray( FILE *stream, int dim, int *shape, float *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, FLOAT, 0, 0);
}


void FibrePrintDoubleArray( FILE *stream, int dim, int *shape, double *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, DOUBLE, 0, 0);
}





