#include <limits.h>

#define UCHAR_MIN 0
#define USHRT_MIN 0
#define UINT_MIN 0
#define ULONG_MIN 0
#define ULLONG_MIN 0

#define minmax(rtype, SACtype, typeucase)	\
rtype max##SACtype()				\
{						\
  return( typeucase##_MAX);			\
}						\
						\
rtype min##SACtype()				\
{						\
  return( typeucase##_MIN);			\
}

minmax(char, byte, CHAR)
minmax(short, short, SHRT)
minmax(long, long, LONG)
minmax(long long, longlong, LLONG)
minmax(unsigned char, ubyte, UCHAR)
minmax(unsigned short, ushort, USHRT)
minmax(unsigned int, uint, UINT)
minmax(unsigned long, ulong, ULONG)
minmax(unsigned long long, ulonglong, ULLONG)
