/*
 *  implementation of directory functions.
 */



#include "Dir.h"

/*
 * SBS: I assume all systems do have readdir
 * If they turn out not to, we may have to preset the macro
 * HAVE_READDIR through cmake...
 */
#define HAVE_READDIR 1

/*****************************************************************/

string SACreaddir( DIR* stream)
{

#if HAVE_READDIR
#else // HAVE_READDIR
  /* some old OSes don't allocate enough room for entry.d_name. */
  struct bigenough {
    struct dirent entry;
    char name[1024];
  } big;
  int r;
#endif // HAVE_READDIR

  struct dirent* entptr;
  string name = NULL;

  while (name == NULL) {
#if HAVE_READDIR
    entptr = readdir( stream);
    if (entptr != NULL) {
#else // HAVE_READDIR
    entptr = NULL;
    r = readdir_r( stream, &big.entry, &entptr);
    if (r == 0 && entptr != NULL) {
#endif // HAVE_READDIR
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
