/*
 *  implementation of external standard module SysErr
 */


#include <stdio.h>
#include <string.h>

#include <sys/errno.h>


/*****************************************************************/




int	Eperm( void) {return( EPERM );}				/* Not owner */
int	Enoent( void) {return( ENOENT );}		        	/* No such file or directory */
int	Esrch( void) {return( ESRCH );}			/* No such process */
int	Eintr( void) {return( EINTR );}				/* Interrupted system call */
int	Eio( void) {return( EIO );}				/* I/O error */
int	Enxio( void) {return(ENXIO  );}				/* No such device or address */
int	E2big( void) {return( E2BIG );}				/* Arg list too long */
int	Enoexec( void) {return( ENOEXEC );}				/* Exec format error */
int	Ebadf( void) {return( EBADF );}				/* Bad file number */
int	Echild( void) {return(ECHILD  );}				/* No children */
int	Eagain( void) {return( EAGAIN );}				/* No more processes */
int	Enomem( void) {return( ENOMEM );}				/* Not enough core */
int	Eacces( void) {return( EACCES );}				/* Permission denied */
int	Efault( void) {return( EFAULT );}				/* Bad address */
int	Enotblk( void) {return(ENOTBLK  );}				/* Block device required */
int	Ebusy( void) {return( EBUSY );}				/* Mount device busy */
int	Eexist( void) {return( EEXIST );}				/* File exists */
int	Exdev( void) {return( EXDEV );}				/* Cross-device link */
int	Enodev( void) {return(ENODEV  );}				/* No such device */
int	Enotdir( void) {return( ENOTDIR );}				/* Not a directory*/
int	Eisdir( void) {return( EISDIR );}				/* Is a directory */
int	Einval( void) {return(EINVAL  );}				/* Invalid argument */
int	Enfile( void) {return(ENFILE  );}				/* File table overflow */
int	Emfile( void) {return( EMFILE );}	        		/* Too many open files */
int	Enotty( void) {return( ENOTTY );}				/* Not a typewriter */
int	Etxtbsy( void) {return( ETXTBSY );}				/* Text file busy */
int	Efbig( void) {return( EFBIG );}				/* File too large */
int	Enospc( void) {return( ENOSPC );}				/* No space left on device */
int	Espipe( void) {return( ESPIPE );}				/* Illegal seek */
int	Erofs( void) {return( EROFS );}				/* Read-only file system */
int	Emlink( void) {return(EMLINK  );}				/* Too many links */
int	Epipe( void) {return(EPIPE  );}				/* Broken pipe */

/* math software */
int	Edom( void) {return( EDOM );}				/* Argument too large */
int	Erange( void) {return(ERANGE  );}				/* Result too large */


	/* operational errors */
int	Enetdown( void) {return(  ENETDOWN);}			/* Network is down */
int	Enetunreach( void) {return( ENETUNREACH );}			/* Network is unreachable */
int	Enetreset( void) {return( ENETRESET );}			/* Network dropped connection on reset */
int	Econnaborted( void) {return( ECONNABORTED );}			/* Software caused connection abort */
int	Econnreset( void) {return( ECONNRESET );}			/* Connection reset by peer */
int	Enobufs( void) {return( ENOBUFS );}	       		/* No buffer space available */
int	Eisconn( void) {return( EISCONN );}	       		/* Socket is already connected */
int	Enotconn( void) {return( ENOTCONN );}			/* Socket is not connected */
int	Eshutdown( void) {return(ESHUTDOWN  );}			/* Can't send after socket shutdown */
int	Etoomanyrefs( void) {return( ETOOMANYREFS );}		/* Too many references: can't splice */
int	Etimedout( void) {return( ETIMEDOUT );}			/* Connection timed out */
int	Econnrefused( void) {return( ECONNREFUSED );}			/* Connection refused */

	/* */
int	Eloop( void) {return( ELOOP );}	       		/* Too many levels of symbolic links */
int	Enametoolong( void) {return(ENAMETOOLONG  );}			/* File name too long */

/* should be rearranged */
int	Ehostdown( void) {return(EHOSTDOWN  );}	       	        /* Host is down */
int	Ehostunreach( void) {return( EHOSTUNREACH );}			/* No route to host */
int	Enotempty( void) {return(ENOTEMPTY  );}			/* Directory not empty */

/* quotas & mush */
int	Eusers( void) {return( EUSERS );}		       	/* Too many users */
int	Edquot( void) {return( EDQUOT );}		       	/* Disc quota exceeded */

/* Network File System */
int	Estale( void) {return( ESTALE );}		       	/* Stale NFS file handle */
int	Eremote( void) {return(EREMOTE  );}		       	/* Too many levels of remote in path */




