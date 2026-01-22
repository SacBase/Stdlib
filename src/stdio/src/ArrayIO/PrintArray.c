/*
 * Implementation of printing functions for Arrays as used in ArrayIO.
 */

#include "ArrayIO.h"

#define PRINT_CASE(constant, ctype, ftype)                                     \
case constant:                                                                 \
    fprintf(stream, format, (ftype)((ctype *)a)[Index2Offset(dim, shp, index)]);\
    break;

#define PRINT_FUNS(name_prefix, ctype, constant, default_format)               \
void ARRAYIO__Print##name_prefix##Array(FILE *stream, sac_int dim,             \
                                        sac_int *shp, ctype *a)                \
{                                                                              \
    PrintArr(stream, constant, default_format, dim, shp, a);                   \
}                                                                              \
                                                                               \
void ARRAYIO__Print##name_prefix##ArrayFormat(FILE *stream, string format,     \
                                           sac_int dim, sac_int *shp, ctype *a)\
{                                                                              \
    PrintArr(stream, constant, format, dim, shp, a);                           \
}

static
sac_int Index2Offset(sac_int dim, sac_int *shp, sac_int *index)
{
    sac_int offset = 0;

    for (sac_int i = 0; i < dim; i++) {
        sac_int fact = 1;

        for (sac_int n = i + 1; n < dim; n++) {
           fact *= shp[n];
        }

        offset += index[i] * fact;
    }

    return offset;
}

static void PrintArr(FILE *stream, sac_int typeflag, string format,
                     sac_int dim, sac_int *shp, void *a)
{
    fprintf(stream, "Dimension: %2"PRIisac"\n", dim);
    fprintf(stream, "Shape    : <");

    sac_int element_count = 1;
    for (sac_int i = 0; i < dim;) {
        fprintf(stream, " %2"PRIisac, shp[i]);
        element_count *= shp[i];
        i += 1;

        if (i < dim) {
            fprintf(stream, ",");
        }
    }

    fprintf(stream, ">\n");

    /*
     * Now, element_count carries the total number of elements
     * to be expected behind *a!
     */
    if(dim == 0) {
        switch(typeflag) {
        case BOOL:
            fprintf(stream, format, ((bool *)a)[0]);
            break;
        case BYTE:
            fprintf(stream, format, ((char *)a)[0]);
            break;
        case SHORT:
            fprintf(stream, format, ((short *)a)[0]);
            break;
        case INT:
            fprintf(stream, format, ((sac_int *)a)[0]);
            break;
        case LONG:
            fprintf(stream, format, ((long *)a)[0]);
            break;
        case LONGLONG:
            fprintf(stream, format, ((long long *)a)[0]);
            break;
        case UBYTE:
            fprintf(stream, format, ((unsigned char *)a)[0]);
            break;
        case USHORT:
            fprintf(stream, format, ((unsigned short *)a)[0]);
            break;
        case UINT:
            fprintf(stream, format, ((unsigned int *)a)[0]);
            break;
        case ULONG:
            fprintf(stream, format, ((unsigned long *)a)[0]);
            break;
        case ULONGLONG:
            fprintf(stream, format, ((unsigned long long *)a)[0]);
            break;
        case FLOAT:
            fprintf(stream, format, (double)((float *)a)[0]);
            break;
        case DOUBLE:
            fprintf(stream, format, ((double *)a)[0]);
            break;
        case CHAR:
            // TODO: Isn't CHAR compiled to unsigned char?
            fprintf(stream, format, ((char *)a)[0]);
            break;
        default:
            SAC_RuntimeError("illegal typeflag %d", typeflag);
        }

        fprintf(stream, "\n");
    } else if (dim > 0) {
        if (element_count == 0) {
            fprintf(stream, "<>\n");
        } else {
            sac_int *index = SAC_MALLOC((size_t)dim * sizeof(sac_int));
            for (sac_int i = 0; i < dim; i++) {
                index[i] = 0;
            }

            sac_int n = dim - 1;

            /*
             * Now, we have:
             *     index == [0,...,0]
             *               0,...,n
             */
            do {
                if ((dim % 2) == 1) {
                    fprintf(stream, "<");
                } else {
                    fprintf(stream, "|");
                }

                while (index[n] < shp[dim - 1]) {
                    switch(typeflag) {
                        PRINT_CASE(BOOL, bool, bool)
                        PRINT_CASE(BYTE, char, char)
                        PRINT_CASE(SHORT, short, short)
                        PRINT_CASE(INT, sac_int, sac_int)
                        PRINT_CASE(LONG, long, long)
                        PRINT_CASE(LONGLONG, long long, long long)
                        PRINT_CASE(UBYTE, unsigned char, unsigned char)
                        PRINT_CASE(USHORT, unsigned short, unsigned short)
                        PRINT_CASE(UINT, unsigned int, unsigned int)
                        PRINT_CASE(ULONG, unsigned long, unsigned long)
                        PRINT_CASE(ULONGLONG, unsigned long long, unsigned long long)
                        PRINT_CASE(FLOAT, float, double)
                        PRINT_CASE(DOUBLE, double, double)
                        PRINT_CASE(CHAR, char, char)  /* TODO: Isn't CHAR compiled to unsigned char? */
                        default:
                            SAC_RuntimeError ("illegal typeflag %d", typeflag);
                    }

                    index[n] += 1;
                }

                if ((dim % 2) == 1) {
                    index[n] = 0;
                    fprintf(stream, "> ");
                    n -= 1;
                } else {
                    fprintf(stream, "| ");
                }

                char *space = " ";
                while((n > 0) && (index[n] >= (shp[n] - 1))) {
                    index[n] = 0;
                    n -= 2;

                    if (n < 0) {
                        space = "\n";
                        n = ((dim - 2) / 2) * 2;
                    }

                    fprintf(stream, "%s", space);
                }

                if((n >= 0) && (index[n] < (shp[n] - 1))) {
                    index[n] += 1;
                    n = dim - 1;
                    space = " ";
                }
            } while(n > 0);

            fprintf(stream, "\n");
            SAC_FREE(index);
        }
    } else {
        SAC_RuntimeError ("Dimension is less than 0, aborting!");
    }
}

PRINT_FUNS(Bool, bool, BOOL, "%2i ")
PRINT_FUNS(Double, double, DOUBLE, "%e ")
PRINT_FUNS(Float, float, FLOAT, "%4f ")
PRINT_FUNS(Byte, char, BYTE, "%2hd ")
PRINT_FUNS(Short, short, SHORT, "%2hd ")
PRINT_FUNS(Int, sac_int, INT, "%2"PRIisac" ")
PRINT_FUNS(Long, long, LONG, "%2ld ")
PRINT_FUNS(Longlong, long long, LONGLONG, "%2lld ")
PRINT_FUNS(Ubyte, unsigned char, UBYTE, "%2hu ")
PRINT_FUNS(Ushort, unsigned short, USHORT, "%2hu ")
PRINT_FUNS(Uint, unsigned int, UINT, "%2u ")
PRINT_FUNS(Ulong, unsigned long, ULONG, "%2lu ")
PRINT_FUNS(Ulonglong, unsigned long long, ULONGLONG, "%2llu ")
PRINT_FUNS(Char, char, CHAR, "%c")
