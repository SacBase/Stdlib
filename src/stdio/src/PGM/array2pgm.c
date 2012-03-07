/*
 * Implement writing PGM images for SAC.
 * Support saving in either binary or ASCII representation.
 * Support both 8-bit and 16-bit pixel values.
 * Detect when pixel data which lie outside of the valid range.
 * Support large PGM data efficiently.
 * Detect and report all errors.
 */

#include "sac_pgm.h"

PGM* SAC_PGM_new( const int shape[2], const int maxval,
                  const bool binary, FILE* fp)
{
  PGM* pgm = (PGM *) SAC_MALLOC( sizeof(PGM));
  pgm->width = shape[1];
  pgm->height = shape[0];
  pgm->maxval = maxval;
  pgm->kind = (binary) ? PGM_BINARY : PGM_TEXT;
  pgm->fp = fp;
  pgm->pos = ftell( fp );
  return pgm;
}

void SAC_PGM_write_header( PGM* pgm)
{
  if (pgm->width == 0 || pgm->height == 0 ||
      pgm->maxval < 1 || pgm->maxval > PGM_MAX_VAL)
  {
    SAC_RuntimeError( "SAC_PGM_create: Invalid PGM image dimensions (%zu, %zu, %zu).",
                     pgm->width, pgm->height, pgm->maxval);
  }
  fprintf( pgm->fp,
           "P%c\n"
           "%zu %zu\n"
           "%zu\n",
           pgm->kind,
           pgm->width,
           pgm->height,
           pgm->maxval);
  fflush( pgm->fp);
}

#define array_nt  (array, T_OLD((AUD, (NHD, (NUQ, )))))

void SAC_PGM_write_data( SAC_ND_PARAM_in_nodesc(array_nt, int),
                         PGM* pgm)
{
  int *restrict int_array = SAC_ND_A_FIELD(array_nt);
  const size_t pixelcount = pgm->height * pgm->width;
  size_t i = 0;

  if (pgm->kind == PGM_BINARY)
  {
    if (pgm->maxval <= PGM_MAX_BYTE_VAL)
    {
      for (i = 0; i < pixelcount; ++i)
      {
        unsigned char b = (unsigned char) (int_array[i] & 0xFF);

        if ((unsigned) int_array[i] > pgm->maxval) {
          goto bad;
        }

        myput(b, pgm->fp);
      }
    }
    else
    {
      for (i = 0; i < pixelcount; ++i)
      {
        unsigned char a = (unsigned char) ((int_array[i] >> 8) & 0xFF);
        unsigned char b = (unsigned char) (int_array[i] & 0xFF);

        if ((unsigned) int_array[i] > pgm->maxval) {
          goto bad;
        }

        myput(a, pgm->fp);
        myput(b, pgm->fp);
      }
    }
  }
  else
  {
    int col = 0;

    for (i = 0; i < pixelcount; ++i)
    {
      unsigned char rep[20];
      int dig = 0;
      int num = int_array[i];

      if ((unsigned) num > pgm->maxval) {
        goto bad;
      }

      while (num >= 10)
      {
        rep[dig++] = '0' + (num % 10);
        num /= 10;
      }
      rep[dig++] = '0' + num;
      if (col + dig >= PGM_MAX_LINE_SIZE)
      {
        myput('\n', pgm->fp);
        col = 0;
      }
      else if (i)
      {
        myput(' ', pgm->fp);
        ++col;
      }
      col += dig;
      while (--dig >= 0)
      {
        myput(rep[dig], pgm->fp);
      }
    }
    if (col)
    {
      myput('\n', pgm->fp);
    }
  }

bad:
  if (i < pixelcount && (unsigned) int_array[i] > pgm->maxval) {
    SAC_RuntimeError( "SAC_PGM_write_data: Invalid pixel %d at index [%zu,%zu].",
                      int_array[i],
                      (size_t) i % pgm->width,
                      (size_t) i / pgm->width);
  }
  else if (ferror( pgm->fp) || fflush( pgm->fp))
  {
    SAC_RuntimeError( "SAC_PGM_write_data: Errors while writing to file: %s",
                      strerror(errno));
  }
}

