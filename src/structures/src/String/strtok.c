/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

string SACstrtok( string *remain, string input, string sep)
{
  int i, j, k;
  string token;

  /* increment 'i' as long as input[i] is in "sep". */
  i = k = 0;
  while (input[i] && sep[k]) {
    k = 0;
    while (sep[k] && input[i] != sep[k]) {
      ++k;
    }
    if (sep[k]) {
      ++i;
    }
  }

  /* increment 'j' as long as input[j] is not in "sep". */
  j = i;
  k = 0;
  while (input[j] && sep[k] != input[j]) {
    k = 0;
    while (sep[k] && input[j] != sep[k]) {
      ++k;
    }
    if (!sep[k]) {
      ++j;
    }
  }

  token = (string) SAC_MALLOC( j - i + 1);
  strncpy(token, input + i, j - i);
  token[j - i] = '\0';

  *remain = (string) SAC_MALLOC( strlen( input + j) + 1);
  strcpy( *remain, input + j);
  
  return( token);
}

/*****************************************************************/
