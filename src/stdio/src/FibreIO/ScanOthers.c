/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

#define FIBRESCAN(returntype, alias, token, typename)	\
returntype FibreScan##alias( FILE *stream)		\
{							\
  start_token = PARSE_##token;				\
  doScan( stream);                                     \
  return( typename##val);				\
}

FIBRESCAN(char, Byte, BYTE, byte)
FIBRESCAN(short, Short, SHORT, short)
FIBRESCAN(long, Long, LONG, long)
FIBRESCAN(long long, Longlong, LONGLONG, longlong)
FIBRESCAN(unsigned char, Ubyte, UBYTE, ubyte)
FIBRESCAN(unsigned short, Ushort, USHORT, ushort)
FIBRESCAN(unsigned int, Uint, UINT, uint)
FIBRESCAN(unsigned long, Ulong, ULONG, ulong)
FIBRESCAN(unsigned long long, Ulonglong, ULONGLONG, ulonglong)

