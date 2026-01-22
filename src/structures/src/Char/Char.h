#ifndef STDLIB__CHAR__H
#define STDLIB__CHAR__H

/*
 *  Implementation of standard module Char ctype functions.
 *  It is sort of unfortunate that we have to use these
 *  functions as they incur a per-character overhead.
 *  However, without them incorrect values were produced.
 *  There were two problems:
 *  The isxxx(.) functions work on unsigned chars and not on chars.
 *  They may segfault when not in the range [-1,255].
 *  They may return any non-zero value when true, but a SAC bool is true if 1.
 */

#include "sacinterface.h"
#include <stdbool.h>

typedef unsigned char uchar;

bool SACisalpha(uchar c);
bool SACisupper(uchar c);
bool SACislower(uchar c);
bool SACisdigit(uchar c);
bool SACisxdigit(uchar c);
bool SACisspace(uchar c);
bool SACispunct(uchar c);
bool SACisalnum(uchar c);
bool SACisprint(uchar c);
bool SACisgraph(uchar c);
bool SACiscntrl(uchar c);
bool SACisascii(sac_int c);
uchar SACtoascii(sac_int c);
uchar SACtolower(uchar c);
uchar SACtoupper(uchar c);

#endif // STDLIB__CHAR__H