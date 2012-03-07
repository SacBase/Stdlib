#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#include "sac.h"

/* This structure holds the current file position
 * and the contents of the PGM header.
 */
typedef struct PGM {
  FILE*  fp;
  long   pos;
  int    kind;          // either PGM_BINARY or PGM_TEXT.
  size_t width;
  size_t height;
  size_t maxval;
} PGM;

/* The PGM 'maxval' for 8-bit images. */
#define PGM_MAX_BYTE_VAL        255

/* The PGM 'maxval' for 16-bit images. */
#define PGM_MAX_VAL             65535

/* The lowest/blackest pixel value. */
#define PGM_MIN_VAL             0

/* The second character in a PGM header for binary images. */
#define PGM_BINARY              '5'

/* The second character in a PGM header for text mode images. */
#define PGM_TEXT                '2'

/* The maximum allowed line length in a PGM file according to specification. */
#define PGM_MAX_LINE_SIZE       70

/*
 * Because we access the file single-threaded it is more
 * efficient to use unlocked versions of getc and putc.
 * We could also use the functions 'getc_unlocked' and 'putc_unlocked',
 * but we cannot easily detect whether these are supported
 * by the current system.
 */
#if defined(_IO_getc_unlocked)
#define myget(f)      _IO_getc_unlocked(f)
#else
#define myget(f)      getc(f)
#endif

#if defined(_IO_putc_unlocked)
#define myput(c,f)      _IO_putc_unlocked(c,f)
#else
#define myput(c,f)      putc(c,f)
#endif


#endif
