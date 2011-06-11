#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sac.h"

#define array_nt  (array, T_OLD((AKD, (NHD, (NUQ, )))))

void SAC_PGM_array2pgm( FILE* fp,
                        SAC_ND_PARAM_in_nodesc( array_nt, int),
                        const int shape[2],
                        const bool binary)
{
  const int w = shape[1];
  const int h = shape[0];

  /*
   * ASCII output
   */
  if ( binary == false) {
    fprintf(fp, "P2\n");

    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for(int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        fprintf(fp, "%d", SAC_ND_A_FIELD(array_nt)[i*w+j]);

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
    fprintf(fp, "P5\n");

    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for(int i = 0; i < w * h; i++) {
      fprintf(fp, "%c", SAC_ND_A_FIELD(array_nt)[i]);
    }
  }

}
         
