/*
 *  Implementation of standard module FibrePrint.
 */


#include <stdio.h>
#include <string.h>

#include "../../../structures/src/StringArray/StringArray.h"

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    STRING,
    BYTE,
    SHORT,
    LONG,
    LONGLONG,
    UBYTE,
    USHORT,
    UINT,
    ULONG,
    ULONGLONG
} typeflag_t;

#define INDENT(stream, ind)                     \
{                                               \
   int q;                                       \
   for (q=0; q<ind; q++) fprintf(stream, " ");  \
 }


sac_int FibreWriteAll(FILE *stream, sac_int dim, sac_int *shp, void *arr,
                   typeflag_t typeflag, int indent, sac_int done)
{
  sac_int i;

  INDENT(stream, indent);
  fprintf(stream, "[ 0,%" PRIisac ":\n", (*shp) - 1);

  if (dim==1)
  {
    for (i=0; i<*shp; i++)
    {
      switch (typeflag)
      {
      case BYTE:
        INDENT(stream, indent+1);
        fprintf(stream, "%hhd\n", ((char*)arr)[done + i]);
        break;
      case SHORT:
        INDENT(stream, indent+1);
        fprintf(stream, "%hd\n", ((short*)arr)[done + i]);
        break;
      case INT:
        INDENT(stream, indent+1);
        fprintf(stream, "%" PRIisac "\n", ((sac_int*)arr)[done + i]);
        break;
      case LONG:
        INDENT(stream, indent+1);
        fprintf(stream, "%ld\n", ((long*)arr)[done + i]);
        break;
      case LONGLONG:
        INDENT(stream, indent+1);
        fprintf(stream, "%lld\n", ((long long*)arr)[done + i]);
        break;
      case UBYTE:
        INDENT(stream, indent+1);
        fprintf(stream, "%hhu\n", ((unsigned char*)arr)[done + i]);
        break;
      case USHORT:
        INDENT(stream, indent+1);
        fprintf(stream, "%hu\n", ((unsigned short*)arr)[done + i]);
        break;
      case UINT:
        INDENT(stream, indent+1);
        fprintf(stream, "%u\n", ((unsigned int*)arr)[done + i]);
        break;
      case ULONG:
        INDENT(stream, indent+1);
        fprintf(stream, "%lu\n", ((unsigned long*)arr)[done + i]);
        break;
      case ULONGLONG:
        INDENT(stream, indent+1);
        fprintf(stream, "%llu\n", ((unsigned long long*)arr)[done + i]);
        break;
      case FLOAT:
         if((((float*)arr)[done + i]) >= 0) {
          INDENT(stream, indent+4);
        } else {
          INDENT(stream, indent+3);
        }
        fprintf(stream, "%f\n", (double)((float*)arr)[done + i]);
        break;
      case DOUBLE:
        if((((double*)arr)[done + i]) >= 0) {
          INDENT(stream, indent+4);
        } else {
          INDENT(stream, indent+3);
        }
        fprintf(stream, "%f\n", ((double*)arr)[done + i]);
        break;
      case STRING:
        INDENT(stream, indent+1);
        const char *str = SACARGgetSharedData(SAC__String__string,
                                              ((array*)arr)->elems[done + i]);
        fprintf(stream, "\"%s\"\n", str);
        break;
      default:
        SAC_RuntimeError ("illegal typeflag (int)%d", typeflag);
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
      case BYTE:
        done = FibreWriteAll(stream, dim-1, shp+1, ((char*)arr),
                             typeflag, indent+1, done);
        break;
      case SHORT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((short*)arr),
                             typeflag, indent+1, done);
        break;
      case INT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((sac_int*)arr),
                             typeflag, indent+1, done);
        break;
      case LONG:
        done = FibreWriteAll(stream, dim-1, shp+1, ((long*)arr),
                             typeflag, indent+1, done);
        break;
      case LONGLONG:
        done = FibreWriteAll(stream, dim-1, shp+1, ((long long*)arr),
                             typeflag, indent+1, done);
        break;
      case UBYTE:
        done = FibreWriteAll(stream, dim-1, shp+1, ((unsigned char*)arr),
                             typeflag, indent+1, done);
        break;
      case USHORT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((unsigned short*)arr),
                             typeflag, indent+1, done);
        break;
      case UINT:
        done = FibreWriteAll(stream, dim-1, shp+1, ((unsigned int*)arr),
                             typeflag, indent+1, done);
        break;
      case ULONG:
        done = FibreWriteAll(stream, dim-1, shp+1, ((unsigned long*)arr),
                             typeflag, indent+1, done);
        break;
      case ULONGLONG:
        done = FibreWriteAll(stream, dim-1, shp+1, ((unsigned long long*)arr),
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
      case STRING:
        done = FibreWriteAll(stream, dim-1, shp+1, ((array*)arr),
                             typeflag, indent+1, done);
        break;
      default:
        SAC_RuntimeError ("illegal typeflag %d", typeflag);
      }
    }
  }

  INDENT(stream, indent);
  fprintf(stream, "]\n");

  return( done);
}


void FibrePrintIntArray(FILE *stream, sac_int dim, sac_int *shape, sac_int *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, INT, 0, 0);
}


void FibrePrintFloatArray( FILE *stream, sac_int dim, sac_int *shape, float *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, FLOAT, 0, 0);
}


void FibrePrintDoubleArray( FILE *stream, sac_int dim, sac_int *shape, double *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, DOUBLE, 0, 0);
}

void FibrePrintStringArray( FILE *stream, sac_int dim, sac_int *shape, array *array)
{
  (void) FibreWriteAll(stream, dim, shape, array, STRING, 0, 0);
}

#define PRINTARR(type,alias,switchname)					     \
									     \
void FibrePrint##alias##Array( FILE *stream, sac_int dim, sac_int *shape, type *array) \
{									     \
  (void) FibreWriteAll(stream, dim, shape, array, switchname, 0, 0);	     \
}

PRINTARR(char, Byte, BYTE)
PRINTARR(short, Short, SHORT)
PRINTARR(long, Long, LONG)
PRINTARR(long long, Longlong, LONGLONG)
PRINTARR(unsigned char, Ubyte, UBYTE)
PRINTARR(unsigned short, Ushort, USHORT)
PRINTARR(unsigned int, Uint, UINT)
PRINTARR(unsigned long, Ulong, ULONG)
PRINTARR(unsigned long long, Ulonglong, ULONGLONG)
