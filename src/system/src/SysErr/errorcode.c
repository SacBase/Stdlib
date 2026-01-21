/*
 *  implementation of external standard module SysErr
 */

#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

#include "sacinterface.h"

sac_int	Eperm(void)   { return EPERM;   } /* Not owner */
sac_int	Enoent(void)  { return ENOENT;  } /* No such file or directory */
sac_int	Esrch(void)   { return ESRCH;   } /* No such process */
sac_int	Eintr(void)   { return EINTR;   } /* Interrupted system call */
sac_int	Eio(void)     { return EIO;     } /* I/O error */
sac_int	Enxio(void)   { return ENXIO;   } /* No such device or address */
sac_int	E2big(void)   { return E2BIG;   } /* Arg list too long */
sac_int	Enoexec(void) { return ENOEXEC; } /* Exec format error */
sac_int	Ebadf(void)   { return EBADF;   } /* Bad file number */
sac_int	Echild(void)  { return ECHILD;  } /* No children */
sac_int	Eagain(void)  { return EAGAIN;  } /* No more processes */
sac_int	Enomem(void)  { return ENOMEM;  } /* Not enough core */
sac_int	Eacces(void)  { return EACCES;  } /* Permission denied */
sac_int	Efault(void)  { return EFAULT;  } /* Bad address */
sac_int	Enotblk(void) { return ENOTBLK; } /* Block device required */
sac_int	Ebusy(void)   { return EBUSY;   } /* Mount device busy */
sac_int	Eexist(void)  { return EEXIST;  } /* File exists */
sac_int	Exdev(void)   { return EXDEV;   } /* Cross-device link */
sac_int	Enodev(void)  { return ENODEV;  } /* No such device */
sac_int	Enotdir(void) { return ENOTDIR; } /* Not a directory*/
sac_int	Eisdir(void)  { return EISDIR;  } /* Is a directory */
sac_int	Einval(void)  { return EINVAL;  } /* Invalid argument */
sac_int	Enfile(void)  { return ENFILE;  } /* File table overflow */
sac_int	Emfile(void)  { return EMFILE;  } /* Too many open files */
sac_int	Enotty(void)  { return ENOTTY;  } /* Not a typewriter */
sac_int	Etxtbsy(void) { return ETXTBSY; } /* Text file busy */
sac_int	Efbig(void)   { return EFBIG;   } /* File too large */
sac_int	Enospc(void)  { return ENOSPC;  } /* No space left on device */
sac_int	Espipe(void)  { return ESPIPE;  } /* Illegal seek */
sac_int	Erofs(void)   { return EROFS;   } /* Read-only file system */
sac_int	Emlink(void)  { return EMLINK;  } /* Too many links */
sac_int	Epipe(void)   { return EPIPE;   } /* Broken pipe */

/* math software */
sac_int	Edom(void)   { return EDOM;   } /* Argument too large */
sac_int	Erange(void) { return ERANGE; } /* Result too large */


/* operational errors */
sac_int	Enetdown(void)     { return ENETDOWN;     } /* Network is down */
sac_int	Enetunreach(void)  { return ENETUNREACH;  } /* Network is unreachable */
sac_int	Enetreset(void)    { return ENETRESET;    } /* Network dropped connection on reset */
sac_int	Econnaborted(void) { return ECONNABORTED; } /* Software caused connection abort */
sac_int	Econnreset(void)   { return ECONNRESET;   } /* Connection reset by peer */
sac_int	Enobufs(void)      { return ENOBUFS;      } /* No buffer space available */
sac_int	Eisconn(void)      { return EISCONN;      } /* Socket is already connected */
sac_int	Enotconn(void)     { return ENOTCONN;     } /* Socket is not connected */
sac_int	Eshutdown(void)    { return ESHUTDOWN;    } /* Can't send after socket shutdown */
sac_int	Etoomanyrefs(void) { return ETOOMANYREFS; } /* Too many references: can't splice */
sac_int	Etimedout(void)    { return ETIMEDOUT;    } /* Connection timed out */
sac_int	Econnrefused(void) { return ECONNREFUSED; } /* Connection refused */

/* */
sac_int	Eloop(void)        { return ELOOP;        } /* Too many levels of symbolic links */
sac_int	Enametoolong(void) { return ENAMETOOLONG; } /* File name too long */

/* should be rearranged */
sac_int	Ehostdown(void)    { return EHOSTDOWN;    } /* Host is down */
sac_int	Ehostunreach(void) { return EHOSTUNREACH; } /* No route to host */
sac_int	Enotempty(void)    { return ENOTEMPTY;    } /* Directory not empty */

/* quotas & mush */
sac_int	Eusers(void) { return EUSERS; } /* Too many users */
sac_int	Edquot(void) { return EDQUOT; } /* Disc quota exceeded */

/* network file system */
sac_int	Estale(void)  { return ESTALE;  } /* Stale NFS file handle */
sac_int	Eremote(void) { return EREMOTE; } /* Too many levels of remote in path */
