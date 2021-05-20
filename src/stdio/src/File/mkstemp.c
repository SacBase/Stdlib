/*
 *  implementation of class File
 */
#include <string.h>
#include <stdlib.h>

#include "File.h"

#define res_nt    (res,   T_OLD((SCL, (HID, (NUQ,)))))
#define str_nt    (str,   T_OLD((SCL, (HID, (NUQ,)))))
#define filep_nt  (filep, T_OLD((SCL, (HID, (NUQ,)))))

/*****************************************************************/

int SACmkstemp ( SAC_ND_PARAM_out_nodesc (filep_nt, FILE*),
                 SAC_ND_PARAM_out (str_nt, char*),
                 const char* template)
{
  int error = EXIT_SUCCESS;
  int filedesc;
  int length = strlen (template);
  SAC_ND_DECL__DESC (str_nt, )
  SAC_ND_DECL__DATA (str_nt, char*, )
  SAC_ND_DECL__DATA (filep_nt, FILE*, )

  // initialise filep
  SAC_ND_A_FIELD (filep_nt) = NULL;

  // alloc string descriptor and string
  SAC_ND_ALLOC__DESC (str_nt, 0)
  SAC_ND_SET__RC (str_nt, 1)
  SAC_ND_A_FIELD (str_nt) = SAC_MALLOC (length + 1);

  // copy template
  strncpy (SAC_ND_A_FIELD (str_nt), template, length);
  SAC_ND_A_FIELD (str_nt)[length + 1] = '\0';

  // create temp file, get name back
  filedesc = mkstemp (SAC_ND_A_FIELD (str_nt));

  if (filedesc == -1) {
    error = EIO;
  }
  else {
    SAC_ND_A_FIELD (filep_nt) = fdopen( filedesc, "w+");
    if (SAC_ND_A_FIELD (filep_nt) == NULL) {
	    error = errno;
    }
  }

  SAC_ND_RET_out__NODESC (filep_nt, filep_nt)
  SAC_ND_RET_out (str_nt, str_nt)

  // return the error
  return error;
}

#undef res_nt
#undef str_nt
#undef filep_nt
