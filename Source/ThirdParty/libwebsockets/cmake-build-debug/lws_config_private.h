/* lws_config_private.h.in. Private compilation options. */

#ifndef NDEBUG
	#ifndef _DEBUG
		#define _DEBUG
	#endif
#endif
/* #undef LWIP_PROVIDE_ERRNO */

/* Define to 1 to use CyaSSL as a replacement for OpenSSL. 
 * LWS_OPENSSL_SUPPORT needs to be set also for this to work. */
/* #undef USE_CYASSL */

/* Define to 1 if you have the `fork' function. */
#define LWS_HAVE_FORK

/* Define to 1 if you have the `getenv' function. */
#define LWS_HAVE_GETENV

/* Define to 1 if you have the <in6addr.h> header file. */
/* #undef LWS_HAVE_IN6ADDR_H */

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define LWS_HAVE_MALLOC

/* Define to 1 if you have the <memory.h> header file. */
#define LWS_HAVE_MEMORY_H

/* Define to 1 if you have the <netinet/in.h> header file. */
#define LWS_HAVE_NETINET_IN_H

/* Define to 1 if you have the <stdint.h> header file. */
#define LWS_HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define LWS_HAVE_STDLIB_H

/* Define to 1 if you have the `strerror' function. */
#define LWS_HAVE_STRERROR

/* Define to 1 if you have the <strings.h> header file. */
#define LWS_HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#define LWS_HAVE_STRING_H

/* Define to 1 if you have the <sys/prctl.h> header file. */
/* #undef LWS_HAVE_SYS_PRCTL_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define LWS_HAVE_SYS_SOCKET_H

/* Define to 1 if you have the <sys/sockio.h> header file. */
#define LWS_HAVE_SYS_SOCKIO_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#define LWS_HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#define LWS_HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#define LWS_HAVE_UNISTD_H

/* #undef LWS_HAVE_TCP_USER_TIMEOUT */

/* Define to 1 if you have the `vfork' function. */
#define LWS_HAVE_VFORK

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef LWS_HAVE_VFORK_H */

/* Define to 1 if `fork' works. */
/* #undef LWS_HAVE_WORKING_FORK */

/* Define to 1 if `vfork' works. */
/* #undef LWS_HAVE_WORKING_VFORK */

/* Define to 1 if execvpe() exists */
/* #undef LWS_HAVE_EXECVPE */

/* Define to 1 if you have the <zlib.h> header file. */
/* #undef LWS_HAVE_ZLIB_H */

#define LWS_HAVE_GETLOADAVG

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#undef LT_OBJDIR // We're not using libtool

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to rpl_realloc if the replacement function should be used. */
/* #undef realloc */

/* Define to 1 if we have getifaddrs */
#define LWS_HAVE_GETIFADDRS

/* Define if the inline keyword doesn't exist. */
/* #undef inline */

/* #undef LWS_WITH_ZLIB */
/* #undef LWS_HAS_PTHREAD_SETNAME_NP */

/* Defined if you have the <inttypes.h> header file. */
#define LWS_HAVE_INTTYPES_H
