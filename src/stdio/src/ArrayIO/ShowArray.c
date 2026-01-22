/*
 * Implementation of printing functions for Arrays as used in ArrayIO,
 * conforming with ISO Standard APL N8485.
 * The show() functions print data only - no rank, shape, or decorators.
 */

#include "ArrayIO.h"

static
void ShowArr(FILE *stream, string fmt, sac_int dim, sac_int *shp, char *a)
{
    // Introduce new lines at end of ultimate and penultimate dimensions
    sac_int element_count;
    sac_int rownums, colnums, planenums;
    sac_int rowoffset = 0;

    planenums = 1;
    for (sac_int i = 0; i < (dim - 2); i++) {
        planenums = planenums * shp[i];
    }

    if (dim == 0) {
        // Show scalar
        fprintf(stream, fmt, a[0]);
        // End row with new line
        fprintf(stream, "\n");
    } else {
        colnums = shp[dim - 1];
        if (dim >= 2) {
            // Row count for matrix and tensor
            rownums = shp[dim - 2];
        } else {
            // Vector row count
            rownums = 1;
        }

        element_count = planenums * colnums * rownums;

        if (element_count != 0) {
            // No output for empty array
            for (sac_int planenum = 0; planenum < planenums; planenum++) {
                for (sac_int rownum = 0; rownum < rownums; rownum++) {
                    for (sac_int colnum = 0; colnum < colnums; colnum++) {
                        // Format one row
                        fprintf(stream, fmt, a[rowoffset + colnum]);
                    }

                    // End row with new line
                    fprintf(stream, "\n");

                    if ((rownum == (rownums - 1)) && (planenum != (planenums - 1))) {
                        // End all but last plane with new line
                        fprintf(stream, "\n");
                    }

                    rowoffset += colnums;
                }
            }
        }
    }
}

void ARRAYIO__ShowCharArray(FILE *stream, sac_int dim, sac_int *shp, char *a)
{
    ShowArr(stream, CHAR, "%c", dim, shp, a);
}
