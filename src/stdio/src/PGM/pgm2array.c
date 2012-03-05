/*
 * Implement reading of PGM images for SAC.
 * Support all details of the PGM specification:
 *  - both binary and ASCII representation PGM images.
 *  - both 8-bit and 16-bit pixel values.
 *  - comments in PGM files, even in weird places.
 * Support large PGM data efficiently.
 * Detect all invalid data conditions such as image
 * dimensions which exceed a 32-bit address space.
 */

#include <stdio.h>
#include <stdlib.h>
#include "sac.h"

static int *read_pgm_int(char *fn, int *width_ptr, int *height_ptr,
                         int *maxval_ptr);

#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void read_pgm(SAC_ND_PARAM_out(array_nt, int), int *maxval, char *fn)
{
  SAC_ND_DECL__DATA(ret_nt, int,)
  SAC_ND_DECL__DESC(ret_nt,)
  int width = 0;
  int height = 0;
  int *intarray = read_pgm_int(fn, &width, &height, maxval);
  int num_dims = 2;

  int SAC_ND_A_MIRROR_DIM(ret_nt) = num_dims;

  SAC_ND_ALLOC__DESC(ret_nt, num_dims)
  SAC_ND_SET__RC(ret_nt, 1) SAC_ND_A_DESC_SHAPE(ret_nt, 0) = height;
  SAC_ND_A_DESC_SHAPE(ret_nt, 1) = width;
  SAC_ND_A_DESC_SIZE(ret_nt) = width * height;
  SAC_ND_A_FIELD(ret_nt) = intarray;
  SAC_ND_RET_out(array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt

#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define MAX_PGM_BYTE_VAL        255
#define MAX_PGM_VAL             65535

#if defined(_IO_getc_unlocked)
#define myget(f)      _IO_getc_unlocked(f)
#else
#define myget(f)      getc(f)
#endif

/* Read the next character from the input stream 'fp'.
 */
#define next()        do { c = myget(fp); } while (0)

/* Ignore comments.
 * Skip the rest of the line and ignore more comments until 
 * the first character of the next line is not a comment character.
 */
#define comment()                                          \
        do {                                               \
          do {                                             \
            next();                                        \
          } while (c != '\n' && c != '\r' && c != EOF);    \
          if (c == '\r') { next(); }                       \
          if (c == '\n') { next(); }                       \
        } while (c == '#')


/* Expect to find a whitespace character or a comment delimiter.
 * Skip all whitespace characters and comments.
 */
#define skip()                                 \
        if (c != '#' && !isspace(c)) {         \
          if (c == EOF) {                      \
            goto eof;                          \
          } else {                             \
            goto bad;                          \
          }                                    \
        } else do {                            \
          if (c == '#') {                      \
            comment();                         \
          } else {                             \
            next();                            \
          }                                    \
        } while (c == '#' || isspace(c))

/* Expect to find a digit.
 * Convert this and subsequent digits to an unsigned number in 'n'.
 */
#define num(n)                                 \
        if (!isdigit(c)) {                     \
          goto bad;                            \
        } else {                               \
          n = c - '0';                         \
          next();                              \
          while (isdigit(c)) {                 \
            n = n * 10 + (c - '0');            \
            next();                            \
          }                                    \
        }


static int *read_pgm_int(char *fn,
                         int *width_ptr, int *height_ptr, int *maxval_ptr)
{
  int *data = NULL;
  FILE *fp;
  size_t width = 0, height = 0, pixelcount = 0;
  unsigned maxval = 0, val = 0;
  size_t i;
  int hdr[2];
  /* 'c' is used by the macros to store the next input character. */
  int c;

  fp = fopen(fn, "rb");
  if (fp == NULL)
  {
    SAC_RuntimeError("read_pgm: Cannot open \"%s\": %s", fn, strerror(errno));
    return NULL;
  }

  hdr[0] = myget(fp);
  hdr[1] = myget(fp);
  if (hdr[0] != 'P' || (hdr[1] != '2' && hdr[1] != '5'))
  {
    SAC_RuntimeError("read_pgm: File \"%s\" is not in PGM format", fn);
    goto done;
  }

  next();
  skip();
  num(width);
  skip();
  num(height);
  skip();
  num(maxval);

  if (width == 0 || height == 0 || maxval > MAX_PGM_VAL)
  {
    SAC_RuntimeError("read_pgm: File \"%s\" has invalid PGM header", fn);
    goto done;
  }

  pixelcount = width * height;
  if (width > INT_MAX || height > INT_MAX ||
      pixelcount > INT_MAX || pixelcount / width != height)
  {
    SAC_RuntimeError(
      "read_pgm: Image dimensions of \"%s\" (%u * %u = %u) exceed INT_MAX",
      fn, width, height, pixelcount);
    goto done;
  }

  data = SAC_MALLOC(pixelcount * sizeof(int));

  if (hdr[1] == '2')
  {
    for (i = 0; i < pixelcount; ++i)
    {
      skip();
      num(val);
      data[i] = (int) val;
    }
  }
  else if (hdr[1] == '5')
  {
    /* maxval may be followed by comments. */
    if (c == '#') {
      comment();
    }
    /* exactly one space character separates the header from the data. */
    if (!isspace(c)) {
      goto bad;
    }
    if (maxval <= MAX_PGM_BYTE_VAL)
    {
      for (i = 0; i < pixelcount; ++i)
      {
        data[i] = myget(fp);
      }
    }
    else
    {
      for (i = 0; i < pixelcount; ++i)
      {
        int b1 = myget(fp);
        int b2 = myget(fp);

        data[i] = ((b1 << 8) | b2);
      }
    }
  }

  if (ferror(fp)) {
    goto err;
  }
  if (feof(fp) && (hdr[1] != '2' || val > MAX_PGM_VAL)) {
    goto eof;
  }

done:
  *width_ptr = width;
  *height_ptr = height;
  *maxval_ptr = maxval;
  return data;

bad:
  if (c != EOF && !ferror(fp) && !feof(fp)) {
    SAC_RuntimeError("Invalid PGM data in \"%s\".", fn);
    goto done;
  }

err:
  if (ferror(fp)) {
    SAC_RuntimeError("read_pgm: Errors while reading PGM data from \"%s\".",
                     fn);
    goto done;
  }

eof:
  SAC_RuntimeError(
    "read_pgm: Premature end-of-file while reading PGM data from \"%s\".", fn);
  goto done;
}

