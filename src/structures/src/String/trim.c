/*
 *  implementation of standard module StringC
 */


#include <ctype.h>
#include "StringC.h"


/*****************************************************************/

string SACchomp(string in)
{
  size_t len = strlen(in);
  size_t i;
  string out;

  for (i = len; i > 0; ) {
    --i;
    if (in[i] != '\r' && in[i] != '\n') {
      ++i;
      break;
    }
  }

  out = (string) SAC_MALLOC( i + 1);
  strncpy(out, in, i);
  out[i] = '\0';

  return out;
}

/*****************************************************************/

string SACrtrim(string in)
{
  size_t len = strlen(in);
  size_t i;
  string out;

  for (i = len; i > 0; ) {
    --i;
    if (!isspace((unsigned char) in[i])) {
      ++i;
      break;
    }
  }

  out = (string) SAC_MALLOC( i + 1);
  strncpy(out, in, i);
  out[i] = '\0';

  return out;
}

/*****************************************************************/

string SACltrim(string in)
{
  size_t len = strlen(in);
  size_t i;
  string out;

  for (i = 0; i < len; ++i) {
    if (!isspace((unsigned char) in[i])) {
      break;
    }
  }

  out = (string) SAC_MALLOC( len - i + 1);
  strncpy(out, in + i, len - i);
  out[len - i] = '\0';

  return out;
}

/*****************************************************************/

string SACtrim(string in)
{
  size_t len = strlen(in);
  size_t i, j;
  string out;

  for (i = len; i > 0; ) {
    --i;
    if (!isspace((unsigned char) in[i])) {
      ++i;
      break;
    }
  }
  for (j = 0; j < i; ++j) {
    if (!isspace((unsigned char) in[j])) {
      break;
    }
  }

  out = (string) SAC_MALLOC( i - j + 1);
  strncpy(out, in + j, i - j);
  out[i - j] = '\0';

  return out;
}

/*****************************************************************/
