/*
 *  implementation of external standard module SysErr
 */


#include <stdio.h>
#include <string.h>

#include <sys/errno.h>


/*****************************************************************/




int	Eperm() {return( EPERM );}				/* Not owner */
int	Enoent() {return( ENOENT );}		        	/* No such file or directory */
int	Esrch() {return( ESRCH );}			/* No such process */
int	Eintr() {return( EINTR );}				/* Interrupted system call */
int	Eio() {return( EIO );}				/* I/O error */
int	Enxio() {return(ENXIO  );}				/* No such device or address */
int	E2big() {return( E2BIG );}				/* Arg list too long */
int	Enoexec() {return( ENOEXEC );}				/* Exec format error */
int	Ebadf() {return( EBADF );}				/* Bad file number */
int	Echild() {return(ECHILD  );}				/* No children */
int	Eagain() {return( EAGAIN );}				/* No more processes */
int	Enomem() {return( ENOMEM );}				/* Not enough core */
int	Eacces() {return( EACCES );}				/* Permission denied */
int	Efault() {return( EFAULT );}				/* Bad address */
int	Enotblk() {return(ENOTBLK  );}				/* Block device required */
int	Ebusy() {return( EBUSY );}				/* Mount device busy */
int	Eexist() {return( EEXIST );}				/* File exists */
int	Exdev() {return( EXDEV );}				/* Cross-device link */
int	Enodev() {return(ENODEV  );}				/* No such device */
int	Enotdir() {return( ENOTDIR );}				/* Not a directory*/
int	Eisdir() {return( EISDIR );}				/* Is a directory */
int	Einval() {return(EINVAL  );}				/* Invalid argument */
int	Enfile() {return(ENFILE  );}				/* File table overflow */
int	Emfile() {return( EMFILE );}	        		/* Too many open files */
int	Enotty() {return( ENOTTY );}				/* Not a typewriter */
int	Etxtbsy() {return( ETXTBSY );}				/* Text file busy */
int	Efbig() {return( EFBIG );}				/* File too large */
int	Enospc() {return( ENOSPC );}				/* No space left on device */
int	Espipe() {return( ESPIPE );}				/* Illegal seek */
int	Erofs() {return( EROFS );}				/* Read-only file system */
int	Emlink() {return(EMLINK  );}				/* Too many links */
int	Epipe() {return(EPIPE  );}				/* Broken pipe */

/* math software */
int	Edom() {return( EDOM );}				/* Argument too large */
int	Erange() {return(ERANGE  );}				/* Result too large */


	/* operational errors */
int	Enetdown() {return(  ENETDOWN);}			/* Network is down */
int	Enetunreach() {return( ENETUNREACH );}			/* Network is unreachable */
int	Enetreset() {return( ENETRESET );}			/* Network dropped connection on reset */
int	Econnaborted() {return( ECONNABORTED );}			/* Software caused connection abort */
int	Econnreset() {return( ECONNRESET );}			/* Connection reset by peer */
int	Enobufs() {return( ENOBUFS );}	       		/* No buffer space available */
int	Eisconn() {return( EISCONN );}	       		/* Socket is already connected */
int	Enotconn() {return( ENOTCONN );}			/* Socket is not connected */
int	Eshutdown() {return(ESHUTDOWN  );}			/* Can't send after socket shutdown */
int	Etoomanyrefs() {return( ETOOMANYREFS );}			/* Too many references: can't splice */
int	Etimedout() {return( ETIMEDOUT );}			/* Connection timed out */
int	Econnrefused() {return( ECONNREFUSED );}			/* Connection refused */

	/* */
int	Eloop() {return( ELOOP );}	       		/* Too many levels of symbolic links */
int	Enametoolong() {return(ENAMETOOLONG  );}			/* File name too long */

/* should be rearranged */
int	Ehostdown() {return(EHOSTDOWN  );}	       	        /* Host is down */
int	Ehostunreach() {return( EHOSTUNREACH );}			/* No route to host */
int	Enotempty() {return(ENOTEMPTY  );}			/* Directory not empty */

/* quotas & mush */
int	Eusers() {return( EUSERS );}		       	/* Too many users */
int	Edquot() {return( EDQUOT );}		       	/* Disc quota exceeded */

/* Network File System */
int	Estale() {return( ESTALE );}		       	/* Stale NFS file handle */
int	Eremote() {return(EREMOTE  );}		       	/* Too many levels of remote in path */

/* streams */
int	Enostr() {return( ENOSTR );}		      	/* Device is not a stream */
int	Etime() {return(ETIME  );}	       		/* Timer expired */
int	Enosr() {return(ENOSR  );}	       		/* Out of streams resources */
int	Enomsg() {return(ENOMSG  );}	       		/* No message of desired type */
int	Ebadmsg() {return( EBADMSG );}	       		/* Trying to read unreadable message */

