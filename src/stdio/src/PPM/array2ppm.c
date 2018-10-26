#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sac.h"

typedef char* string;

#define array_nt  (array, T_OLD((AKD, (NHD, (NUQ, )))))

void SAC_PPM_array2ppm( FILE *fp,
                        SAC_ND_PARAM_in_nodesc( array_nt, int),
                        int shape[2],
                        bool binary)
{
  const int w = shape[1];
  const int h = shape[0];
  int i, j;

  /*
   * ASCII output
   */
  if ( binary == false) {
    fprintf(fp, "P3\n");

    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for(i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
        fprintf(fp, "%d %d %d", SAC_ND_A_FIELD(array_nt)[(i*w+j)*3],
                                SAC_ND_A_FIELD(array_nt)[(i*w+j)*3+1],
                                SAC_ND_A_FIELD(array_nt)[(i*w+j)*3+2]);

        if (j != w-1) {
          fprintf(fp, " ");
        }
      }
      fprintf(fp, "\n");
    }

  }
  /*
   * Binary output
   */
  else {
    fprintf(fp, "P6\n");

    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for(i = 0; i < h * w * 3; i++) {
      fprintf(fp, "%c", SAC_ND_A_FIELD(array_nt)[i]);
    }
  }
}
         
