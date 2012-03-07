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
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#include "sac.h"

typedef struct PGM {
  size_t width, height, maxval;
  int kind;
  long pos;
  FILE *fp;
} PGM;

#define MAX_PGM_BYTE_VAL        255
#define MAX_PGM_VAL             65535
#define PGM_BINARY              '5'
#define PGM_TEXT                '2'

/*
 * Because we access the file single-threaded
 * it is more efficient to use an unlocked version of getc.
 * We could also use the function 'getc_unlocked', but we
 * cannot easily detect whether this is supported by the current system.
 */
#if defined(_IO_getc_unlocked)
#define myget(f)      _IO_getc_unlocked(f)
#else
#define myget(f)      getc(f)
#endif

/*
 * We use macros next(), comment() skip() and num(n) 
 * to read the PGM input data, because PGM has awkward
 * grammar rules which are not easily translated to
 * common stdio routines. Also, note that for parsing
 * large PGM data in text mode it is very slow to use stdio.
 * When a parse error occurs we use the statement "goto bad;".
 */

/* Read the next character from the input stream 'fp'
 * into variable 'c'.
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
 * Jump to the label 'bad' if this is not the case.
 * Skip all whitespace characters and comments.
 */
#define skip()                                 \
        if (c != '#' && !isspace(c)) {         \
          goto bad;                            \
        } else do {                            \
          if (c == '#') {                      \
            comment();                         \
          } else {                             \
            next();                            \
          }                                    \
        } while (c == '#' || isspace(c))

/* Expect to find a digit at the current input position.
 * Jump to the label 'bad' if this is not the case.
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


/*
 * Read a PGM header at the current file position.
 */
PGM* SAC_PGM_open( FILE* fp)
{
  PGM* pgm = (PGM *) SAC_MALLOC( sizeof(PGM));
  size_t width = 0, height = 0;
  unsigned maxval = 0;
  int hdr[2];
  /* 'c' is used by the macros to store the next input character. */
  int c;

  hdr[0] = myget(fp);
  hdr[1] = myget(fp);
  if (hdr[0] != 'P' || (hdr[1] != PGM_TEXT && hdr[1] != PGM_BINARY))
  {
    SAC_RuntimeError("read_pgm: File is not in PGM format");
    goto done;
  }

  next();
  skip();
  num(width);
  skip();
  num(height);
  skip();
  num(maxval);

  if (ungetc(c, fp) == EOF) {
    SAC_RuntimeError("SAC_PGM_open: Failed to ungetc.");
    goto done;
  }

done:
  pgm->width = width;
  pgm->height = height;
  pgm->maxval = maxval;
  pgm->fp = fp;
  pgm->pos = ftell(fp);
  pgm->kind = hdr[1];
  return pgm;

bad:
  if (c != EOF && !ferror(fp) && !feof(fp)) {
    SAC_RuntimeError("SAC_PGM_open: Invalid PGM header.");
    goto done;
  }
  if (ferror(fp)) {
    SAC_RuntimeError("SAC_PGM_open: Errors while reading PGM header.");
    goto done;
  }
  SAC_RuntimeError(
    "SAC_PGM_open: Premature end-of-file while reading PGM header.");
  goto done;
}

void SAC_PGM_close( PGM* pgm)
{
  pgm->width = 0;
  pgm->height = 0;
  pgm->maxval = 0;
  pgm->fp = NULL;
  SAC_FREE( pgm);
}

int SAC_PGM_width( PGM* pgm) { return pgm->width; }
int SAC_PGM_height( PGM* pgm) { return pgm->height; }
int SAC_PGM_maxval( PGM* pgm) { return pgm->maxval; }
FILE* SAC_PGM_stream( PGM* pgm) { return pgm->fp; }

static int *SAC_PGM_read_data( PGM* pgm);

#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void SAC_PGM_data( SAC_ND_PARAM_out(array_nt, int), PGM* pgm)
{
  SAC_ND_DECL__DATA(ret_nt, int,)
  SAC_ND_DECL__DESC(ret_nt,)
  const int num_dims = 2;
  int *intarray = SAC_PGM_read_data( pgm);
  int SAC_ND_A_MIRROR_DIM(ret_nt) = num_dims;

  SAC_ND_ALLOC__DESC(ret_nt, num_dims)
  SAC_ND_SET__RC(ret_nt, 1)
  SAC_ND_A_DESC_SHAPE(ret_nt, 0) = (int) pgm->height;
  SAC_ND_A_DESC_SHAPE(ret_nt, 1) = (int) pgm->width;
  SAC_ND_A_DESC_SIZE(ret_nt) = (int) (pgm->width * pgm->height);
  SAC_ND_A_FIELD(ret_nt) = intarray;
  SAC_ND_RET_out(array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt

static int* SAC_PGM_read_data( PGM* pgm)
{
  size_t pixelcount = pgm->width * pgm->height;
  size_t i;
  size_t val = 0;
  int* data = NULL;
  /* 'c' is used by the macros to store the next input character. */
  int c;
  FILE* fp = pgm->fp;

  /* Verify that the header makes some sense. */
  if (pgm->width == 0 || pgm->height == 0 || pgm->maxval > MAX_PGM_VAL)
  {
    SAC_RuntimeError("SAC_PGM_read_data: File has invalid PGM header");
    goto done;
  }

  /* Make sure the data fits into the address space. */
  pixelcount = pgm->width * pgm->height;
  if (pgm->width > INT_MAX || pgm->height > INT_MAX ||
      pixelcount > INT_MAX || pixelcount / pgm->width != pgm->height)
  {
    SAC_RuntimeError(
      "SAC_PGM_read_data: Image dimensions of (%zu * %zu = %zu) exceed INT_MAX",
      pgm->width, pgm->height, pixelcount);
    goto done;
  }

  /* Restore file position to after the header. */
  if (fseek(pgm->fp, pgm->pos, SEEK_SET) == -1) {
    SAC_RuntimeError("SAC_PGM_read_data: Failed to seek to %ld.", pgm->pos);
    goto done;
  }

  /* Read the first byte. */
  next();

  /* Allocate the image. */
  data = SAC_MALLOC(pixelcount * sizeof(int));

  if (pgm->kind == PGM_TEXT)
  {
    for (i = 0; i < pixelcount; ++i)
    {
      skip();
      num(val);
      data[i] = (int) val;
    }
  }
  else if (pgm->kind == PGM_BINARY)
  {
    /* The header parameter 'maxval' may still be followed by comments. */
    if (c == '#') {
      comment();
    }
    /* One space character separates the header and comments from the data. */
    if (!isspace(c)) {
      goto bad;
    }
    if (pgm->maxval <= MAX_PGM_BYTE_VAL)
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

  /* Check for I/O errors. */
  if (ferror(fp)) {
    goto err;
  }
  if (feof(fp) && (pgm->kind != PGM_TEXT || val > MAX_PGM_VAL)) {
    goto eof;
  }

done:
  return data;

bad:
  if (c != EOF && !ferror(fp) && !feof(fp)) {
    SAC_RuntimeError("SAC_PGM_read_data: Invalid PGM data.");
    goto done;
  }

err:
  if (ferror(fp)) {
    SAC_RuntimeError("SAC_PGM_read_data: Errors while reading PGM data.");
    goto done;
  }

eof:
  SAC_RuntimeError(
      "SAC_PGM_read_data: Premature end-of-file while reading PGM data.");
  goto done;
}

