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

#include <sacinterface.h>
#include <ctype.h>

typedef unsigned char uchar;

int SACisalpha(uchar c);
int SACisupper(uchar c);
int SACislower(uchar c);
int SACisdigit(uchar c);
int SACisxdigit(uchar c);
int SACisspace(uchar c);
int SACispunct(uchar c);
int SACisalnum(uchar c);
int SACisprint(uchar c);
int SACisgraph(uchar c);
int SACiscntrl(uchar c);
int SACisascii(sac_int c);
int SACtoascii(sac_int c);
int SACtolower(uchar c);
int SACtoupper(uchar c);

#endif // STDLIB__CHAR__H