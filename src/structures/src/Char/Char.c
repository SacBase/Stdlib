#include <ctype.h>

#include "Char.h"

bool SACisalpha(uchar c)
{
    return isalpha(c) != 0;
}

bool SACisupper(uchar c)
{
    return isupper(c) != 0;
}

bool SACislower(uchar c)
{
    return islower(c) != 0;
}

bool SACisdigit(uchar c)
{
    return isdigit(c) != 0;
}

bool SACisxdigit(uchar c)
{
    return isxdigit(c) != 0;
}

bool SACisspace(uchar c)
{
    return isspace(c) != 0;
}

bool SACispunct(uchar c)
{
    return ispunct(c) != 0;
}

bool SACisalnum(uchar c)
{
    return isalnum(c) != 0;
}

bool SACisprint(uchar c)
{
    return isprint(c) != 0;
}

bool SACisgraph(uchar c)
{
    return isgraph(c) != 0;
}

bool SACiscntrl(uchar c)
{
    return iscntrl(c) != 0;
}

bool SACisascii(sac_int c)
{
    return c >= 0 && c < 256 && isascii(c) != 0;
}

uchar SACtoascii(sac_int c)
{
    return toascii(c & 0xFF);
}

uchar SACtolower(uchar c)
{
    return tolower(c);
}

uchar SACtoupper(uchar c)
{
    return toupper(c);
}
