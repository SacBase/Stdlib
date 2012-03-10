/*
 *  implementation of directory functions.
 */



#include "Dir.h"



/*****************************************************************/

string SACreaddir( DIR* stream)
{
  /* some old OSes don't allocate enough room for entry.d_name. */
  struct bigenough {
    struct dirent entry;
    char name[1024];
  } big;
  struct dirent* entptr;
  int r;
  string name = NULL;

  while (name == NULL) {
    entptr = NULL;
    r = readdir_r( stream, &big.entry, &entptr);
    if (r == 0 && entptr != NULL) {
      char *s = entptr->d_name;
      /* ignore "." and ".." */
      if (*s == '.' && (s[1] == '\0' || (s[1] == '.' && s[2] == '\0'))) {
      } else {
        name = (string) SAC_MALLOC( strlen( s) + 1);
        strcpy( name, s);
      }
    } else {
      name = (string) SAC_MALLOC( 1);
      name[0] = '\0';
    }
  }

  return( name);
}


/*****************************************************************/
