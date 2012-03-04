/*
 * Implement writing PGM images for SAC.
 * Support saving in either binary or ASCII representation.
 * Support both 8-bit and 16-bit pixel values.
 * Detect when pixel data which lie outside of the valid range.
 * Support large PGM data efficiently.
 * Detect and report all errors.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "sac.h"

typedef char *string;

#define PGM_MAX_VAL      65535
#define PGM_MIN_VAL      0
#define PGM_MAX_BYTE_VAL 255
#define PGM_LINE         70

#define array_nt  (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define string_nt (str,   T_OLD((SCL, (HID, (NUQ, )))))

#if defined(_IO_putc_unlocked)
#define myput(c,f)      _IO_putc_unlocked(c,f)
#else
#define myput(c,f)      putc(c,f)
#endif

void write_pgm(SAC_ND_PARAM_in_nodesc(array_nt, int),
               const int shape[2],
               const bool binary, SAC_ND_PARAM_in_nodesc(string_nt, string))
{
  const char *filename = NT_NAME(string_nt);
  const int height = shape[0];
  const int width = shape[1];
  int *restrict int_array = SAC_ND_A_FIELD(array_nt);
  const int pixelcount = height * width;
  int min = PGM_MAX_VAL;
  int max = PGM_MIN_VAL;
  int maxval;
  FILE *fp;

  for (int i = 0; i < pixelcount; ++i)
  {
    if (min > int_array[i])
    {
      min = int_array[i];
    }
    if (max < int_array[i])
    {
      max = int_array[i];
    }
  }
  if (min < PGM_MIN_VAL)
  {
    SAC_RuntimeError("write_pgm: Image minimum %d is less than %d for %s\n",
                     min, PGM_MIN_VAL, filename);
  }
  if (max > PGM_MAX_VAL)
  {
    SAC_RuntimeError("write_pgm: Image maximum %d is more than %d for %s\n",
                     max, PGM_MAX_VAL, filename);
  }

  maxval = (max <= PGM_MAX_BYTE_VAL) ? PGM_MAX_BYTE_VAL : PGM_MAX_VAL;

  fp = fopen(filename, "wb");
  if (fp == NULL)
  {
    SAC_RuntimeError("write_pgm: Could not open %s for writing: %s",
                     filename, strerror(errno));
  }

  fprintf(fp, "P%c\n%d %d\n%d\n", binary ? '5' : '2', width, height, maxval);

  if (binary)
  {
    if (maxval <= PGM_MAX_BYTE_VAL)
    {
      for (int i = 0; i < pixelcount; ++i)
      {
        myput(int_array[i], fp);
      }
    }
    else
    {
      for (int i = 0; i < pixelcount; ++i)
      {
        unsigned char a = (unsigned char) (int_array[i] >> 8);
        unsigned char b = (unsigned char) (int_array[i] & 0xFF);

        myput(a, fp);
        myput(b, fp);
      }
    }
  }
  else
  {
    int col = 0;

    for (int i = 0; i < pixelcount; ++i)
    {
      unsigned char rep[20];
      int dig = 0;
      int num = int_array[i];

      while (num >= 10)
      {
        rep[dig++] = '0' + (num % 10);
        num /= 10;
      }
      rep[dig++] = '0' + num;
      if (col + dig >= PGM_LINE)
      {
        myput('\n', fp);
        col = 0;
      }
      else if (i)
      {
        myput(' ', fp);
        ++col;
      }
      col += dig;
      while (--dig >= 0)
      {
        myput(rep[dig], fp);
      }
    }
    if (col)
    {
      myput('\n', fp);
    }
  }

  if (ferror(fp))
  {
    SAC_RuntimeError("write_pgm: Errors while writing to %s: %s",
                     filename, strerror(errno));
  }

  fclose(fp);
}

