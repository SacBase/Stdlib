#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sac.h"

typedef char* string;

#define array_nt  (array, T_OLD((AKD, (NHD, (NUQ, )))))
#define string_nt (str,   T_OLD((SCL, (HID, (NUQ, )))))
#define shape_nt  (shape, T_OLD((AKS, (NHD, (NUQ, )))))
#define ascii_nt  (ascii, T_OLD((SCL, (HID, (NUQ, )))))

#define MAXLINE 80

void SAC_PPM_array2ppm( SAC_ND_PARAM_in_nodesc( string_nt, string),
                        SAC_ND_PARAM_in_nodesc( array_nt, int),
                        SAC_ND_PARAM_in_nodesc( shape_nt, int),
                        SAC_ND_PARAM_in_nodesc( ascii_nt, int))
{
  FILE *fp;

  int w = SAC_ND_A_FIELD( shape_nt)[1];
  int h = SAC_ND_A_FIELD( shape_nt)[0];

  if ( strncmp( NT_NAME( string_nt), "stdout", 6) == 0) {
    fp = stdout;
  } else {
    fp = fopen( NT_NAME( string_nt), "w+");
  }

  /*
   * ASCII output
   */
  if ( NT_NAME( ascii_nt) == 1) {
    fprintf(fp, "P3\n");

    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");

    for(int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
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

    for(int i = 0; i < h * w * 3; i++) {
      fprintf(fp, "%c", SAC_ND_A_FIELD(array_nt)[i]);
    }
  }

  if (fp != stdout) {
    fclose(fp);
  }
}
         
