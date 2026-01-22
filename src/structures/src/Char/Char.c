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

#include <ctype.h>
#include "Char.h"

typedef unsigned char uchar;

int SACisalpha(uchar c)
{
  return isalpha(c) != 0;
}

int SACisupper(uchar c)
{
  return isupper(c) != 0;
}

int SACislower(uchar c)
{
  return islower(c) != 0;
}

int SACisdigit(uchar c)
{
  return isdigit(c) != 0;
}

int SACisxdigit(uchar c)
{
  return isxdigit(c) != 0;
}

int SACisspace(uchar c)
{
  return isspace(c) != 0;
}

int SACispunct(uchar c)
{
  return ispunct(c) != 0;
}

int SACisalnum(uchar c)
{
  return isalnum(c) != 0;
}

int SACisprint(uchar c)
{
  return isprint(c) != 0;
}

int SACisgraph(uchar c)
{
  return isgraph(c) != 0;
}

int SACiscntrl(uchar c)
{
  return iscntrl(c) != 0;
}

int SACisascii(sac_int c)
{
  return c >= 0 && c < 256 && isascii(c) != 0;
}

int SACtoascii(sac_int c)
{
  return toascii(c & 0xFF);
}

int SACtolower(uchar c)
{
  return tolower(c);
}

int SACtoupper(uchar c)
{
  return toupper(c);
}

