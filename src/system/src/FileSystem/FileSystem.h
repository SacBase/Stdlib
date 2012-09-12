/*
 *  implementation of class FileSystem
 */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "sac.h"

/* 
 * Cygwin fix to ensure P_tmpdir is defined as "/tmp" 
 * without this the stdlib build will die here.
 */
#ifdef __CYGWIN__
#define P_tmpdir 		"/tmp"
#endif

